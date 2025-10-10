/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include "../DGUSDisplayDef.h"



  enum Screen_t   : uint8_t  {Screen_null,Screen_control,Screen_print,Screen_abort,Screen_pause};
  enum language_t : uint8_t { CHS = 1,EHG = 2,ESP = 3,FRA = 4,DEU = 5,PYC = 6};
  typedef struct _lcd_info_t {
    language_t       language;
    Screen_t         Screen_now;
    uint8_t          fil_runout_flag;
    uint8_t          level_flag;
    uint8_t          reach_flag;
    uint8_t          set_hoted_flag;
    uint8_t          level_pos = 0;
    uint8_t          level_start = 0;
    uint8_t          beep_flag;
    uint8_t          sdremove_flag = 1;
    uint8_t          load_flag;
    uint8_t          unload_flag;
    uint16_t         preheat_abs_hoted = 230;
    uint16_t         preheat_abs_bed = 80;
    uint16_t         preheat_pla_hoted = 200 ;
    uint16_t         preheat_pla_bed = 60;
    uint32_t         reach_cnt;
  } lcd_info_t;
extern lcd_info_t lcd_info;

// enum DGUSLCD_Screens : uint8_t {
//   DGUSLCD_SCREEN_BOOT                =   0,
//   DGUSLCD_SCREEN_MAIN                =  1,
//   DGUSLCD_SCREEN_TEMPERATURE         =  2,
//   DGUSLCD_SCREEN_STATUS              =  3,
//   DGUSLCD_SCREEN_STATUS2             =  4,
//   DGUSLCD_SCREEN_MANUALMOVE          =  5,
//   DGUSLCD_SCREEN_MANUALEXTRUDE       =  6,
//   DGUSLCD_SCREEN_FANANDFEEDRATE      =  7,
//   DGUSLCD_SCREEN_FLOWRATES           =  8,
//   DGUSLCD_SCREEN_SDFILELIST          =  9,
//   DGUSLCD_SCREEN_SDPRINTMANIPULATION =  10,
//   DGUSLCD_SCREEN_POWER_LOSS          = 11,
//   DGUSLCD_SCREEN_PREHEAT             = 12,
//   DGUSLCD_SCREEN_UTILITY             = 13,
//   DGUSLCD_SCREEN_FILAMENT_HEATING    = 14,
//   DGUSLCD_SCREEN_FILAMENT_LOADING    = 15,
//   DGUSLCD_SCREEN_FILAMENT_UNLOADING  = 16,
//   DGUSLCD_SCREEN_SDPRINTTUNE         = 17,
//   DGUSLCD_SCREEN_CONFIRM             = 18,
//   DGUSLCD_SCREEN_KILL                = 19, ///< Kill Screen. Must always be 250 (to be able to display "Error wrong LCD Version")
//   DGUSLCD_SCREEN_WAITING             = 20,
//   DGUSLCD_SCREEN_POPUP               = 21, ///< special target, popup screen will also return this code to say "return to previous screen"
//   DGUSLCD_SCREEN_UNUSED              = 22
// };
enum DGUSLCD_Screens : uint8_t {
  DGUSLCD_SCREEN_BOOT                 =  0,

  DGUSLCD_SCREEN_SDFILELIST           =  1,
  DGUSLCD_SCREEN_CONTROL              =  2,
  DGUSLCD_SCREEN_PREPARE              =  3,
  DGUSLCD_SCREEN_INFO                 =  4,
  DGUSLCD_SCREEN_PRINTING             =  5,
  DGUSLCD_SCREEN_MOVEAXIS             =  6,
  DGUSLCD_SCREEN_LOAD                 =  7,
  DGUSLCD_SCREEN_LOAD_1               =  8,
  DGUSLCD_SCREEN_NULL                 =  9,
  DGUSLCD_SCREEN_TEMPERTURE           =  10,
  DGUSLCD_SCREEN_MOVE                 =  11,
  DGUSLCD_SCREEN_MAXSPEED             =  12,
  DGUSLCD_SCREEN_MAXACCE              =  13,
  DGUSLCD_SCREEN_UNLOAD_1             =  14,
  DGUSLCD_SCREEN_STEP                 =  15,
  DGUSLCD_SCREEN_CONTROL_1            =  16,
  DGUSLCD_SCREEN_LEVEL                =  17,
  DGUSLCD_SCREEN_TUNE                 =  18,
  DGUSLCD_SCREEN_SET_PLA              =  19,
  DGUSLCD_SCREEN_SET_ABS              =  20,
  DGUSLCD_SCREEN_OFFSET_Z             =  21,
  DGUSLCD_SCREEN_PREPARE_1            =  26,
  DGUSLCD_SCREEN_LANGUAGE_CN          =  27,
  DGUSLCD_SCREEN_GOHOME               =  28,
  // DGUSLCD_SCREEN_ABORT_FILE           =  33,
  DGUSLCD_SCREEN_POWER_LOSS           =  33,
  DGUSLCD_SCREEN_MAIN                 =  34,
  DGUSLCD_SCREEN_FIL_PAUSE            =  35,

  DGUSLCD_SCREEN_UNLOAD               =  37,

  DGUSLCD_SCREEN_EN_MAIN              =  40,
  DGUSLCD_SCREEN_EN_SDFILELIST        =  41,
  DGUSLCD_SCREEN_EN_CONTROL           =  42,
  DGUSLCD_SCREEN_EN_PREPARE           =  43,
  DGUSLCD_SCREEN_EN_INFO              =  44,
  DGUSLCD_SCREEN_EN_PRINTING          =  45,
  DGUSLCD_SCREEN_EN_MOVEAXIS          =  46,
  DGUSLCD_SCREEN_EN_LOAD              =  47,
  DGUSLCD_SCREEN_EN_LOAD_1            =  48,
  DGUSLCD_SCREEN_EN_OFFSET_Z          =  49,
  DGUSLCD_SCREEN_EN_TEMPERTURE        =  50,
  DGUSLCD_SCREEN_EN_MAXSPEED          =  52,
  DGUSLCD_SCREEN_EN_MAXACCE           =  53,
  DGUSLCD_SCREEN_EN_STEP              =  54,
  DGUSLCD_SCREEN_EN_UNLOAD            =  55,
  DGUSLCD_SCREEN_EN_CONTROL_1         =  56,
  DGUSLCD_SCREEN_EN_LEVEL             =  57,
  DGUSLCD_SCREEN_EN_TUNE              =  58,
  DGUSLCD_SCREEN_EN_OFFSET_Z_1        =  61,
  DGUSLCD_SCREEN_LANGUAGE_EN          =  63,
  DGUSLCD_SCREEN_LANGUAGE_EN_1        =  65,
  DGUSLCD_SCREEN_EN_POWER_LOSS        =  69,
  DGUSLCD_SCREEN_EN_UNLOAD_1          =  73,



  DGUSLCD_SCREEN_ES_MAIN              =  75,
  DGUSLCD_SCREEN_ES_SDFILELIST        =  76,
  DGUSLCD_SCREEN_ES_CONTROL           =  77,
  DGUSLCD_SCREEN_ES_PREPARE           =  78,
  DGUSLCD_SCREEN_ES_INFO              =  79,
  DGUSLCD_SCREEN_ES_PRINTING          =  80,
  DGUSLCD_SCREEN_ES_MOVEAXIS          =  81,
  DGUSLCD_SCREEN_ES_LOAD              =  82,
  DGUSLCD_SCREEN_ES_LOAD_1            =  83,
  DGUSLCD_SCREEN_ES_OFFSET_Z          =  84,
  DGUSLCD_SCREEN_ES_TEMPERTURE        =  85,
  DGUSLCD_SCREEN_ES_MAXSPEED          =  87,
  DGUSLCD_SCREEN_ES_MAXACCE           =  88,
  DGUSLCD_SCREEN_ES_UNLOAD_1          =  89,
  DGUSLCD_SCREEN_ES_STEP              =  90,
  DGUSLCD_SCREEN_ES_CONTROL_1         =  91,
  DGUSLCD_SCREEN_ES_LEVEL             =  92,
  DGUSLCD_SCREEN_ES_TUNE              =  93,
  DGUSLCD_SCREEN_ES_OFFSET_Z_1        =  96,
  DGUSLCD_SCREEN_ES_PREPARE_1         =  99,
  DGUSLCD_SCREEN_LANGUAGE_ES          =  100,
  DGUSLCD_SCREEN_ES_POWER_LOSS        =  106,
  DGUSLCD_SCREEN_ES_UNLOAD            =  109,



  DGUSLCD_SCREEN_FR_MAIN              =  115,
  DGUSLCD_SCREEN_FR_SDFILELIST        =  116,
  DGUSLCD_SCREEN_FR_CONTROL           =  117,
  DGUSLCD_SCREEN_FR_PREPARE           =  118,
  DGUSLCD_SCREEN_FR_INFO              =  119,
  DGUSLCD_SCREEN_FR_PRINTING          =  120,
  DGUSLCD_SCREEN_FR_MOVEAXIS          =  121,
  DGUSLCD_SCREEN_FR_LOAD              =  122,
  DGUSLCD_SCREEN_FR_LOAD_1            =  123,
  DGUSLCD_SCREEN_FR_OFFSET_Z_1        =  124,
  DGUSLCD_SCREEN_FR_TEMPERTURE        =  125,
  DGUSLCD_SCREEN_FR_MAXSPEED          =  127,
  DGUSLCD_SCREEN_FR_MAXACCE           =  128,
  DGUSLCD_SCREEN_FR_STEP              =  129,
  DGUSLCD_SCREEN_FR_CONTROL_1         =  130,
  DGUSLCD_SCREEN_FR_LEVEL             =  131,
  DGUSLCD_SCREEN_FR_TUNE              =  132,
  DGUSLCD_SCREEN_FR_OFFSET_Z          =  135,
  DGUSLCD_SCREEN_LANGUAGE_FR          =  137,
  DGUSLCD_SCREEN_FR_POWER_LOSS        =  145,
  DGUSLCD_SCREEN_FR_UNLOAD            =  147,
  DGUSLCD_SCREEN_FR_UNLOAD_1          =  148,


  DGUSLCD_SCREEN_DE_MAIN              =  150,
  DGUSLCD_SCREEN_DE_SDFILELIST        =  151,
  DGUSLCD_SCREEN_DE_CONTROL           =  152,
  DGUSLCD_SCREEN_DE_PREPARE           =  153,
  DGUSLCD_SCREEN_DE_INFO              =  154,
  DGUSLCD_SCREEN_DE_PRINTING          =  155,
  DGUSLCD_SCREEN_DE_MOVEAXIS          =  156,
  DGUSLCD_SCREEN_DE_LOAD              =  157,
  DGUSLCD_SCREEN_DE_LOAD_1            =  158,
  DGUSLCD_SCREEN_DE_OFFSET_Z_1        =  159,
  DGUSLCD_SCREEN_DE_TEMPERTURE        =  160,
  DGUSLCD_SCREEN_DE_MAXSPEED          =  162,
  DGUSLCD_SCREEN_DE_MAXACCE           =  163,
  DGUSLCD_SCREEN_DE_STEP              =  165,
  DGUSLCD_SCREEN_DE_CONTROL_1         =  166,
  DGUSLCD_SCREEN_DE_LEVEL             =  167,
  DGUSLCD_SCREEN_DE_TUNE              =  168,
  DGUSLCD_SCREEN_DE_OFFSET_Z          =  171,
  DGUSLCD_SCREEN_LANGUAGE_DE          =  174,
  DGUSLCD_SCREEN_DE_POWER_LOSS        =  180,
  DGUSLCD_SCREEN_DE_UNLOAD            =  183,
  DGUSLCD_SCREEN_DE_UNLOAD_1          =  184,


  DGUSLCD_SCREEN_PY_MAIN              =  190,
  DGUSLCD_SCREEN_PY_SDFILELIST        =  191,
  DGUSLCD_SCREEN_PY_CONTROL           =  192,
  DGUSLCD_SCREEN_PY_PREPARE           =  193,
  DGUSLCD_SCREEN_PY_INFO              =  194,
  DGUSLCD_SCREEN_PY_PRINTING          =  195,
  DGUSLCD_SCREEN_PY_MOVEAXIS          =  196,
  DGUSLCD_SCREEN_PY_LOAD              =  197,
  DGUSLCD_SCREEN_PY_LOAD_1            =  198,
  DGUSLCD_SCREEN_PY_OFFSET_Z_1        =  199,
  DGUSLCD_SCREEN_PY_TEMPERTURE        =  200,
  DGUSLCD_SCREEN_PY_MAXSPEED          =  202,
  DGUSLCD_SCREEN_PY_MAXACCE           =  203,
  DGUSLCD_SCREEN_PY_STEP              =  204,
  DGUSLCD_SCREEN_PY_CONTROL_1         =  205,
  DGUSLCD_SCREEN_PY_LEVEL             =  206,
  DGUSLCD_SCREEN_PY_TUNE              =  207,
  DGUSLCD_SCREEN_PY_OFFSET_Z          =  210,
  DGUSLCD_SCREEN_LANGUAGE_PY          =  212,
  DGUSLCD_SCREEN_PY_UNLOAD            =  220,
  DGUSLCD_SCREEN_PY_UNLOAD_1          =  221,
  DGUSLCD_SCREEN_PY_POWER_LOSS        =  222,

  DGUSLCD_SCREEN_CONFIRM              =  240

  };
// Display Memory layout used (T5UID)
// Except system variables this is arbitrary, just to organize stuff....

// 0x0000 .. 0x0FFF  -- System variables and reserved by the display
// 0x1000 .. 0x1FFF  -- Variables to never change location, regardless of UI Version
// 0x2000 .. 0x2FFF  -- Controls (VPs that will trigger some action)
// 0x3000 .. 0x4FFF  -- Marlin Data to be displayed
// 0x5000 ..         -- SPs (if we want to modify display elements, e.g change color or like) -- currently unused

// As there is plenty of space (at least most displays have >8k RAM), we do not pack them too tight,
// so that we can keep variables nicely together in the address space.

// UI Version always on 0x1000...0x1002 so that the firmware can check this and bail out.
// constexpr uint16_t VP_UI_VERSION_MAJOR = 0x1000;  // Major -- incremented when incompatible
// constexpr uint16_t VP_UI_VERSION_MINOR = 0x1000;  // Minor -- incremented on new features, but compatible
// constexpr uint16_t VP_UI_VERSION_PATCH = 0x1002;  // Patch -- fixed which do not change functionality.
// constexpr uint16_t VP_UI_FLAVOUR       = 0x3010;  // lets reserve 16 bytes here to determine if UI is suitable for this Marlin. tbd.

// Storage space for the Killscreen messages. 0x1100 - 0x1200 . Reused for the popup.
constexpr uint16_t VP_MSGSTR1 = 0x1100;
constexpr uint8_t VP_MSGSTR1_LEN = 0x20;  // might be more place for it...
constexpr uint16_t VP_MSGSTR2 = 0x1140;
constexpr uint8_t VP_MSGSTR2_LEN = 0x20;
constexpr uint16_t VP_MSGSTR3 = 0x1180;
constexpr uint8_t VP_MSGSTR3_LEN = 0x20;
constexpr uint16_t VP_MSGSTR4 = 0x11C0;
constexpr uint8_t VP_MSGSTR4_LEN = 0x20;

// Screenchange request for screens that only make sense when printer is idle.
// e.g movement is only allowed if printer is not printing.
// Marlin must confirm by setting the screen manually.
constexpr uint16_t VP_SCREENCHANGE_ASK = 0x1000;
constexpr uint16_t VP_SCREENCHANGE = 0x1001;   // Key-Return button to new menu pressed. Data contains target screen in low byte and info in high byte.
constexpr uint16_t VP_TEMP_ALL_OFF = 0x1002;   // Turn all heaters off. Value arbitrary ;)=
constexpr uint16_t VP_SCREENCHANGE_WHENSD = 0x1003; // "Print" Button touched -- go only there if there is an SD Card.

constexpr uint16_t VP_CONFIRMED = 0x5010; // OK on confirm screen.



// Controls for movement (we can't use the incremental / decremental feature of the display at this feature works only with 16 bit values
// (which would limit us to 655.35mm, which is likely not a problem for common setups, but i don't want to rule out hangprinters support)
// A word about the coding: The VP will be per axis and the return code will be an signed 16 bit value in 0.01 mm resolution, telling us
// the relative travel amount t he user wants to do. So eg. if the display sends us VP=2100 with value 100, the user wants us to move X by +1 mm.

//constexpr uint16_t VP_MOVE_E2 = 0x2114;
//constexpr uint16_t VP_MOVE_E3 = 0x2116;
//constexpr uint16_t VP_MOVE_E4 = 0x2118;
//constexpr uint16_t VP_MOVE_E5 = 0x211A;
// constexpr uint16_t VP_AXIS_MOVE_BUTTON = 0x2006;
constexpr uint16_t VP_HOME_BUTTON = 0x2000; // 2 Byte Integer4

constexpr uint16_t VP_BEEP_LOCK_UNLOK  =0X2005;
constexpr uint16_t   VP_CHECK_FIL_BUTTON = 0x2006;
constexpr uint16_t VP_MOTOR_LOCK_UNLOK = 0x2007;
constexpr uint16_t VP_HOME_ALL = 0x2008;
constexpr uint16_t VP_LEVEL_BUTTON = 0X2009;
constexpr uint16_t VP_PLA_BUTTON = 0X200A;
constexpr uint16_t VP_ABS_BUTTON = 0X200B;
constexpr uint16_t VP_LOAD_BUTTON = 0X200C;
constexpr uint16_t VP_UNLOAD_BUTTON = 0X200D;
constexpr uint16_t VP_COOLDOWN_BUTTON = 0X200E;
constexpr uint16_t VP_SETTING_FACTORY_BUTTON = 0X200F;

constexpr uint16_t VP_MOVE_X_Positive_BUTTON = 0x2016; // 2 Byte Integer4
constexpr uint16_t VP_MOVE_X_Negative_BUTTON = 0x2015; // 2 Byte Integer4
constexpr uint16_t VP_MOVE_Y_Positive_BUTTON = 0x2018; // 2 Byte Integer4
constexpr uint16_t VP_MOVE_Y_Negative_BUTTON = 0x2017; // 2 Byte Integer4
constexpr uint16_t VP_MOVE_Z_Positive_BUTTON = 0x2019; // 2 Byte Integer4
constexpr uint16_t VP_MOVE_Z_Negative_BUTTON = 0x201A; // 2 Byte Integer4


constexpr uint16_t VP_X_AXIS_coordinate  = 0x3230;
constexpr uint16_t VP_Y_AXIS_coordinate  = 0x3234;
constexpr uint16_t VP_Z_AXIS_coordinate  = 0x3238;

constexpr uint16_t VP_Z_OFFSET_BUTTON =0X2020;

constexpr uint16_t VP_SETTING_LANG_BUTTON   = 0X2300;


constexpr uint16_t VP_PREPARE_PLA_HOTED_BUTTON   = 0X2304;
constexpr uint16_t VP_PREPARE_PLA_BED_BUTTON   = 0X2308;
constexpr uint16_t VP_PREPARE_ABS_HOTED_BUTTON   = 0X230C;
constexpr uint16_t VP_PREPARE_ABS_BED_BUTTON   = 0X2310;

// Power loss recovery
constexpr uint16_t VP_POWER_LOSS_RECOVERY = 0x4180;

// Fan Control Buttons , switch between "off" and "on"

//constexpr uint16_t VP_FAN2_CONTROL = 0x2204;
//constexpr uint16_t VP_FAN3_CONTROL = 0x2206;

// Heater Control Buttons , triged between "cool down" and "heat PLA" state
constexpr uint16_t VP_E0_CONTROL = 0x2200;

//constexpr uint16_t VP_E2_CONTROL = 0x2214;
//constexpr uint16_t VP_E3_CONTROL = 0x2216;
//constexpr uint16_t VP_E4_CONTROL = 0x2218;
//constexpr uint16_t VP_E5_CONTROL = 0x221A;
constexpr uint16_t VP_BED_CONTROL = 0x2204;

// Preheat

//constexpr uint16_t VP_E2_BED_CONTROL = 0x2224;
//constexpr uint16_t VP_E3_BED_CONTROL = 0x2226;
//constexpr uint16_t VP_E4_BED_CONTROL = 0x2228;
//constexpr uint16_t VP_E5_BED_CONTROL = 0x222A;

// Filament load and unload

// Settings store , reset
constexpr uint16_t VP_SETTINGS = 0x4400;

// PID autotune


// Firmware version on the boot screen.
constexpr uint16_t VP_MARLIN_VERSION = 0x3450;
constexpr uint8_t VP_MARLIN_VERSION_LEN = 16;   // there is more space on the display, if needed.

constexpr uint16_t VP_MachineName = 0x3410;
constexpr uint8_t VP_MachineName_LEN = 16;   // there is more space on the display, if needed.

constexpr uint16_t VP_PRINTSIZE = 0x3430;
constexpr uint8_t VP_PRINTSIZE_LEN = 16;   // there is more space on the display, if needed.

constexpr uint16_t VP_Web = 0x3470;
constexpr uint8_t VP_WEB_LEN = 24;   // there is more space on the display, if needed.

constexpr uint16_t VP_Email = 0x3490;
constexpr uint8_t VP_EMAIL_LEN = 32;   // there is more space on the display, if needed.

// Place for status messages.
constexpr uint16_t VP_M117 = 0x3020;
constexpr uint8_t VP_M117_LEN = 0x20;

// Temperatures.
constexpr uint16_t VP_T_E0_Is = 0x3002;  // 4 Byte Integer
constexpr uint16_t VP_T_E0_Set = 0x3042; // 2 Byte Integer

constexpr uint16_t VP_Tune_E0_Set = 0x224C; // 2 Byte Integer
constexpr uint16_t VP_Tune_BED_Set = 0x2250; // 2 Byte Integer
constexpr uint16_t VP_Tune_FAN_Set = 0x2254; // 2 Byte Integer
// constexpr uint16_t VP_T_E1_Is = 0x3364;  // 4 Byte Integer

// reserved to support up to 6 Extruders:
//constexpr uint16_t VP_T_E1_Set = 0x3066; // 2 Byte Integer
//constexpr uint16_t VP_T_E2_Is = 0x3068;  // 4 Byte Integer
//constexpr uint16_t VP_T_E2_Set = 0x306A; // 2 Byte Integer
//constexpr uint16_t VP_T_E3_Is = 0x306C;  // 4 Byte Integer
//constexpr uint16_t VP_T_E3_Set = 0x306E; // 2 Byte Integer
//constexpr uint16_t VP_T_E4_Is = 0x3070;  // 4 Byte Integer
//constexpr uint16_t VP_T_E4_Set = 0x3072; // 2 Byte Integer
//constexpr uint16_t VP_T_E4_Is = 0x3074;  // 4 Byte Integer
//constexpr uint16_t VP_T_E4_Set = 0x3076; // 2 Byte Integer
//constexpr uint16_t VP_T_E5_Is = 0x3078;  // 4 Byte Integer
//constexpr uint16_t VP_T_E5_Set = 0x307A; // 2 Byte Integer

constexpr uint16_t VP_T_Bed_Is = 0x3004;  // 4 Byte Integer
constexpr uint16_t VP_T_Bed_Set = 0x3044; // 2 Byte Integer

constexpr uint16_t VP_Flowrate_E0 = 0x3090; // 2 Byte Integer
constexpr uint16_t VP_Flowrate_E1 = 0x3092; // 2 Byte Integer

// reserved for up to 6 Extruders:
//constexpr uint16_t VP_Flowrate_E2 = 0x3094;
//constexpr uint16_t VP_Flowrate_E3 = 0x3096;
//constexpr uint16_t VP_Flowrate_E4 = 0x3098;
//constexpr uint16_t VP_Flowrate_E5 = 0x309A;



constexpr uint16_t VP_CANCEL_BUTTON = 0X2FF0;

constexpr uint16_t VP_PAUSE_BUTTON = 0X2004;



// constexpr uint16_t VP_INPUT_BUTTON = 0x200A; // 2 Byte Integer4





constexpr uint16_t VP_MOVE_DIS_A_BUTTON = 0x4507; // 2 Byte Integer4
constexpr uint16_t VP_MOVE_DIS_B_BUTTON = 0x4508; // 2 Byte Integer4
constexpr uint16_t VP_MOVE_DIS_C_BUTTON = 0x4509; // 2 Byte Integer4



// constexpr uint16_t VP_Flowrate_E1 = 0x3092; // 2 Byte Integer
constexpr uint16_t VP_Fan_SET = 0x2208;  // 2 Byte Integer (0..100)
// constexpr uint16_t VP_TUNE_Fan_SET = 0x2254;  // 2 Byte Integer (0..100)

constexpr uint16_t VP_Fan0_Percentage = 0x5100;  // 2 Byte Integer (0..100)
constexpr uint16_t VP_Fan1_Percentage = 0x33A2;  // 2 Byte Integer (0..100)
//constexpr uint16_t VP_Fan2_Percentage = 0x33A4;  // 2 Byte Integer (0..100)·
//constexpr uint16_t VP_Fan3_Percentage = 0x33A6;  // 2 Byte Integer (0..100)

// Buttons on the SD-Card File listing.
constexpr uint16_t VP_SD_ScrollEvent = 0x210F; // Data: 0 for "up a directory", numbers are the amount to scroll, e.g -1 one up, 1 one down
constexpr uint16_t VP_SD_FileSelected = 0x2022; // Number of file field selected.
constexpr uint16_t VP_SD_FileSelectConfirm = 0x2024; // (This is a virtual VP and emulated by the Confirm Screen when a file has been confirmed)


// constexpr uint16_t VP_SD_ResumePause = 0x2010; // Resume(Data=0), Pause(Data=1), Abort(Data=2) SD Card prints
constexpr uint16_t VP_SD_ResumePauseAbort = 0x2010; // Resume(Data=0), Pause(Data=1), Abort(Data=2) SD Card prints



constexpr uint16_t VP_SD_AbortPrintConfirmed = 0x2028; // Abort print confirmation (virtual, will be injected by the confirm dialog)
constexpr uint16_t VP_SD_Print_Setting = 0x2040;
constexpr uint16_t VP_SD_Print_LiveAdjustZ = 0x2050; // Data: 0 down, 1 up

constexpr uint16_t VP_SD_POWER_LESS_BUTTON = 0X2012;

constexpr uint16_t VP_SD_FIL_PAUSE_BUTTON = 0X2014;

constexpr uint16_t VP_Feedrate_Percentage = 0x2248; // 2 Byte Integer (0..100)
constexpr uint16_t VP_Feedrate_Percent = 0x300E; // 2 Byte Integer (0..100)

constexpr uint16_t VP_PrintProgress_Percentage = 0x5A00; // 2 Byte Integer (0..100)

// constexpr uint16_t VP_PrintProgress_Percentage_1 = 0x5A00; // 2 Byte Integer (0..100)

constexpr uint16_t VP_PrintTime = 0x5106;
constexpr uint16_t VP_PrintTime_LEN = 10;

constexpr uint16_t VP_PrintAccTime = 0x5160;
constexpr uint16_t VP_PrintAccTime_LEN = 32;

constexpr uint16_t VP_PrintsTotal = 0x5180;
constexpr uint16_t VP_PrintsTotal_LEN = 16;

// Actual Position
// constexpr uint16_t VP_XPos = 0x5110;  // 4 Byte Fixed point number; format xxx.yy
// constexpr uint16_t VP_YPos = 0x5112;  // 4 Byte Fixed point number; format xxx.yy
// constexpr uint16_t VP_ZPos = 0x5114;  // 4 Byte Fixed point number; format xxx.yy

constexpr uint16_t VP_EPos = 0x5120;  // 4 Byte Fixed point number; format xxx.yy

// SDCard File Listing
constexpr uint16_t VP_SD_FileName_LEN = 0x30; // LEN is shared for all entries.
constexpr uint16_t DGUS_SD_FILESPERSCREEN = 5; // FIXME move that info to the display and read it from there.
constexpr uint16_t VP_SD_FileName0 = 0x3100;
constexpr uint16_t VP_SD_FileName1 = 0x3130;
constexpr uint16_t VP_SD_FileName2 = 0x3160;
constexpr uint16_t VP_SD_FileName3 = 0x3190;
constexpr uint16_t VP_SD_FileName4 = 0x31C0;


constexpr uint16_t VP_FileName_BUTTON = 0x2101;
constexpr uint16_t VP_FileName_EN_BUTTON = 0x2102;
constexpr uint16_t VP_FileName_ES_BUTTON = 0x2103;
constexpr uint16_t VP_FileName_FR_BUTTON = 0x2104;
constexpr uint16_t VP_FileName_DE_BUTTON = 0x2105;
constexpr uint16_t VP_FileName_PY_BUTTON = 0x2106;


constexpr uint16_t VP_ProbeOffsetZ = 0x3200; //
constexpr uint16_t VP_ProbeOffsetZ_PRINTING = 0x3210; //



constexpr uint16_t VP_SHOW_PRINT_FILE      =0X3500;
constexpr uint16_t VP_SD_Print_ProbeOffsetZ = 0x32A0; //
constexpr uint16_t VP_SD_Print_Filename = 0x32C0; //

// Fan status
// constexpr uint16_t VP_FAN0_STATUS = 0x3300;
// constexpr uint16_t VP_FAN1_STATUS = 0x3302;
//constexpr uint16_t VP_FAN2_STATUS = 0x3304;
//constexpr uint16_t VP_FAN3_STATUS = 0x3306;

// Heater status
// constexpr uint16_t VP_E0_STATUS = 0x3310;
//constexpr uint16_t VP_E1_STATUS = 0x3312;
//constexpr uint16_t VP_E2_STATUS = 0x3314;
//constexpr uint16_t VP_E3_STATUS = 0x3316;
//constexpr uint16_t VP_E4_STATUS = 0x3318;
//constexpr uint16_t VP_E5_STATUS = 0x331A;
// constexpr uint16_t VP_BED_STATUS = 0x331C;

constexpr uint16_t VP_MOVE_OPTION = 0x4400;

// Step per mm
constexpr uint16_t VP_X_STEP_PER_MM = 0x223C; // at the moment , 2 byte unsigned int , 0~1638.4
//constexpr uint16_t VP_X2_STEP_PER_MM = 0x3602;
constexpr uint16_t VP_Y_STEP_PER_MM = 0x223E;
//constexpr uint16_t VP_Y2_STEP_PER_MM = 0x3606;
constexpr uint16_t VP_Z_STEP_PER_MM = 0x2240;
//constexpr uint16_t VP_Z2_STEP_PER_MM = 0x360A;
constexpr uint16_t VP_E0_STEP_PER_MM = 0x2244;
//constexpr uint16_t VP_E1_STEP_PER_MM = 0x3612;
//constexpr uint16_t VP_E2_STEP_PER_MM = 0x3614;
//constexpr uint16_t VP_E3_STEP_PER_MM = 0x3616;
//constexpr uint16_t VP_E4_STEP_PER_MM = 0x3618;
//constexpr uint16_t VP_E5_STEP_PER_MM = 0x361A;

// PIDs

constexpr uint16_t VP_X_MAX_SPEED   =  0X220C;
constexpr uint16_t VP_Y_MAX_SPEED   =  0X2210;
constexpr uint16_t VP_Z_MAX_SPEED   =  0X2214;
constexpr uint16_t VP_E_MAX_SPEED   =  0X2218;

constexpr uint16_t VP_X_MAX_ACC   =  0X2400;
constexpr uint16_t VP_Y_MAX_ACC   =  0X2404;
constexpr uint16_t VP_Z_MAX_ACC   =  0X2408;
constexpr uint16_t VP_E_MAX_ACC   =  0X240C;

// constexpr uint16_t VP_X_MAX_CORNER   =  0X222C;
// constexpr uint16_t VP_Y_MAX_CORNER   =  0X2220;
// constexpr uint16_t VP_Z_MAX_CORNER   =  0X2224;
// constexpr uint16_t VP_E_MAX_CORNER   =  0X2228;

// Waiting screen status
constexpr uint16_t VP_WAITING_STATUS = 0x3800;

// SPs for certain variables...
// located at 0x5000 and up
// Not used yet!
// This can be used e.g to make controls / data display invisible
