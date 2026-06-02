#!/usr/bin/env python3

# ------------------------------------------------------------------------------
# Orca / Prusa / Super Slicer post-processor script for the Professional Firmware
# URL: https://github.com/mriscoc/Ender3V2S1
# Miguel A. Risco-Castillo
# version: 2.2
# date: 2023/12/10
#
# Contains code from the jpg re-encoder thumbnail post processor script:
# github.com/alexqzd/Marlin/blob/Gcode-preview/Display%20firmware/gcode_thumb_to_jpg.py
# ------------------------------------------------------------------------------

"""
Copy and paste this into "Machine start G-code" in Printer Settings
(see Orca-PrinterSettings-StartScript.png)

;
; First layer print x min = [first_layer_print_min_0]
; First layer print y min = [first_layer_print_min_1]
; First layer print x max = [first_layer_print_max_0]
; First layer print y max = [first_layer_print_max_1]
; Total layer count = [total_layer_count]
;

"""

import sys
import re
import os
import base64
import io
import subprocess

try:
    from PIL import Image
except ImportError:
    subprocess.check_call([sys.executable, "-m", "pip", "install", "Pillow"])

try:
    from PIL import Image
except Exception:
    warning_msg = "Python Pillow (PIL) is not installed!\n\nOpen your terminal and run:\nsudo apt install python3-pil"
    try:
        subprocess.run(['zenity', '--error', '--title', 'Missing Dependency', '--text', warning_msg], check=False)
    except FileNotFoundError:
        pass
    print("Pillow missing. Exiting script so slicer doesn't freeze.")
    sys.exit(0)

# Fallback for older Pillow versions commonly found on Debian/ChromeOS
try:
    resampling_filter = Image.Resampling.LANCZOS
except AttributeError:
    resampling_filter = Image.LANCZOS

# Get the g-code source file name
sourceFile = sys.argv[1]

# Read the ENTIRE g-code file into memory
with open(sourceFile, "r") as f:
    lines = f.read()

thumb_expresion = "; thumbnail begin.*?\n((.|\n)*?); thumbnail end"
size_expresion = "; thumbnail begin [0-9]+x[0-9]+ [0-9]+"
size_expresion_group = "; thumbnail begin [0-9]+x[0-9]+ ([0-9]+)"

thumb_matches = re.findall(thumb_expresion, lines)
size_matches = re.findall(size_expresion, lines)

def encodedStringToGcodeComment(encodedString):
    n = 78
    return ("; " + "\n; ".join(encodedString[i : i + n] for i in range(0, len(encodedString), n)) + "\n")

# Thumbnail size selection
size_options = {
    "1": ("200x200", (200, 200), "DWIN LCD screen"),
    "2": ("180x180", (180, 180), "TJC/DACAI LCD screen")
}

# GUI Pop-up for thumbnail selection
try:
    import tkinter as tk

    def get_gui_choice():
        root = tk.Tk()
        root.title("Thumbnail Size Selector")
        root.attributes('-topmost', True)
        root.geometry("450x180")

        # Explicitly bind variables to the root window to prevent memory loss
        choice_var = tk.StringVar(root, value="1")
        result = {"choice": "1"}

        def save_and_close(event=None):
            result["choice"] = choice_var.get()
            root.quit()

        # Safely capture the choice even if you hit Enter or use the "X" button
        root.protocol("WM_DELETE_WINDOW", save_and_close)
        root.bind('<Return>', save_and_close)

        tk.Label(root, text="Select thumbnail size:", font=("Arial", 12, "bold")).pack(pady=10)

        for key, (label, _, desc) in size_options.items():
            tk.Radiobutton(root, text=f"{label} - {desc}", variable=choice_var, value=key).pack(anchor="w", padx=30)

        tk.Button(root, text="OK", command=save_and_close, width=15).pack(pady=15)

        root.eval('tk::PlaceWindow . center')
        root.mainloop()

        try:
            root.destroy()
        except:
            pass

        return result["choice"]

    choice = get_gui_choice()

except ImportError:
    # If tkinter fails to load, try to show an OS-level pop-up warning
    warning_msg = "Python Tkinter is not installed!\n\nDefaulting to 200x200 thumbnail.\n\nTo enable the pop-up selector, open your terminal and run:\nsudo apt install python3-tk"
    try:
        # zenity creates a standard Linux error/warning dialog box
        subprocess.run(["zenity", "--warning", "--title", "Missing Dependency", "--text", warning_msg], check=False)
    except FileNotFoundError:
        try:
            # Fallback to system notification if zenity isn't installed
            subprocess.run(["notify-send", "Slicer Script Warning", "Tkinter missing. Defaulting to 200x200."], check=False)
        except FileNotFoundError:
            pass

    print("Tkinter missing. Defaulting to 200x200.")
    choice = "1"

except Exception as e:
    print(f"GUI failed to load: {e}. Defaulting to 200x200.")
    choice = "1"

# Process selected size
if choice in size_options:
    size_label, size_tuple, _ = size_options[choice]
else:
    size_tuple = (200, 200)
    size_label = "200x200"

for idx, match in enumerate(thumb_matches):
    original = match[0]
    encoded = original.replace("; ", "")
    encoded = encoded.replace("\n", "")
    encoded = encoded.replace("\r", "")
    decoded = base64.b64decode(encoded)
    img_png = Image.open(io.BytesIO(decoded))
    img_png_rgb = img_png.convert("RGB")

    # Using the safe resampling filter set at the top of the script
    img_png_rgb = img_png_rgb.resize(size_tuple, resampling_filter)

    img_byte_arr = io.BytesIO()
    img_png_rgb.save(img_byte_arr, format="jpeg")
    img_byte_arr = img_byte_arr.getvalue()
    encodedjpg = base64.b64encode(img_byte_arr).decode("utf-8")
    encodedjpg_gcode = encodedStringToGcodeComment(encodedjpg)
    lines = lines.replace(original, encodedjpg_gcode)

    size_match = size_matches[idx]
    size = re.findall(size_expresion_group, size_match)
    new_size = size_match.replace(size[0], str(len(encodedjpg)))
    new_size = re.sub(r'(\d+x\d+)', size_label, new_size)
    lines = lines.replace(size_match, new_size)

# If the thumbnail was already a JPG, reformat block start
lines = lines.replace("thumbnail_JPG", "thumbnail")

# Prepare header values
ph = re.search("; generated by (.*)\n", lines)
if ph is not None:
    lines = lines.replace(ph[0], "")

time = 0
match = re.search(r'; estimated printing time \(normal mode\) = (.*)\n', lines)
if match is not None:
    h = re.search(r'(\d+)h', match[1])
    h = int(h[1]) if h is not None else 0
    m = re.search(r'(\d+)m', match[1])
    m = int(m[1]) if m is not None else 0
    s = re.search(r'(\d+)s', match[1])
    s = int(s[1]) if s is not None else 0
    time = h * 3600 + m * 60 + s

match = re.search(r'; filament used \[mm\] = ([0-9.]+)', lines)
filament = float(match[1]) / 1000 if match is not None else 0

match = os.getenv("SLIC3R_LAYER_HEIGHT")
layer = float(match) if match is not None else 0

match = re.search(r'; First layer print x min = ([0-9.]+)', lines)
minx = float(match[1]) if match is not None else 0

match = re.search(r'; First layer print y min = ([0-9.]+)', lines)
miny = float(match[1]) if match is not None else 0

match = re.search(r'; First layer print x max = ([0-9.]+)', lines)
maxx = float(match[1]) if match is not None else 0

match = re.search(r'; First layer print y max = ([0-9.]+)', lines)
maxy = float(match[1]) if match is not None else 0

match = re.search(r'; Total layer count = ([0-9.]+)', lines)
totlc = float(match[1]) if match is not None else 0

maxz = layer * totlc
minz = 0

# Generate output file
try:
    with open(sourceFile, "w+") as of:
        # Write header values
        if ph is not None: of.write(ph[0])
        of.write(";FLAVOR:Marlin\n")
        of.write(";TIME:{:d}\n".format(time))
        of.write(";Filament used: {:.6f}\n".format(filament))
        of.write(";Layer height: {:.2f}\n".format(layer))
        of.write(";MINX:{:.3f}\n".format(minx))
        of.write(";MINY:{:.3f}\n".format(miny))
        of.write(";MINZ:{:.3f}\n".format(minz))
        of.write(";MAXX:{:.3f}\n".format(maxx))
        of.write(";MAXY:{:.3f}\n".format(maxy))
        of.write(";MAXZ:{:.3f}\n".format(maxz))
        of.write(";POSTPROCESSED\n")
        of.write(";Header generated for the MRiscoCProUI Firmware\n")
        of.write(";https://github.com/classicrocker883/MRiscoCProUI\n")
        of.write(lines)
except Exception as e:
    print(f"Error writing output file: {e}")
