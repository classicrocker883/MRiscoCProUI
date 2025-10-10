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

/**
 * lcd/extui/dgus/origin/DGUSDisplayDef.cpp
 */

#include "../../../../inc/MarlinConfigPre.h"

#if DGUS_LCD_UI_ORIGIN

#include "DGUSDisplayDef.h"
#include "../DGUSDisplay.h"
#include "../DGUSScreenHandler.h"

#include "../../../../module/temperature.h"
#include "../../../../module/motion.h"
#include "../../../../module/planner.h"

#include "../../../marlinui.h"
#include "../../ui_api.h"

lcd_info_t lcd_info;

#if ENABLED(DGUS_UI_MOVE_DIS_OPTION)
  uint16_t distanceToMove = 10;
#endif
using namespace ExtUI;

const uint16_t VPList_Boot[] PROGMEM = {
  VP_MARLIN_VERSION,
  0x0000
};
const uint16_t VPList_Info[] PROGMEM = {
  VP_MARLIN_VERSION,
  VP_MachineName,
  VP_Web,
  VP_PRINTSIZE,
  VP_Email,
  0x0000
};
// const uint16_t VPList_Main[] PROGMEM = {
//   // VP_M117, for completeness, but it cannot be auto-uploaded.
//     #if HAS_HOTEND
//     VP_T_E0_Is, VP_T_E0_Set,
//     #if HAS_MULTI_HOTEND
//       VP_T_E1_Is, VP_T_E1_Set,
//     #endif
//   #endif
//   #if HAS_HEATED_BED
//     VP_T_Bed_Is,VP_T_Bed_Set,
//   #endif
//   0x0000
// };

const uint16_t VPList_Main[] PROGMEM = {VP_T_E0_Is, VP_T_E0_Set,VP_T_Bed_Is,VP_T_Bed_Set,0x0000};
// const uint16_t VPList_ManualMove[]           PROGMEM = { VP_XPos, VP_YPos, VP_ZPos, 0x0000 };
// const uint16_t VPList_ManualExtrude[]        PROGMEM = { VP_EPos, 0x0000 };
const uint16_t VPList_FanAndFeedrate[]       PROGMEM = { VP_Feedrate_Percentage, VP_Fan0_Percentage, 0x0000 };
// const uint16_t VPList_SD_FlowRates[]         PROGMEM = { VP_Flowrate_E0, VP_Flowrate_E1, 0x0000 };
const uint16_t VPList_SDFileList[]           PROGMEM = {VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,VP_SD_FileName0, VP_SD_FileName1, VP_SD_FileName2, VP_SD_FileName3, VP_SD_FileName4, 0x0000 };
// const uint16_t VPList_SD_PrintManipulation[] PROGMEM = { VP_PrintProgress_Percentage, VP_PrintTime, 0x0000 };
const uint16_t VPList_Control[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,0x0000};
const uint16_t VPList_Prepare[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,0x0000};
// const uint16_t VPList_Info[ ] PROGMEM = {};
const uint16_t VPList_Printing[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,VP_Feedrate_Percent,VP_ProbeOffsetZ_PRINTING,VP_PrintProgress_Percentage,VP_PrintTime,VP_PrintsTotal,0000};
const uint16_t VPList_EN_Printing[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,VP_Feedrate_Percent,VP_ProbeOffsetZ_PRINTING,VP_PrintProgress_Percentage,0000};
const uint16_t VPList_Moveaxis[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,VP_X_AXIS_coordinate,VP_Y_AXIS_coordinate,VP_Z_AXIS_coordinate,0x0000};
const uint16_t VPList_Load[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,0x0000};
const uint16_t VPList_Unload[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,0x0000};
const uint16_t VPList_Null[] PROGMEM = {VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,VP_ProbeOffsetZ,0X0000};
const uint16_t VPList_Temperture[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,VP_Fan_SET,0x0000};
const uint16_t VPList_Move[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,0x0000};
const uint16_t VPList_Maxspeed[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,VP_X_MAX_SPEED,VP_Y_MAX_SPEED,VP_Z_MAX_SPEED,VP_E_MAX_SPEED,0x0000};
const uint16_t VPList_Maxacce[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,VP_X_MAX_ACC,VP_Y_MAX_ACC,VP_Z_MAX_ACC,VP_E_MAX_ACC,0x0000};
const uint16_t VPList_Maxcorner[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,0x0000};
const uint16_t VPList_Step[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,VP_X_STEP_PER_MM,VP_Y_STEP_PER_MM,VP_Z_STEP_PER_MM,VP_E0_STEP_PER_MM,0x0000};
const uint16_t VPList_Control_1[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,0x0000};
const uint16_t VPList_Level[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,0x0000};
const uint16_t VPList_Tune[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,VP_Feedrate_Percentage,VP_Tune_E0_Set,VP_Tune_BED_Set,VP_Tune_FAN_Set,0x0000};
const uint16_t VPList_Set_pla[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,0x0000};
const uint16_t VPList_Set_abs[] PROGMEM = { VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,0x0000};
const uint16_t VPList_OFFSET_Z[] PROGMEM = {VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,VP_ProbeOffsetZ,0X0000};
const uint16_t VPList_POWER_LESS[] PROGMEM = {VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,0X0000};
const uint16_t VPList_FIL_Pause[] PROGMEM = {VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,VP_Feedrate_Percent,VP_ProbeOffsetZ_PRINTING,0X0000};
const uint16_t VPList_Abort_File[] PROGMEM ={VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,0X0000};
const uint16_t VPList_Language[] PROGMEM ={VP_T_E0_Is, VP_T_E0_Set, VP_T_Bed_Is,VP_T_Bed_Set,0X0000};
const struct VPMapping VPMap[] PROGMEM = {
  // // { DGUSLCD_SCREEN_BOOT,                VPList_Boot                 },

  {DGUSLCD_SCREEN_MAIN,VPList_Main},
  {DGUSLCD_SCREEN_SDFILELIST,VPList_SDFileList},
  {DGUSLCD_SCREEN_CONTROL,VPList_Control},
  {DGUSLCD_SCREEN_CONTROL_1,VPList_Control_1},
  {DGUSLCD_SCREEN_PREPARE,VPList_Prepare},
  {DGUSLCD_SCREEN_PREPARE_1,VPList_Prepare},


  {DGUSLCD_SCREEN_LANGUAGE_CN,VPList_Language},
  // {DGUSLCD_SCREEN_LANGUAGE_EN,VPList_Language},
  // {DGUSLCD_SCREEN_LANGUAGE_ES,VPList_Language},
  // {DGUSLCD_SCREEN_LANGUAGE_FR,VPList_Language},

  {DGUSLCD_SCREEN_INFO,VPList_Info},
  {DGUSLCD_SCREEN_PRINTING,VPList_Printing},
  {DGUSLCD_SCREEN_MOVEAXIS,VPList_Moveaxis},
  {DGUSLCD_SCREEN_LOAD,VPList_Load},
  {DGUSLCD_SCREEN_LOAD_1,VPList_Load},
  {DGUSLCD_SCREEN_UNLOAD,VPList_Unload},
  {DGUSLCD_SCREEN_UNLOAD_1,VPList_Unload},
  {DGUSLCD_SCREEN_NULL,VPList_Null},
  {DGUSLCD_SCREEN_TEMPERTURE,VPList_Temperture},
  {DGUSLCD_SCREEN_MOVE,VPList_Move},
  {DGUSLCD_SCREEN_MAXSPEED,VPList_Maxspeed},
  {DGUSLCD_SCREEN_MAXACCE,VPList_Maxacce},
  {DGUSLCD_SCREEN_UNLOAD,VPList_Maxcorner},
  {DGUSLCD_SCREEN_STEP,VPList_Step},
  {DGUSLCD_SCREEN_LEVEL,VPList_Level},
  {DGUSLCD_SCREEN_TUNE,VPList_Tune},
  {DGUSLCD_SCREEN_SET_PLA,VPList_Set_pla},
  {DGUSLCD_SCREEN_SET_ABS,VPList_Set_abs},
  {DGUSLCD_SCREEN_OFFSET_Z,VPList_OFFSET_Z},

  {DGUSLCD_SCREEN_EN_TEMPERTURE,VPList_Temperture},
  {DGUSLCD_SCREEN_EN_PREPARE,VPList_Prepare},
  {DGUSLCD_SCREEN_EN_CONTROL,VPList_Control},
  {DGUSLCD_SCREEN_EN_CONTROL_1,VPList_Control_1},
  {DGUSLCD_SCREEN_EN_OFFSET_Z_1,VPList_OFFSET_Z},
  {DGUSLCD_SCREEN_EN_LOAD,VPList_Load},
  {DGUSLCD_SCREEN_EN_LOAD_1,VPList_Load},
  {DGUSLCD_SCREEN_EN_UNLOAD,VPList_Unload},
  {DGUSLCD_SCREEN_EN_UNLOAD_1,VPList_Unload},
  {DGUSLCD_SCREEN_EN_TUNE,VPList_Tune},
  {DGUSLCD_SCREEN_EN_OFFSET_Z,VPList_Null},
  {DGUSLCD_SCREEN_EN_MAXSPEED,VPList_Maxspeed},
  {DGUSLCD_SCREEN_EN_MAXACCE,VPList_Maxacce},
  {DGUSLCD_SCREEN_EN_STEP,VPList_Step},
  {DGUSLCD_SCREEN_EN_MAIN,VPList_Main},
  {DGUSLCD_SCREEN_EN_SDFILELIST,VPList_SDFileList},
  {DGUSLCD_SCREEN_EN_PRINTING,VPList_EN_Printing},
  {DGUSLCD_SCREEN_EN_INFO,VPList_Info},
  {DGUSLCD_SCREEN_EN_LEVEL,VPList_Level},
  {DGUSLCD_SCREEN_EN_MOVEAXIS,VPList_Moveaxis},

  {DGUSLCD_SCREEN_ES_TEMPERTURE,VPList_Temperture},
  {DGUSLCD_SCREEN_ES_PREPARE,VPList_Prepare},
  {DGUSLCD_SCREEN_ES_CONTROL,VPList_Control},
  {DGUSLCD_SCREEN_ES_CONTROL_1,VPList_Control_1},
  {DGUSLCD_SCREEN_ES_OFFSET_Z_1,VPList_OFFSET_Z},
  {DGUSLCD_SCREEN_ES_LOAD,VPList_Load},
  {DGUSLCD_SCREEN_ES_LOAD_1,VPList_Load},
  {DGUSLCD_SCREEN_ES_UNLOAD,VPList_Unload},
  {DGUSLCD_SCREEN_ES_UNLOAD_1,VPList_Unload},
  {DGUSLCD_SCREEN_ES_TUNE,VPList_Tune},
  {DGUSLCD_SCREEN_ES_OFFSET_Z,VPList_Null},
  {DGUSLCD_SCREEN_ES_MAXSPEED,VPList_Maxspeed},
  {DGUSLCD_SCREEN_ES_MAXACCE,VPList_Maxacce},
  {DGUSLCD_SCREEN_ES_STEP,VPList_Step},
  {DGUSLCD_SCREEN_ES_MAIN,VPList_Main},
  {DGUSLCD_SCREEN_ES_SDFILELIST,VPList_SDFileList},
  {DGUSLCD_SCREEN_ES_PRINTING,VPList_EN_Printing},
  {DGUSLCD_SCREEN_ES_INFO,VPList_Info},
  {DGUSLCD_SCREEN_ES_LEVEL,VPList_Level},
  {DGUSLCD_SCREEN_ES_MOVEAXIS,VPList_Moveaxis},

  {DGUSLCD_SCREEN_FR_TEMPERTURE,VPList_Temperture},
  {DGUSLCD_SCREEN_FR_PREPARE,VPList_Prepare},
  {DGUSLCD_SCREEN_FR_CONTROL,VPList_Control},
  {DGUSLCD_SCREEN_FR_CONTROL_1,VPList_Control_1},
  {DGUSLCD_SCREEN_FR_OFFSET_Z_1,VPList_OFFSET_Z},
  {DGUSLCD_SCREEN_FR_LOAD,VPList_Load},
  {DGUSLCD_SCREEN_FR_LOAD_1,VPList_Load},
  {DGUSLCD_SCREEN_FR_UNLOAD,VPList_Unload},
  {DGUSLCD_SCREEN_FR_UNLOAD_1,VPList_Unload},
  {DGUSLCD_SCREEN_FR_TUNE,VPList_Tune},
  {DGUSLCD_SCREEN_FR_OFFSET_Z,VPList_Null},
  {DGUSLCD_SCREEN_FR_MAXSPEED,VPList_Maxspeed},
  {DGUSLCD_SCREEN_FR_MAXACCE,VPList_Maxacce},
  {DGUSLCD_SCREEN_FR_STEP,VPList_Step},
  {DGUSLCD_SCREEN_FR_MAIN,VPList_Main},
  {DGUSLCD_SCREEN_FR_SDFILELIST,VPList_SDFileList},
  {DGUSLCD_SCREEN_FR_PRINTING,VPList_EN_Printing},
  {DGUSLCD_SCREEN_FR_INFO,VPList_Info},
  {DGUSLCD_SCREEN_FR_LEVEL,VPList_Level},
  {DGUSLCD_SCREEN_FR_MOVEAXIS,VPList_Moveaxis},

  {DGUSLCD_SCREEN_DE_TEMPERTURE,VPList_Temperture},
  {DGUSLCD_SCREEN_DE_PREPARE,VPList_Prepare},
  {DGUSLCD_SCREEN_DE_CONTROL,VPList_Control},
  {DGUSLCD_SCREEN_DE_CONTROL_1,VPList_Control_1},
  {DGUSLCD_SCREEN_DE_OFFSET_Z_1,VPList_OFFSET_Z},
  {DGUSLCD_SCREEN_DE_LOAD,VPList_Load},
  {DGUSLCD_SCREEN_DE_LOAD_1,VPList_Load},
  {DGUSLCD_SCREEN_DE_UNLOAD,VPList_Unload},
  {DGUSLCD_SCREEN_DE_UNLOAD_1,VPList_Unload},
  {DGUSLCD_SCREEN_DE_TUNE,VPList_Tune},
  {DGUSLCD_SCREEN_DE_OFFSET_Z,VPList_Null},
  {DGUSLCD_SCREEN_DE_MAXSPEED,VPList_Maxspeed},
  {DGUSLCD_SCREEN_DE_MAXACCE,VPList_Maxacce},
  {DGUSLCD_SCREEN_DE_STEP,VPList_Step},
  {DGUSLCD_SCREEN_DE_MAIN,VPList_Main},
  {DGUSLCD_SCREEN_DE_SDFILELIST,VPList_SDFileList},
  {DGUSLCD_SCREEN_DE_PRINTING,VPList_EN_Printing},
  {DGUSLCD_SCREEN_DE_INFO,VPList_Info},
  {DGUSLCD_SCREEN_DE_LEVEL,VPList_Level},
  {DGUSLCD_SCREEN_DE_MOVEAXIS,VPList_Moveaxis},


  {DGUSLCD_SCREEN_PY_TEMPERTURE,VPList_Temperture},
  {DGUSLCD_SCREEN_PY_PREPARE,VPList_Prepare},
  {DGUSLCD_SCREEN_PY_CONTROL,VPList_Control},
  {DGUSLCD_SCREEN_PY_CONTROL_1,VPList_Control_1},
  {DGUSLCD_SCREEN_PY_OFFSET_Z_1,VPList_OFFSET_Z},
  {DGUSLCD_SCREEN_PY_LOAD,VPList_Load},
  {DGUSLCD_SCREEN_PY_LOAD_1,VPList_Load},
  {DGUSLCD_SCREEN_PY_UNLOAD,VPList_Unload},
  {DGUSLCD_SCREEN_PY_UNLOAD_1,VPList_Unload},
  {DGUSLCD_SCREEN_PY_TUNE,VPList_Tune},
  {DGUSLCD_SCREEN_PY_OFFSET_Z,VPList_Null},
  {DGUSLCD_SCREEN_PY_MAXSPEED,VPList_Maxspeed},
  {DGUSLCD_SCREEN_PY_MAXACCE,VPList_Maxacce},
  {DGUSLCD_SCREEN_PY_STEP,VPList_Step},
  {DGUSLCD_SCREEN_PY_MAIN,VPList_Main},
  {DGUSLCD_SCREEN_PY_SDFILELIST,VPList_SDFileList},
  {DGUSLCD_SCREEN_PY_PRINTING,VPList_EN_Printing},
  {DGUSLCD_SCREEN_PY_INFO,VPList_Info},
  {DGUSLCD_SCREEN_PY_LEVEL,VPList_Level},
  {DGUSLCD_SCREEN_PY_MOVEAXIS,VPList_Moveaxis},

  // {DGUSLCD_SCREEN_DE_MAIN,VPList_Main},
  // {DGUSLCD_SCREEN_DE_SDFILELIST,VPList_SDFileList},
  // {DGUSLCD_SCREEN_DE_CONTROL,VPList_Control},
  // {DGUSLCD_SCREEN_DE_CONTROL_1,VPList_Control_1},
  // {DGUSLCD_SCREEN_DE_PREPARE,VPList_Prepare},
  // {DGUSLCD_SCREEN_DE_PREPARE_1,VPList_Prepare},
  // {DGUSLCD_SCREEN_DE_INFO,VPList_Info},
  // {DGUSLCD_SCREEN_DE_PRINTING,VPList_Printing},
  // {DGUSLCD_SCREEN_DE_MOVEAXIS,VPList_Moveaxis},
  // {DGUSLCD_SCREEN_DE_LOAD,VPList_Load},
  // {DGUSLCD_SCREEN_DE_LOAD_1,VPList_Load},
  // {DGUSLCD_SCREEN_DE_LOAD_2,VPList_Load},

  // {DGUSLCD_SCREEN_PY_MAIN,VPList_Main},
  // {DGUSLCD_SCREEN_PY_SDFILELIST,VPList_SDFileList},
  // {DGUSLCD_SCREEN_PY_CONTROL,VPList_Control},
  // {DGUSLCD_SCREEN_PY_CONTROL_1,VPList_Control_1},
  // {DGUSLCD_SCREEN_PY_PREPARE,VPList_Prepare},
  // {DGUSLCD_SCREEN_PY_PREPARE_1,VPList_Prepare},
  // {DGUSLCD_SCREEN_PY_INFO,VPList_Info},
  // {DGUSLCD_SCREEN_PY_PRINTING,VPList_Printing},
  // {DGUSLCD_SCREEN_PY_MOVEAXIS,VPList_Moveaxis},
  // {DGUSLCD_SCREEN_PY_LOAD,VPList_Load},
  // {DGUSLCD_SCREEN_PY_LOAD_1,VPList_Load},
  // {DGUSLCD_SCREEN_PY_LOAD_2,VPList_Load},

  // {DGUSLCD_SCREEN_POWER_LOSS,VPList_POWER_LESS},
  // {DGUSLCD_SCREEN_FIL_PAUSE,VPList_FIL_Pause},
  // {DGUSLCD_SCREEN_ABORT_FILE,VPList_Abort_File},
  { 0 , nullptr } // List is terminated with an nullptr as table entry.
};
#define TTTT "2.0.2"
const char MarlinVersion[] PROGMEM = TTTT;
const char MachineName[] PROGMEM = "Aquila D1";
const char WEB[] PROGMEM = "www.voxelab3dp.com";
const char EMAIL[] PROGMEM = "support@voxelab3dp.com";
const char P_SIZE[] PROGMEM = "235*235*250";

const struct DGUS_VP_Variable ListOfVP[] PROGMEM = {
  // Helper to detect touch events
  VPHELPER(VP_SCREENCHANGE, nullptr, ScreenHandler.ScreenChangeHook, nullptr),
  VPHELPER(VP_SCREENCHANGE_ASK, nullptr, ScreenHandler.ScreenChangeHookIfIdle, nullptr),
  #if HAS_MEDIA
  VPHELPER(VP_SCREENCHANGE_WHENSD, nullptr, ScreenHandler.ScreenChangeHookIfSD, nullptr),
  #endif
  VPHELPER(VP_CONFIRMED, nullptr, ScreenHandler.ScreenConfirmedOK, nullptr),

  VPHELPER(VP_TEMP_ALL_OFF, nullptr, ScreenHandler.HandleAllHeatersOff, nullptr),

  #if ENABLED(DGUS_UI_MOVE_DIS_OPTION)
    VPHELPER(VP_MOVE_OPTION, &distanceToMove, ScreenHandler.HandleManualMoveOption, nullptr),
  #endif
  #if ENABLED(DGUS_UI_MOVE_DIS_OPTION)
    VPHELPER(VP_MOVE_X, &distanceToMove, ScreenHandler.HandleManualMove, nullptr),
    VPHELPER(VP_MOVE_Y, &distanceToMove, ScreenHandler.HandleManualMove, nullptr),
    VPHELPER(VP_MOVE_Z, &distanceToMove, ScreenHandler.HandleManualMove, nullptr),
    VPHELPER(VP_HOME_ALL, &distanceToMove, ScreenHandler.HandleManualMove, nullptr),
  #else
    // VPHELPER(VP_MOVE_X, nullptr, ScreenHandler.HandleManualMove, nullptr),
    // VPHELPER(VP_MOVE_Y, nullptr, ScreenHandler.HandleManualMove, nullptr),
    // VPHELPER(VP_MOVE_Z, nullptr, ScreenHandler.HandleManualMove, nullptr),
  VPHELPER(VP_HOME_ALL, nullptr, ScreenHandler.HandleManualHome, nullptr),
  #endif

  VPHELPER(VP_PLA_BUTTON, nullptr, ScreenHandler.HandlePLAHEAT, nullptr),
  VPHELPER(VP_ABS_BUTTON, nullptr, ScreenHandler.HandleABSHEAT, nullptr),

VPHELPER(VP_PREPARE_PLA_HOTED_BUTTON, nullptr, ScreenHandler.HandlePreparePLAHotedChanged, nullptr),
VPHELPER(VP_PREPARE_PLA_BED_BUTTON, nullptr, ScreenHandler.HandlePreparePLABedChanged, nullptr),
VPHELPER(VP_PREPARE_ABS_HOTED_BUTTON, nullptr, ScreenHandler.HandlePrepareABSHotedChanged, nullptr),
VPHELPER(VP_PREPARE_ABS_BED_BUTTON, nullptr, ScreenHandler.HandlePrepareABSBedChanged, nullptr),


  VPHELPER(VP_LOAD_BUTTON, nullptr, ScreenHandler.HandleLoad, nullptr),
  VPHELPER(VP_UNLOAD_BUTTON, nullptr, ScreenHandler.HandleUnload, nullptr),

  VPHELPER(VP_COOLDOWN_BUTTON, nullptr, ScreenHandler.HandleCooldown, nullptr),

  VPHELPER(VP_MOTOR_LOCK_UNLOK, nullptr, ScreenHandler.HandleMotorLockUnlock, nullptr),

  VPHELPER(VP_BEEP_LOCK_UNLOK, nullptr, ScreenHandler.HandleBeepLockUnlock, nullptr),

  VPHELPER(VP_CHECK_FIL_BUTTON, nullptr, ScreenHandler.HandleCHECK_FIL, nullptr),
  #if ENABLED(POWER_LOSS_RECOVERY)
    // VPHELPER(VP_POWER_LOSS_RECOVERY, nullptr, ScreenHandler.HandlePowerLossRecovery, nullptr),
  #endif
  VPHELPER(VP_SETTINGS, nullptr, ScreenHandler.HandleSettings, nullptr),

  { .VP = VP_MARLIN_VERSION, .memadr = (void*)MarlinVersion, .size = VP_MARLIN_VERSION_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplay },
  { .VP = VP_MachineName, .memadr = (void*)MachineName, .size = VP_MachineName_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplay },
  { .VP = VP_Web, .memadr = (void*)WEB, .size = VP_WEB_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplay },
  { .VP = VP_PRINTSIZE, .memadr = (void*)P_SIZE, .size = VP_PRINTSIZE_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplay },
  { .VP = VP_Email, .memadr = (void*)EMAIL, .size = VP_EMAIL_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplay },
  // M117 LCD String (We don't need the string in memory but "just" push it to the display on demand, hence the nullptr

  { .VP = VP_M117, .memadr = nullptr, .size = VP_M117_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplay },


  // Temperature Data
  #if HAS_HOTEND
    VPHELPER(VP_T_E0_Is, &thermalManager.temp_hotend[0].celsius, nullptr, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<2>),
    // VPHELPER(VP_T_E0_Set, &thermalManager.temp_hotend[0].target,nullptr, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<2>),
    VPHELPER(VP_T_E0_Set, &thermalManager.temp_hotend[0].target, ScreenHandler.HandleTemperatureChanged, &ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    VPHELPER(VP_Tune_E0_Set, &thermalManager.temp_hotend[0].target, ScreenHandler.HandleTemperatureChanged, &ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    // VPHELPER(VP_Flowrate_E0, nullptr, ScreenHandler.HandleFlowRateChanged, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    // VPHELPER(VP_EPos, &destination.e, nullptr, ScreenHandler.DGUSLCD_SendFloatAsLongValueToDisplay<2>),
    // VPHELPER(VP_MOVE_E0, nullptr, ScreenHandler.HandleManualExtrude, nullptr),
    VPHELPER(VP_E0_CONTROL, &thermalManager.temp_hotend[0].target,  ScreenHandler.HandleTemperatureChanged, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    // VPHELPER(VP_E0_STATUS, &thermalManager.temp_hotend[0].target, nullptr, ScreenHandler.DGUSLCD_SendHeaterStatusToDisplay),
    #if ENABLED(DGUS_PREHEAT_UI)
      VPHELPER(VP_E0_BED_PREHEAT, nullptr, ScreenHandler.HandlePreheat, nullptr),
    #endif
    #if ENABLED(PIDTEMP)
      // VPHELPER(VP_E0_PID_P, &thermalManager.temp_hotend[0].pid.Kp, ScreenHandler.HandleTemperaturePIDChanged, ScreenHandler.DGUSLCD_SendTemperaturePID),
      // VPHELPER(VP_E0_PID_I, &thermalManager.temp_hotend[0].pid.Ki, ScreenHandler.HandleTemperaturePIDChanged, ScreenHandler.DGUSLCD_SendTemperaturePID),
      // VPHELPER(VP_E0_PID_D, &thermalManager.temp_hotend[0].pid.Kd, ScreenHandler.HandleTemperaturePIDChanged, ScreenHandler.DGUSLCD_SendTemperaturePID),
      // VPHELPER(VP_PID_AUTOTUNE_E0, nullptr, ScreenHandler.HandlePIDAutotune, nullptr),
    #endif
    #if ENABLED(DGUS_FILAMENT_LOADUNLOAD)
      VPHELPER(VP_E0_FILAMENT_LOAD_UNLOAD, nullptr, ScreenHandler.HandleFilamentOption, ScreenHandler.HandleFilamentLoadUnload),
    #endif
  #endif
  #if HAS_MULTI_HOTEND
    VPHELPER(VP_T_E1_Is, &thermalManager.temp_hotend[1].celsius, nullptr, ScreenHandler.DGUSLCD_SendFloatAsLongValueToDisplay<0>),
    VPHELPER(VP_T_E1_Set, &thermalManager.temp_hotend[1].target, ScreenHandler.HandleTemperatureChanged, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    VPHELPER(VP_Flowrate_E1, nullptr, ScreenHandler.HandleFlowRateChanged, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    VPHELPER(VP_MOVE_E1, nullptr, ScreenHandler.HandleManualExtrude, nullptr),
    VPHELPER(VP_E1_CONTROL, &thermalManager.temp_hotend[1].target, ScreenHandler.HandleHeaterControl, nullptr),
    VPHELPER(VP_E1_STATUS, &thermalManager.temp_hotend[1].target, nullptr, ScreenHandler.DGUSLCD_SendHeaterStatusToDisplay),
    #if ENABLED(PIDTEMP)
      VPHELPER(VP_PID_AUTOTUNE_E1, nullptr, ScreenHandler.HandlePIDAutotune, nullptr),
    #endif
  #endif
  #if HAS_HEATED_BED
    VPHELPER(VP_T_Bed_Is, &thermalManager.temp_bed.celsius, nullptr, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<2>),
    VPHELPER(VP_T_Bed_Set, &thermalManager.temp_bed.target, ScreenHandler.HandleTemperatureChanged, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    VPHELPER(VP_Tune_BED_Set, &thermalManager.temp_bed.target, ScreenHandler.HandleTemperatureChanged, ScreenHandler.DGUSLCD_SendWordValueToDisplay),

    VPHELPER(VP_BED_CONTROL, &thermalManager.temp_bed.target,  ScreenHandler.HandleTemperatureChanged, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    // VPHELPER(VP_BED_STATUS, &thermalManager.temp_bed.target, nullptr, ScreenHandler.DGUSLCD_SendHeaterStatusToDisplay),
    #if ENABLED(PIDTEMPBED)
      VPHELPER(VP_BED_PID_P, &thermalManager.temp_bed.pid.Kp, ScreenHandler.HandleTemperaturePIDChanged, ScreenHandler.DGUSLCD_SendTemperaturePID),
      VPHELPER(VP_BED_PID_I, &thermalManager.temp_bed.pid.Ki, ScreenHandler.HandleTemperaturePIDChanged, ScreenHandler.DGUSLCD_SendTemperaturePID),
      VPHELPER(VP_BED_PID_D, &thermalManager.temp_bed.pid.Kd, ScreenHandler.HandleTemperaturePIDChanged, ScreenHandler.DGUSLCD_SendTemperaturePID),
    #endif
  #endif

  // Fan Data
  VPHELPER(VP_Fan_SET, &thermalManager.fan_speed[0], ScreenHandler.HandleFanChanged, &ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  VPHELPER(VP_Tune_FAN_Set, &thermalManager.fan_speed[0], ScreenHandler.HandleFanChanged, &ScreenHandler.DGUSLCD_SendWordValueToDisplay),

  //  VPHELPER(VP_Fan0_Percentage, &thermalManager.fan_speed[N],nullptr, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<2>),
  #if HAS_FAN
    #define FAN_VPHELPER(N) \
    //   VPHELPER(VP_Fan##N##_Percentage, &thermalManager.fan_speed[N], ScreenHandler.DGUSLCD_PercentageToUint8, ScreenHandler.DGUSLCD_SendPercentageToDisplay), \
      // VPHELPER(VP_FAN##N##_CONTROL, &thermalManager.fan_speed[N], ScreenHandler.HandleFanControl, nullptr), \
    //   VPHELPER(VP_FAN##N##_STATUS, &thermalManager.fan_speed[N], nullptr, ScreenHandler.DGUSLCD_SendFanStatusToDisplay),

    // REPEAT(FAN_COUNT, FAN_VPHELPER)
  #endif

  // Feedrate
VPHELPER(VP_Feedrate_Percentage, &feedrate_percentage, ScreenHandler.DGUSLCD_SetValueDirectly<int16_t>, ScreenHandler.DGUSLCD_SendWordValueToDisplay),

VPHELPER(VP_Feedrate_Percent, &feedrate_percentage, ScreenHandler.DGUSLCD_SetValueDirectly<int16_t>, ScreenHandler.DGUSLCD_SendWordValueToDisplay),

VPHELPER(VP_HOME_BUTTON, nullptr, ScreenHandler.HandleSendChangeScreen,nullptr),
VPHELPER(VP_CANCEL_BUTTON, nullptr, ScreenHandler.HandleSendCancelChangeScreen,nullptr),

VPHELPER(VP_SETTING_LANG_BUTTON, nullptr, ScreenHandler.HandlelangScreen,nullptr),

VPHELPER(VP_PAUSE_BUTTON, nullptr, ScreenHandler.HandlePauseScreen,nullptr),


VPHELPER(VP_MOVE_X_Positive_BUTTON, nullptr, ScreenHandler.HandleManualMove,nullptr),
VPHELPER(VP_MOVE_X_Negative_BUTTON, nullptr, ScreenHandler.HandleManualMove,nullptr),
VPHELPER(VP_MOVE_Y_Positive_BUTTON, nullptr, ScreenHandler.HandleManualMove,nullptr),
VPHELPER(VP_MOVE_Y_Negative_BUTTON, nullptr, ScreenHandler.HandleManualMove,nullptr),
VPHELPER(VP_MOVE_Z_Positive_BUTTON, nullptr, ScreenHandler.HandleManualMove,nullptr),
VPHELPER(VP_MOVE_Z_Negative_BUTTON, nullptr, ScreenHandler.HandleManualMove,nullptr),

VPHELPER(VP_MOVE_DIS_A_BUTTON, nullptr, ScreenHandler.HandleManualMove,nullptr),
VPHELPER(VP_MOVE_DIS_B_BUTTON, nullptr, ScreenHandler.HandleManualMove,nullptr),
VPHELPER(VP_MOVE_DIS_C_BUTTON, nullptr, ScreenHandler.HandleManualMove,nullptr),

VPHELPER(VP_SETTING_FACTORY_BUTTON, nullptr, ScreenHandler.HandleManualFactory,nullptr),

// VPHELPER(VP_INPUT_NUM_BUTTON, nullptr, ScreenHandler.HandleInputNum,nullptr),

  // Position Data
  VPHELPER(VP_X_AXIS_coordinate, &current_position.x, nullptr, ScreenHandler.HandleShowCoordinate<2>),
  VPHELPER(VP_Y_AXIS_coordinate, &current_position.y, nullptr, ScreenHandler.HandleShowCoordinate<2>),
  VPHELPER(VP_Z_AXIS_coordinate, &current_position.z, nullptr, ScreenHandler.HandleShowCoordinate<2>),

  // Print Progress
  VPHELPER(VP_PrintProgress_Percentage, nullptr, nullptr, ScreenHandler.DGUSLCD_SendPrintProgressToDisplay),

  // Print Time
  VPHELPER_STR(VP_PrintTime, nullptr, VP_PrintTime_LEN, nullptr, ScreenHandler.DGUSLCD_SendPrintTimeToDisplay),
  #if ENABLED(PRINTCOUNTER)
    VPHELPER_STR(VP_PrintAccTime, nullptr, VP_PrintAccTime_LEN, nullptr, ScreenHandler.DGUSLCD_SendPrintAccTimeToDisplay),
    VPHELPER_STR(VP_PrintsTotal, nullptr, VP_PrintsTotal_LEN, nullptr, ScreenHandler.DGUSLCD_SendPrintsTotalToDisplay),
  #endif

  VPHELPER(VP_X_MAX_SPEED, &planner.settings.max_feedrate_mm_s[X_AXIS], ScreenHandler.HandleMAXSpeedChanged, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<2>),
  VPHELPER(VP_Y_MAX_SPEED, &planner.settings.max_feedrate_mm_s[Y_AXIS], ScreenHandler.HandleMAXSpeedChanged, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<2>),
  VPHELPER(VP_Z_MAX_SPEED, &planner.settings.max_feedrate_mm_s[Z_AXIS], ScreenHandler.HandleMAXSpeedChanged, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<2>),
  #if HAS_HOTEND
    VPHELPER(VP_E_MAX_SPEED, &planner.settings.max_feedrate_mm_s[E_AXIS_N(0)], ScreenHandler.HandleMAXSpeedChanged_extruder, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<1>),
    #if HAS_MULTI_HOTEND
      VPHELPER(VP_E1_STEP_PER_MM, &planner.settings.axis_steps_per_mm[E_AXIS_N(1)], ScreenHandler.HandleStepPerMMExtruderChanged, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<1>),
    #endif
  #endif

VPHELPER(VP_X_MAX_ACC, &planner.settings.max_acceleration_mm_per_s2[X_AXIS], ScreenHandler.HandleMaxAccelerationChanged, ScreenHandler.DGUSLCD_SendMAX_ACC),
VPHELPER(VP_Y_MAX_ACC, &planner.settings.max_acceleration_mm_per_s2[Y_AXIS], ScreenHandler.HandleMaxAccelerationChanged, ScreenHandler.DGUSLCD_SendMAX_ACC),
VPHELPER(VP_Z_MAX_ACC, &planner.settings.max_acceleration_mm_per_s2[Z_AXIS], ScreenHandler.HandleMaxAccelerationChanged, ScreenHandler.DGUSLCD_SendMAX_ACC),
  #if HAS_HOTEND
    VPHELPER(VP_E_MAX_ACC, &planner.settings.max_acceleration_mm_per_s2[E_AXIS], ScreenHandler.HandleMaxAccelerationChanged_extruder, ScreenHandler.DGUSLCD_SendMAX_ACC),
    #if HAS_MULTI_HOTEND
      VPHELPER(VP_E1_STEP_PER_MM, &planner.settings.max_acceleration_mm_per_s2[E_AXIS_N(1)], ScreenHandler.HandleStepPerMMExtruderChanged, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<1>),
    #endif
  #endif

  #if ENABLED(EDITABLE_STEPS_PER_UNIT)
    VPHELPER(VP_X_STEP_PER_MM, &planner.settings.axis_steps_per_mm[X_AXIS], ScreenHandler.HandleStepPerMMChanged, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<1>),
    VPHELPER(VP_Y_STEP_PER_MM, &planner.settings.axis_steps_per_mm[Y_AXIS], ScreenHandler.HandleStepPerMMChanged, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<1>),
    VPHELPER(VP_Z_STEP_PER_MM, &planner.settings.axis_steps_per_mm[Z_AXIS], ScreenHandler.HandleStepPerMMChanged, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<1>),
    #if HAS_HOTEND
      VPHELPER(VP_E0_STEP_PER_MM, &planner.settings.axis_steps_per_mm[E_AXIS_N(0)], ScreenHandler.HandleStepPerMMExtruderChanged, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<1>),
      #if HAS_MULTI_HOTEND
        VPHELPER(VP_E1_STEP_PER_MM, &planner.settings.axis_steps_per_mm[E_AXIS_N(1)], ScreenHandler.HandleStepPerMMExtruderChanged, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<1>),
      #endif
    #endif
  #endif

  // SDCard File listing.
  #if HAS_MEDIA
    VPHELPER(VP_SD_ScrollEvent, nullptr, ScreenHandler.DGUSLCD_SD_ScrollFilelist, nullptr),
    VPHELPER(VP_SD_FileSelected, nullptr, ScreenHandler.DGUSLCD_SD_FileSelected, nullptr),
    VPHELPER(VP_SD_FileSelectConfirm, nullptr, ScreenHandler.DGUSLCD_SD_StartPrint, nullptr),
    VPHELPER_STR(VP_SD_FileName0, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename),
    VPHELPER_STR(VP_SD_FileName1, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename),
    VPHELPER_STR(VP_SD_FileName2, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename),
    VPHELPER_STR(VP_SD_FileName3, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename),
    VPHELPER_STR(VP_SD_FileName4, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename),

    VPHELPER(VP_FileName_BUTTON, nullptr, ScreenHandler.DGUSLCD_SD_SendColorFilename,nullptr),
    VPHELPER(VP_FileName_EN_BUTTON, nullptr, ScreenHandler.DGUSLCD_SD_SendColorFilename,nullptr),
    // VPHELPER(VP_FileName_ES_BUTTON, nullptr, ScreenHandler.DGUSLCD_SD_SendColorFilename,nullptr),
    // VPHELPER(VP_FileName_FR_BUTTON, nullptr, ScreenHandler.DGUSLCD_SD_SendColorFilename,nullptr),
    // VPHELPER(VP_FileName_DE_BUTTON, nullptr, ScreenHandler.DGUSLCD_SD_SendColorFilename,nullptr),
    // VPHELPER(VP_FileName_PY_BUTTON, nullptr, ScreenHandler.DGUSLCD_SD_SendColorFilename,nullptr),
    // VPHELPER(VP_FileName1_BUTTON, nullptr, ScreenHandler.DGUSLCD_SD_SendColorFilename,nullptr),
    // VPHELPER(VP_FileName2_BUTTON, nullptr, ScreenHandler.DGUSLCD_SD_SendColorFilename,nullptr),
    // VPHELPER(VP_FileName3_BUTTON, nullptr, ScreenHandler.DGUSLCD_SD_SendColorFilename,nullptr),
    // VPHELPER(VP_FileName4_BUTTON, nullptr, ScreenHandler.DGUSLCD_SD_SendColorFilename,nullptr),

    VPHELPER(VP_SD_POWER_LESS_BUTTON, nullptr, ScreenHandler.DGUSLCD_SD_PowerLess_Recovery, nullptr),
    VPHELPER(VP_SD_FIL_PAUSE_BUTTON, nullptr, ScreenHandler.DGUSLCD_FIL_PAUSE, nullptr),

    VPHELPER(VP_SD_ResumePauseAbort, nullptr, ScreenHandler.DGUSLCD_SD_ResumePauseAbort, nullptr),

    VPHELPER(VP_SD_AbortPrintConfirmed, nullptr, ScreenHandler.DGUSLCD_SD_ReallyAbort, nullptr),
    VPHELPER(VP_SD_Print_Setting, nullptr, ScreenHandler.DGUSLCD_SD_PrintTune, nullptr),
    #if HAS_BED_PROBE
      // VPHELPER(VP_SD_Print_ProbeOffsetZ, &probe.offset.z, ScreenHandler.HandleProbeOffsetZChanged, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<2>),
      VPHELPER(VP_ProbeOffsetZ, &probe.offset.z, nullptr, ScreenHandler.HandleShowZOffSets<2>),
      VPHELPER(VP_ProbeOffsetZ_PRINTING, &probe.offset.z, nullptr, ScreenHandler.HandleShowZOffSets<2>),
      VPHELPER(VP_LEVEL_BUTTON, nullptr, ScreenHandler.HandleManualLevel, nullptr),
      VPHELPER(VP_Z_OFFSET_BUTTON, nullptr, ScreenHandler.HandleManualZOffSet,nullptr),
      #if ENABLED(BABYSTEPPING)
        VPHELPER(VP_SD_Print_LiveAdjustZ, nullptr, ScreenHandler.HandleLiveAdjustZ, nullptr),
      #endif
    #endif
  #endif

  #if ENABLED(DGUS_UI_WAITING)
    VPHELPER(VP_WAITING_STATUS, nullptr, nullptr, ScreenHandler.DGUSLCD_SendWaitingStatusToDisplay),
  #endif

  // Messages for the User, shared by the popup and the kill screen. They can't be autouploaded as we do not buffer content.
  { .VP = VP_MSGSTR1, .memadr = nullptr, .size = VP_MSGSTR1_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplayPGM },
  { .VP = VP_MSGSTR2, .memadr = nullptr, .size = VP_MSGSTR2_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplayPGM },
  { .VP = VP_MSGSTR3, .memadr = nullptr, .size = VP_MSGSTR3_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplayPGM },
  { .VP = VP_MSGSTR4, .memadr = nullptr, .size = VP_MSGSTR4_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplayPGM },

  VPHELPER(0, 0, 0, 0)  // must be last entry.
};

#endif // DGUS_LCD_UI_ORIGIN
