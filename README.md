# Professional Firmware for the Voxelab Aquila and Creality Ender-3 3D Printers <br> **_<sup><sup><sub>(Or any other compatible 3D Printer)</sub></sup></sup>_**

![GitHub Release Date](https://img.shields.io/github/release-date/classicrocker883/MRiscoCProUI.svg)  
![CI Unit Status](https://github.com/classicrocker883/MRiscoCProUI/actions/workflows/ci-unit-tests.yml/badge.svg)  
![CI Build Status](https://github.com/classicrocker883/MRiscoCProUI/actions/workflows/ci-build-tests.yml/badge.svg)  
[![Aquila Build](https://github.com/classicrocker883/MRiscoCProUI/actions/workflows/compile-configs.yml/badge.svg?event=release)](https://github.com/classicrocker883/MRiscoCProUI/releases/latest)  
![HC32 Build](https://github.com/classicrocker883/MRiscoCProUI/actions/workflows/compile-configs-HC32.yml/badge.svg)  
![Ender Build](https://github.com/classicrocker883/MRiscoCProUI/actions/workflows/compile-configs_Ender.yml/badge.svg)

### Visit the [Wiki](https://github.com/classicrocker883/MRiscoCProUI/wiki) for more information about *this* firmware and the features it provides

<br>

**Don't forget to checkout the [thingiverse](https://www.thingiverse.com/classicrocker883/designs) models I've designed:**

[Minimalist Dual Cooling Fan Shroud](https://www.thingiverse.com/thing:5263939) for Aquila / Ender 3 V2
<img src="https://cdn.thingiverse.com/assets/1a/21/e9/e9/f5/card_preview_c60b15d6-69cf-469a-8641-40f6bef37992.png" style="float:left;width:40px;height:40px;" align="left"/>

[Tool Box for Middle Extrusion](https://www.thingiverse.com/thing:5181522) "**VOXELAB**" engraved
<img src="https://cdn.thingiverse.com/assets/39/e7/eb/bd/9f/card_preview_Voxelab_WideMiddle_Shell.png" style="float:left;width:40px;height:40px;" align="left"/>

[Fantastic Filament Guide](https://www.thingiverse.com/thing:4974802) for Aquila
<img src="https://cdn.thingiverse.com/assets/46/79/c1/80/14/card_preview_FantasticFilamentGuideAquilaL.png" style="float:left;width:40px;height:40px;" align="left"/>

[Raspberry Pi Zero Case Mount 30mm case width](https://www.thingiverse.com/thing:5166780) for Aquila
<img src="https://cdn.thingiverse.com/assets/73/1e/84/38/f1/card_preview_Pi_Zero_Case_holder.png" style="float:left;width:40px;height:40px;" align="left"/>

---

## Universal Firmware for RET6/RCT6 chips: G32, N32, H32, Creality 4.2.7 and 4.2.2 boards <br> **_<sup><sup><sub>(Also available for BTT SKR Mini E3 and others)</sub></sup></sup>_**

### - Please read this: -
> [!NOTE]
Many Updates have been included in the most recent MRiscoCProUI for the **2025-May** release.
This release has many changes to the **UI**.
New ICON's have been added, and old ones enhanced. Whoever edited them before saved directly as .*JPG* which in many editors lowers the quality of the image. I painstakingly remastered almost every single one; preserving the original quality.
>
> > You must [REFLASH](https://github.com/classicrocker883/MRiscoCProUI/wiki/HOW-TO-UPDATE-THE-DISPLAY) the *LCD Display* with the new **DWIN_SET**; which is located in the `display assets` folder.
>
> If you encounter any issues, have a suggestion, or feature requests please feel free to post it on the [Issues tab](https://github.com/classicrocker883/MRiscoCProUI/issues), otherwise if everything is going well please leave a comment on the [Discussions tab](https://github.com/classicrocker883/MRiscoCProUI/discussions).
>
> I will be working on more upgrades and features and tweaks along the way. Enjoy using this fork of Marlin as I intend it to be the best; easy to use and convenient. So far I really enjoy the new settings and toolbar for the main menu. There is a variety of parameters and options that can be changed without having to reflash the firmware.

> [!TIP]
> If you start printing and it says `Advance Pause` while **Runout** is enabled, you may have to change state it triggers no filament to **HIGH**, or **LOW** (depending on what is already selected). This is found in the _Prepare_ menu/ _Filament Management_/ _Filament Settings_ -> _Runout Active_.

<br>

#### Important Info regarding HC32:
> [!WARNING]
>
> <ins>**FOREWARNING**</ins>: So far everything has been working great - as normal - except there is an issue with the initialization of the SD card media. If you get a message saying this has failed, just reinsert the card or reboot. Keep trying if this doesn't work the first time. Also using Gcode Thumbnail Preview is giving issues with freezing so this has been disabled for now.

> [!CAUTION]
>
> *G-code Thumbnail Preview* has been disabled for HC32 boards for the time being.  
> When enabled, the screen may **freeze and restart** when the SD card is inserted. This means that everything *so far* seems to work correctly as it should, except for when an **SD card is inserted**, so printing may not be possible *unless* you use USB serial interface to upload the file (through a slicer or something like OctoPrint, or Pronterface).

> [!NOTE]
> H32->HC32 support has been added to the [Marlin Firmware](https://github.com/MarlinFirmware/Marlin) repository. Please post any [Issues](https://github.com/MarlinFirmware/Marlin/issues) there first, otherwise if there are any ProUI specific issues or anything else to report please do so under [Issues tab](https://github.com/classicrocker883/MRiscoCProUI/issues) here. You can find the original HC32 repo here [@shadow578/Marlin-H32](https://github.com/shadow578/Marlin-H32)

<br>

#### Other Information:
General information about the firmware and updates is located in the _Wiki_ page [What's New In This Release](https://github.com/classicrocker883/MRiscoCProUI/wiki/What's-New-in-this-Release). <br>
Other changes and updates are [addressed here](https://github.com/classicrocker883/MRiscoCProUI/releases/latest).

- [LA - Linear Advance](https://marlinfw.org/docs/features/lin_advance.html)
- [MPC - Model Predictive Temperature Control](https://marlinfw.org/docs/features/model_predictive_control.html)
- [IS - Input Shaping](https://marlinfw.org/docs/features/input_shaping.html)
- [Firmware Retract](https://marlinfw.org/docs/features/fwretract.html)


<br>

### MarlinSimulator Instructions
There is a *MarlinSimulator* file provided to test out for yourself. It simulates a pre-built configuration of this firmware.

The *MarlinSimulator* can only compile for Manual Mesh Bed Leveling for now, so make sure your configuration is set for `MESH_BED_LEVELING`.  
To create *MarlinSimulator* with your own build, start in **Configuration.h** and change the `MOTHERBOARD` to `BOARD_SIMULATED`, then disable `ENDSTOP_INTERRUPTS_FEATURE` and `PROUI_EX`.  
You may need to change `#define INVERT_E0_DIR HMI_data.Invert_E0` to `#define INVERT_E0_DIR false` (or comment it and `#undef INVERT_E0_DIR` out) in **dwin_defines.h**. 
Then in **platformio.ini** change to `simulator_windows` in `default_envs =` (for Windows) / `simulator_linux_release` `default_envs =` (for Linux).  
If there is an error, add `-fno-lto` to `build_flags =` in **native.ini**.
For MacOS you're on your own...sorry.

Then you have to extract **SDL2-devel-2.32.2-mingw.zip** from /**docs**.  
Or for the latest releast go to [libsdl-org/SDL/releases](https://github.com/libsdl-org/SDL/releases) and look for the latest **SDL2** version (**NOT** *SDL3*)  
You can *either* copy/paste the files directly, or install them.  
It's recommended to install them, but if you have any issues, then try copy/paste method.

#### Install Files (Windows)
Navigate to the extracted SDL2 directory in an *MSYS2* or *bash* terminal (Run as Administrator):

To install SDL for native (32-bit) development:
>     make native

To install SDL for cross-compiling development:
>     make cross

It's recommended to do both `make native` and `make cross`.

For 64-bit - If you receive an error, then try the following:
>     make install-package arch=x86_64-w64-mingw32 prefix=/usr

#### Alternative SDL2 Install
**Copy/Paste Files**  
You may have to first Build so the directory can be created, but you can:  
- **Copy** the contents of ~\SDL2-2.32.2\x86_64-w64-mingw32\include\SDL2\\*, paste into the directory ~\.pio\libdeps\simulator_windows\\**imgui**  

-OR-  

- **Copy** the just folder ~\SDL2-2.32.2\x86_64-w64-mingw32\include\\**SDL2**, paste into the directory ~\.pio\libdeps\\*simulator_windows*

Once all that is done, just Build like you would normally and *MarlinSimulator.exe* will be created.

#### Install Files (Linux)
These are the files you need to install:  
`sudo apt install libsdl2 libsdl2-dev libsdl2-net-dev libsdl2-2.0-0 libglm-dev`  
- There may be other basic ones if you don't have already; like python, cmake, pip...

#### Using MarlinSimulator
- Under `SD Card`, under `Components` on the right side, select or load an image
- Select Serial Monitor(1)
- Use like a normal terminal, enter `G28` to watch it Home

<br>

### Printer Information
The Precompiled binary files of this firmware can work with STM32 (STM32F103RET6/RCT6 - STMicroelectronics) and it's clones: G32 (GD32F103Rx - GigaDevice), N32 (N32F103Rx / N32G455x - Nation), and H32 (HC32F460x - Huada Semiconductor/HDSC). They can be downloaded from:
[Latest Release](https://github.com/classicrocker883/MRiscoCProUI/releases/latest)

<br>

<img height=260 src="https://enfss.voxelab3dp.com/10001/picture/2021/09/b849845bd0ffa889f00a782aae76ccf3.jpg" align="left" /><p>
<img height=260 src="https://enfss.voxelab3dp.com/10001/picture/2021/09/677b721574efca3daa5c0d39e438fee6.jpg" align="middle" /><p>
<img height=260 src="buildroot/share/pixmaps/Ender-3V2.jpg" align="left" /><p>
<img width=260.5 src="buildroot/share/pixmaps/Ender-3S1.jpg" align="middle"  />

<br>

## Donations
Thank you for your support.  
Please consider making a donation, as large or as small and as often as you'd like.  
[Ko-fi](https://ko-fi.com/classicrocker883)  
[Venmo](https://venmo.com/u/andrewleduc88)  
[Paypal](https://www.paypal.com/paypalme/andrewleduc) - **Single payment**

[<img src="https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif">](https://www.paypal.com/donate/?business=PFNSKQX9WQQ8W&no_recurring=0&currency_code=USD)  **PayPal - Monthly Payment**

<br>

## Wiki
 - [How to install the firmware](https://github.com/classicrocker883/MRiscoCProUI/wiki/How-to-install-the-firmware)
 - [Installing a 3D/BLTouch](https://github.com/classicrocker883/MRiscoCProUI/wiki/3D-BLTouch)
 - [Color themes](https://github.com/classicrocker883/MRiscoCProUI/wiki/Color-Themes)
 - [How to use with Octoprint](https://github.com/classicrocker883/MRiscoCProUI/wiki/Octoprint)

<br>

## Community links
* [Voxelab Aquila Facebook Group](https://www.facebook.com/groups/voxelabaquila/?ref=share&mibextid=NSMWBT)
* [Telegram](https://t.me/ender3v2s1firmware)
* [r/VoxelabAquila on Reddit](https://www.reddit.com/r/VoxelabAquila)
* [r/ender3V2 on Reddit](https://www.reddit.com/r/ender3v2)
* [r/Ender3v2Firmware on Reddit](https://www.reddit.com/r/Ender3v2Firmware)
* [E3V2 Facebook](https://www.facebook.com/groups/ender3v2firmware)
* [E3S1 Facebook](https://www.facebook.com/groups/ender3s1printer)

<!--[](https://raw.githubusercontent.com/mriscoc/Ender3V2S1/Ender3V2S1-Released/screenshots/main.jpg)-->

<br>

## Marlin Support
The Issue Queue is reserved for Bug Reports and Feature Requests. Please use the following resources for help with configuration and troubleshooting:

- [Marlin Documentation](//marlinfw.org) - Official Marlin documentation
- [Marlin Discord](//discord.com/servers/marlin-firmware-461605380783472640) - Discuss issues with Marlin users and developers
- Facebook Group ["Marlin Firmware"](//www.facebook.com/groups/1049718498464482/)
- RepRap.org [Marlin Forum](//forums.reprap.org/list.php?415)
- Facebook Group ["Marlin Firmware for 3D Printers"](//www.facebook.com/groups/3Dtechtalk/)
- [Marlin Configuration](//www.youtube.com/results?search_query=marlin+configuration) on YouTube

<br>

## Credits
Thanks to Reddit u/schuh8 and GitHub @whasupjohn for donating his board to help test the firmware.
<p>
<details>
  <summary>Find me</summary>
On <a href="https://www.facebook.com/yoboyyy">Facebook</a>

On Reddit: u/<b>In*Us*2</b>
</details>
</p>

Join the Voxelab Aquila [Facebook Group](https://www.facebook.com/groups/voxelabaquila/)

This fork of MRiscoC's Professional Firmware is maintained by [@classicrocker883](https://github.com/classicrocker883) (yours truly)

ProUI is a Marlin based firmware maintained by [@mriscoc](https://github.com/mriscoc)

The fork for H32|HC32 firmware is maintained by [@shadow578](https://github.com/shadow578)

Marlin is maintained mainly by [@thinkyhead](https://github.com/thinkyhead)

<br>

## Star History
<a id="starchart" href="https://star-history.com/#classicrocker883/MRiscoCProUI&Date">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="https://api.star-history.com/svg?repos=classicrocker883/MRiscoCProUI&type=Date&theme=dark" />
    <source media="(prefers-color-scheme: light)" srcset="https://api.star-history.com/svg?repos=classicrocker883/MRiscoCProUI&type=Date" />
    <img height=320 alt="Star History Chart" src="https://api.star-history.com/svg?repos=classicrocker883/MRiscoCProUI&type=Date" />
  </picture>
</a>

This work would not be possible without me spending time working on it for free.

I would greatly appreciate supporters, helpers, and beta testers whenever possible.

Please show your support by considering making a donation, or giving your input if you end up using this firmware.

It wasn't easy getting it to this point. I am just a basic programmer and the work is mostly trial and error.  
Thank goodness for VS Code's compiler and also AI like ChatGPT which shows me what changes need to be made as I make them.

- [Marlin Firmware](https://marlinfw.org/) is an Open Source project and owned and maintained by the maker community.
- VS Code is an IDE program owned and maintained by Microsoft.

<br>

## Disclaimer
THIS FIRMWARE AND ALL OTHER FILES IN THE DOWNLOAD ARE PROVIDED FREE OF CHARGE WITH NO WARRANTY OR GUARANTEE. SUPPORT IS NOT INCLUDED JUST BECAUSE YOU DOWNLOADED THE FIRMWARE. WE ARE NOT LIABLE FOR ANY DAMAGE TO YOUR PRINTER, PERSON, OR ANY OTHER PROPERTY DUE TO USE OF THIS FIRMWARE. IF YOU DO NOT AGREE TO THESE TERMS THEN DO NOT USE THE FIRMWARE.

<br>

## LICENSE
For the license, check the header of each file, if the license is not specified there, the project license will be used. Marlin is licensed under the GPL.
