#
# open_explorer.py
#
def open_file_explorer():
    import subprocess
    from pathlib import Path
    from SCons.Script import DefaultEnvironment

    env = DefaultEnvironment()
    BUILD_PATH = Path(env["PROJECT_BUILD_DIR"], env["PIOENV"])
    script = f"{BUILD_PATH}"
    import platform
    current_OS = platform.system()
    if current_OS == "Windows":
        import os
        try:
            os.startfile(script)
        except OSError:
            try:
                subprocess.run(["explorer", str(script)], check=True)
            except Exception as e:
                print(f"Could not open File Explorer, an error occurred: {e}")
    elif current_OS == "Linux":
        try:
            subprocess.run(["xdg-open", str(script)], check=True)
        except Exception as e:
            print(f"Could not open File Explorer, an error occurred: {e}")
