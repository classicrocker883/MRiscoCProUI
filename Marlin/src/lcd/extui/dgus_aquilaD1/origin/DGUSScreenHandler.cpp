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

#include "../../../../inc/MarlinConfigPre.h"

#if DGUS_LCD_UI_ORIGIN

#include "../DGUSScreenHandler.h"

#include "../../../../MarlinCore.h"
#include "../../../../gcode/queue.h"
#include "../../../../libs/duration_t.h"
#include "../../../../libs/BL24CXX.h"
#include "../../../../module/settings.h"
#include "../../../../module/temperature.h"
#include "../../../../module/motion.h"
#include "../../../../module/planner.h"
#include "../../../../module/printcounter.h"
#include "../../../../sd/cardreader.h"

#if ENABLED(POWER_LOSS_RECOVERY)
  #include "../../../../feature/powerloss.h"
#endif

extern uint8_t load_flag, unload_flag;

#if HAS_MEDIA

  extern ExtUI::FileList filelist;
  //static

  void DGUSScreenHandler::DGUSLCD_SD_FileSelected(DGUS_VP_Variable &var, void *val_ptr) {
    uint16_t touched_nr = (int16_t)swap16(*(uint16_t*)val_ptr) + top_file;
    if (touched_nr > filelist.count()) return;
    if (!filelist.seek(touched_nr)) return;

    if (filelist.isDir()) {
      filelist.changeDir(filelist.filename());
      top_file = 0;
      ForceCompleteUpdate();
      return;
    }

    #if ENABLED(DGUS_PRINT_FILENAME)
      // Send print filename
      dgusdisplay.WriteVariable(VP_SD_Print_Filename, filelist.filename(), VP_SD_FileName_LEN, true);
    #endif

    // Setup Confirmation screen
    file_to_print = touched_nr;

    // HandleUserConfirmationPopUp(VP_SD_FileSelectConfirm, nullptr, PSTR("Print file"), filelist.filename(), PSTR("from SD Card?"), true, true, false, true);
  }

  void DGUSScreenHandler::DGUSLCD_SD_StartPrint(DGUS_VP_Variable &var, void *val_ptr) {
    if (!filelist.seek(file_to_print)) return;
    feedrate_percentage = 100 ;
    ExtUI::printFile(filelist.shortFilename());
  }

 void DGUSScreenHandler::DGUSLCD_FIL_PAUSE(DGUS_VP_Variable &var, void *val_ptr) {
    static uint8_t FIL_RUNOUT_FLAG;
    uint16_t value = swap16(*(uint16_t*)val_ptr);
    FIL_RUNOUT_FLAG = READ(PA0);
    if(FIL_RUNOUT_FLAG==false)
    {
          if(value==1)
          {
                 ExtUI::stopPrint();
                lcd_info.Screen_now =  Screen_abort;
                if(lcd_info.language == (language_t)1)
                ScreenHandler.GotoScreen(DGUSLCD_SCREEN_SDFILELIST);
                else if(lcd_info.language == (language_t)2)
                ScreenHandler.GotoScreen(DGUSLCD_SCREEN_EN_SDFILELIST);
                else if(lcd_info.language ==(language_t)3)
                ScreenHandler.GotoScreen(DGUSLCD_Screens(76));
                else if(lcd_info.language ==(language_t)4)
                ScreenHandler.GotoScreen(DGUSLCD_Screens(116));
                else if(lcd_info.language ==(language_t)5)
                ScreenHandler.GotoScreen(DGUSLCD_Screens(151));
                else if(lcd_info.language ==(language_t)6)
                ScreenHandler.GotoScreen(DGUSLCD_Screens(191));
          }
          else if(value==2)
          {
                  lcd_info.Screen_now =  Screen_pause;
                  if(lcd_info.language == (language_t)1)
                  GotoScreen(DGUSLCD_SCREEN_PRINTING);
                  else if(lcd_info.language == (language_t)2)
                  GotoScreen(DGUSLCD_SCREEN_EN_PRINTING);
                  else if(lcd_info.language == (language_t)3)
                  GotoScreen(DGUSLCD_SCREEN_ES_PRINTING);
                  else if(lcd_info.language == (language_t)4)
                  GotoScreen(DGUSLCD_SCREEN_FR_PRINTING);
                  else if(lcd_info.language == (language_t)5)
                  GotoScreen(DGUSLCD_SCREEN_DE_PRINTING);
                  else if(lcd_info.language == (language_t)6)
                  GotoScreen(DGUSLCD_SCREEN_PY_PRINTING);
              if (ExtUI::isPrintingFromMediaPaused()) {
                  ExtUI::resumePrint();
                  if(lcd_info.language == (language_t)1)
                  dgusdisplay.WriteVariable(0x5500,(uint16_t)2);
                  else if(lcd_info.language ==(language_t)2)
                  dgusdisplay.WriteVariable(0x5510,(uint16_t)2);
                  if(lcd_info.language == (language_t)3)
                  dgusdisplay.WriteVariable(0x5520,(uint16_t)2);
                  else if(lcd_info.language ==(language_t)4)
                  dgusdisplay.WriteVariable(0x5530,(uint16_t)2);
                  else if(lcd_info.language ==(language_t)5)
                  dgusdisplay.WriteVariable(0x5540,(uint16_t)2);
                  else if(lcd_info.language ==(language_t)6)
                  dgusdisplay.WriteVariable(0x5550,(uint16_t)2);
                }

          }
    }
    else
    {
          if(value==1)
          {
              ExtUI::stopPrint();
            lcd_info.Screen_now = Screen_abort;
            if(lcd_info.language == (language_t)1)
            ScreenHandler.GotoScreen(DGUSLCD_Screens(30));
            else if(lcd_info.language == (language_t)2)
            ScreenHandler.GotoScreen(DGUSLCD_Screens(66));
            else if(lcd_info.language == (language_t)3)
            ScreenHandler.GotoScreen(DGUSLCD_Screens(103));
            else if(lcd_info.language == (language_t)4)
            ScreenHandler.GotoScreen(DGUSLCD_Screens(140));
            else if(lcd_info.language == (language_t)5)
            ScreenHandler.GotoScreen(DGUSLCD_Screens(177));
            else if(lcd_info.language == (language_t)6)
            ScreenHandler.GotoScreen(DGUSLCD_Screens(215));
          }
    }
  }


  void DGUSScreenHandler::SDPrintingFinished() {
      queue.exhaust();
      gcode.process_subcommands_now(F("M81"));

  }

 void DGUSScreenHandler::DGUSLCD_SD_PowerLess_Recovery(DGUS_VP_Variable &var, void *val_ptr) {

    uint16_t value = swap16(*(uint16_t*)val_ptr);
    char temp_str[20];
      if(value==1)
      {
          TERN_(POWER_LOSS_RECOVERY, recovery.cancel());
           ExtUI::stopPrint();
           if(lcd_info.language == (language_t)1)
          GotoScreen(DGUSLCD_SCREEN_SDFILELIST);
          else if(lcd_info.language ==(language_t)2)
          GotoScreen(DGUSLCD_SCREEN_EN_SDFILELIST);
          else if(lcd_info.language ==(language_t)3)
          GotoScreen(DGUSLCD_SCREEN_ES_SDFILELIST);
           else if(lcd_info.language ==(language_t)4)
          GotoScreen(DGUSLCD_SCREEN_FR_SDFILELIST);
           else if(lcd_info.language ==(language_t)5)
          GotoScreen(DGUSLCD_SCREEN_DE_SDFILELIST);
           else if(lcd_info.language ==(language_t)6)
          GotoScreen(DGUSLCD_SCREEN_PY_SDFILELIST);

      }
      else if(value==2)
      {
        if(lcd_info.language == (language_t)1)
        GotoScreen(DGUSLCD_SCREEN_PRINTING);
        else if(lcd_info.language ==(language_t)2)
        GotoScreen(DGUSLCD_SCREEN_EN_PRINTING);
        else if(lcd_info.language ==(language_t)3)
        GotoScreen(DGUSLCD_SCREEN_ES_PRINTING);
        else if(lcd_info.language ==(language_t)4)
        GotoScreen(DGUSLCD_SCREEN_FR_PRINTING);
        else if(lcd_info.language ==(language_t)5)
        GotoScreen(DGUSLCD_SCREEN_DE_PRINTING);
        else if(lcd_info.language ==(language_t)6)
        GotoScreen(DGUSLCD_SCREEN_PY_PRINTING);
        feedrate_percentage = 100;

          const uint16_t fileCnt = card.get_num_items();
          for (uint16_t i = 0; i < fileCnt; i++) {
            // TODO: Resume print via M1000 then update the UI
            // with the active filename which can come from CardReader.
            card.selectFileByIndexSorted(i);
            if (!strcmp(card.filename, &recovery.info.sd_filename[1])) { // Resume print before power failure while have the same file

              char * const name = card.longest_filename();

              dgusdisplay.WriteVariable(VP_SHOW_PRINT_FILE, name, VP_SD_FileName_LEN, true);
              break;
            }
          }
          recovery.resume();
        if(lcd_info.language == (language_t)1)
        dgusdisplay.WriteVariable(0x5500,(uint16_t)2);
        else if(lcd_info.language ==(language_t)2)
        dgusdisplay.WriteVariable(0x5510,(uint16_t)2);
        if(lcd_info.language == (language_t)3)
        dgusdisplay.WriteVariable(0x5520,(uint16_t)2);
        else if(lcd_info.language ==(language_t)4)
        dgusdisplay.WriteVariable(0x5530,(uint16_t)2);
        else if(lcd_info.language ==(language_t)5)
        dgusdisplay.WriteVariable(0x5540,(uint16_t)2);
        else if(lcd_info.language ==(language_t)6)
        dgusdisplay.WriteVariable(0x5550,(uint16_t)2);
      }
  }

xyz_pos_t position_before_pause;
constexpr feedRate_t park_speed_xy = TERN(NOZZLE_PARK_FEATURE, NOZZLE_PARK_XY_FEEDRATE, 100),
                     park_speed_z  = TERN(NOZZLE_PARK_FEATURE, NOZZLE_PARK_Z_FEEDRATE,    5);

 void DGUSScreenHandler::pause_print_move() {
  if( lcd_info.Screen_now ==  Screen_pause)
  {
      queue.exhaust();
      position_before_pause = current_position;
      // Save the current position, the raise amount, and 'already raised'
      // TERN_(POWER_LOSS_RECOVERY, if (recovery.enabled) recovery.save(true, mks_park_pos.z, true));

      // destination.z = _MIN(current_position.z + mks_park_pos.z, Z_MAX_POS);
      // prepare_internal_move_to_destination(park_speed_z);

      destination.set(X_MIN_POS , Y_MIN_POS);
      prepare_internal_move_to_destination(park_speed_xy);
      lcd_info.Screen_now =  Screen_null;
  }
}

void DGUSScreenHandler::resume_print_move() {
   if( lcd_info.Screen_now ==  Screen_pause)
   {
      destination.set(position_before_pause.x, position_before_pause.y);
      prepare_internal_move_to_destination(park_speed_xy);
      // destination.z = position_before_pause.z;
      // prepare_internal_move_to_destination(park_speed_z);
      TERN_(POWER_LOSS_RECOVERY, if (recovery.enabled) recovery.save(true));
      lcd_info.Screen_now =  Screen_null;
   }
}

  void DGUSScreenHandler::DGUSLCD_SD_ResumePauseAbort(DGUS_VP_Variable &var, void *val_ptr) {
    if (!ExtUI::isPrintingFromMedia()) return; // avoid race condition when user stays in this menu and printer finishes.
    switch (swap16(*(uint16_t*)val_ptr)) {
      case 0:  // Resume
        if (ExtUI::isPrintingFromMediaPaused()) {
          ExtUI::resumePrint();
        }
       break;
      case 1: // Pause
        if (!ExtUI::isPrintingFromMediaPaused()) {
           lcd_info.Screen_now =  Screen_pause;
          ExtUI::pausePrint();
          if(lcd_info.language == (language_t)1)
          {
             GotoScreen(DGUSLCD_SCREEN_PRINTING);
             dgusdisplay.WriteVariable(0x5500,(uint16_t)0);
          }
          else if(lcd_info.language == (language_t)2)
          {
             GotoScreen(DGUSLCD_SCREEN_EN_PRINTING);
              dgusdisplay.WriteVariable(0x5510,(uint16_t)0);
          }
          else if(lcd_info.language == (language_t)3)
          {
             GotoScreen(DGUSLCD_SCREEN_ES_PRINTING);
              dgusdisplay.WriteVariable(0x5520,(uint16_t)0);
          }
           else if(lcd_info.language == (language_t)4)
          {
             GotoScreen(DGUSLCD_SCREEN_FR_PRINTING);
              dgusdisplay.WriteVariable(0x5530,(uint16_t)0);
          }
            else if(lcd_info.language == (language_t)5)
          {
             GotoScreen(DGUSLCD_SCREEN_DE_PRINTING);
              dgusdisplay.WriteVariable(0x5540,(uint16_t)0);
          }
            else if(lcd_info.language == (language_t)6)
          {
             GotoScreen(DGUSLCD_SCREEN_PY_PRINTING);
              dgusdisplay.WriteVariable(0x5550,(uint16_t)0);
          }
        }
        else{
          lcd_info.Screen_now =  Screen_pause;
          ExtUI::resumePrint();
          if(lcd_info.language == (language_t)1)
          {
              GotoScreen(DGUSLCD_SCREEN_PRINTING);
              dgusdisplay.WriteVariable(0x5500,(uint16_t)2);
          }
          else if(lcd_info.language == (language_t)2)
          {
            GotoScreen(DGUSLCD_SCREEN_EN_PRINTING);
            dgusdisplay.WriteVariable(0x5510,(uint16_t)2);
          }
            else if(lcd_info.language == (language_t)3)
          {
             GotoScreen(DGUSLCD_SCREEN_ES_PRINTING);
              dgusdisplay.WriteVariable(0x5520,(uint16_t)2);
          }
           else if(lcd_info.language == (language_t)4)
          {
             GotoScreen(DGUSLCD_SCREEN_FR_PRINTING);
              dgusdisplay.WriteVariable(0x5530,(uint16_t)2);
          }
            else if(lcd_info.language == (language_t)5)
          {
             GotoScreen(DGUSLCD_SCREEN_DE_PRINTING);
              dgusdisplay.WriteVariable(0x5540,(uint16_t)2);
          }
            else if(lcd_info.language == (language_t)6)
          {
             GotoScreen(DGUSLCD_SCREEN_PY_PRINTING);
              dgusdisplay.WriteVariable(0x5550,(uint16_t)2);
          }
        }
        break;
      case 2: // Abort
           ExtUI::stopPrint();
          lcd_info.Screen_now = Screen_abort;
     if(lcd_info.language == (language_t)1)
      ScreenHandler.GotoScreen(DGUSLCD_Screens(30));
      else if(lcd_info.language == (language_t)2)
      ScreenHandler.GotoScreen(DGUSLCD_Screens(66));
      else if(lcd_info.language == (language_t)3)
      ScreenHandler.GotoScreen(DGUSLCD_Screens(103));
      else if(lcd_info.language == (language_t)4)
      ScreenHandler.GotoScreen(DGUSLCD_Screens(140));
      else if(lcd_info.language == (language_t)5)
      ScreenHandler.GotoScreen(DGUSLCD_Screens(177));
      else if(lcd_info.language == (language_t)6)
      ScreenHandler.GotoScreen(DGUSLCD_Screens(215));
          // GotoScreen(DGUSLCD_SCREEN_SDFILELIST);
        break;
        default:
        break;
    }
  }

  void DGUSScreenHandler::DGUSLCD_SD_SendColorFilename(DGUS_VP_Variable& var, void *val_ptr) {
      if (!filelist.seek(file_to_print)) return;
      char tmpfilename[VP_SD_FileName_LEN + 1] = "";
      int16_t file_num = swap16(*(uint16_t*)val_ptr);
      switch (file_num)
      {
      case 1/* constant-expression */:
        /* code */
            if (filelist.seek(top_file + 0)) {
            snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename()); // snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename());
            }
            ExtUI::printFile(filelist.shortFilename());
            if(lcd_info.language == (language_t)1)
            GotoScreen(DGUSLCD_SCREEN_PRINTING);
            else if(lcd_info.language == (language_t)2)
            GotoScreen(DGUSLCD_SCREEN_EN_PRINTING);
            else if(lcd_info.language == (language_t)3)
            GotoScreen(DGUSLCD_SCREEN_ES_PRINTING);
            else if(lcd_info.language == (language_t)4)
            GotoScreen(DGUSLCD_SCREEN_FR_PRINTING);
            else if(lcd_info.language == (language_t)5)
            GotoScreen(DGUSLCD_SCREEN_DE_PRINTING);
            else if(lcd_info.language == (language_t)6)
            GotoScreen(DGUSLCD_SCREEN_PY_PRINTING);
            dgusdisplay.WriteVariable(VP_SHOW_PRINT_FILE, tmpfilename, VP_SD_FileName_LEN, true);

        break;
      case 2:
        if (filelist.seek(top_file + 1)) {
            snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename()); // snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename());
            }

            ExtUI::printFile(filelist.shortFilename());
              if(lcd_info.language == (language_t)1)
            GotoScreen(DGUSLCD_SCREEN_PRINTING);
            else if(lcd_info.language == (language_t)2)
            GotoScreen(DGUSLCD_SCREEN_EN_PRINTING);
            else if(lcd_info.language == (language_t)3)
            GotoScreen(DGUSLCD_SCREEN_ES_PRINTING);
            else if(lcd_info.language == (language_t)4)
            GotoScreen(DGUSLCD_SCREEN_FR_PRINTING);
            else if(lcd_info.language == (language_t)5)
            GotoScreen(DGUSLCD_SCREEN_DE_PRINTING);
            else if(lcd_info.language == (language_t)6)
            GotoScreen(DGUSLCD_SCREEN_PY_PRINTING);
            dgusdisplay.WriteVariable(VP_SHOW_PRINT_FILE, tmpfilename, VP_SD_FileName_LEN, true);
      break;
      case 3:
          if (filelist.seek(top_file + 2)) {
            snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename()); // snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename());
            }
            ExtUI::printFile(filelist.shortFilename());
                if(lcd_info.language == (language_t)1)
            GotoScreen(DGUSLCD_SCREEN_PRINTING);
            else if(lcd_info.language == (language_t)2)
            GotoScreen(DGUSLCD_SCREEN_EN_PRINTING);
            else if(lcd_info.language == (language_t)3)
            GotoScreen(DGUSLCD_SCREEN_ES_PRINTING);
            else if(lcd_info.language == (language_t)4)
            GotoScreen(DGUSLCD_SCREEN_FR_PRINTING);
            else if(lcd_info.language == (language_t)5)
            GotoScreen(DGUSLCD_SCREEN_DE_PRINTING);
            else if(lcd_info.language == (language_t)6)
            GotoScreen(DGUSLCD_SCREEN_PY_PRINTING);
            dgusdisplay.WriteVariable(VP_SHOW_PRINT_FILE, tmpfilename, VP_SD_FileName_LEN, true);
      break;
      case 4:
             if (filelist.seek(top_file + 3)) {
            snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename()); // snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename());
            }
            ExtUI::printFile(filelist.shortFilename());
              if(lcd_info.language == (language_t)1)
            GotoScreen(DGUSLCD_SCREEN_PRINTING);
            else if(lcd_info.language == (language_t)2)
            GotoScreen(DGUSLCD_SCREEN_EN_PRINTING);
            else if(lcd_info.language == (language_t)3)
            GotoScreen(DGUSLCD_SCREEN_ES_PRINTING);
            else if(lcd_info.language == (language_t)4)
            GotoScreen(DGUSLCD_SCREEN_FR_PRINTING);
            else if(lcd_info.language == (language_t)5)
            GotoScreen(DGUSLCD_SCREEN_DE_PRINTING);
            else if(lcd_info.language == (language_t)6)
            GotoScreen(DGUSLCD_SCREEN_PY_PRINTING);
            dgusdisplay.WriteVariable(VP_SHOW_PRINT_FILE, tmpfilename, VP_SD_FileName_LEN, true);
      break;
      case 5:
            if (filelist.seek(top_file + 4)) {
            snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename()); // snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename());
            }
            ExtUI::printFile(filelist.shortFilename());
             if(lcd_info.language == (language_t)1)
            GotoScreen(DGUSLCD_SCREEN_PRINTING);
            else if(lcd_info.language == (language_t)2)
            GotoScreen(DGUSLCD_SCREEN_EN_PRINTING);
            else if(lcd_info.language == (language_t)3)
            GotoScreen(DGUSLCD_SCREEN_ES_PRINTING);
            else if(lcd_info.language == (language_t)4)
            GotoScreen(DGUSLCD_SCREEN_FR_PRINTING);
            else if(lcd_info.language == (language_t)5)
            GotoScreen(DGUSLCD_SCREEN_DE_PRINTING);
            else if(lcd_info.language == (language_t)6)
            GotoScreen(DGUSLCD_SCREEN_PY_PRINTING);
            dgusdisplay.WriteVariable(VP_SHOW_PRINT_FILE, tmpfilename, VP_SD_FileName_LEN, true);
      break;
      default:
        break;
      }
      if(lcd_info.language == (language_t)1)
      dgusdisplay.WriteVariable(0x5500,(uint16_t)2);
      else if(lcd_info.language ==(language_t)2)
      dgusdisplay.WriteVariable(0x5510,(uint16_t)2);
       if(lcd_info.language == (language_t)3)
      dgusdisplay.WriteVariable(0x5520,(uint16_t)2);
      else if(lcd_info.language ==(language_t)4)
      dgusdisplay.WriteVariable(0x5530,(uint16_t)2);
      else if(lcd_info.language ==(language_t)5)
      dgusdisplay.WriteVariable(0x5540,(uint16_t)2);
       else if(lcd_info.language ==(language_t)6)
      dgusdisplay.WriteVariable(0x5550,(uint16_t)2);
  }

  void DGUSScreenHandler::DGUSLCD_SD_SendFilename(DGUS_VP_Variable& var) {
    uint16_t target_line = (var.VP - VP_SD_FileName0) / VP_SD_FileName_LEN;
    // DEBUG_ECHOPGM("target_line", target_line);
    if (target_line >DGUS_SD_FILESPERSCREEN) return;
    char tmpfilename[VP_SD_FileName_LEN + 1] = "";
    var.memadr = (void*)tmpfilename;
    // DEBUG_ECHOPGM(" var.memadr", tmpfilename);
    if(card.get_num_items())
    {
        if (filelist.seek(top_file + target_line)) {
          snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename()); // snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename());
        }
    }
    else
    {
      snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s")," "); // snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename());
    }
    DGUSLCD_SendStringToDisplay(var);
  }

  void DGUSScreenHandler::SDCardInserted() {
    top_file = 0;
    filelist.refresh();

    auto cs = getCurrentScreen();
    if (cs == DGUSLCD_SCREEN_MAIN )
    {
        if(lcd_info.language == (language_t)1)
        GotoScreen(DGUSLCD_SCREEN_SDFILELIST);
        else if(lcd_info.language == (language_t)2)
        GotoScreen((DGUSLCD_Screens)41);
        else if(lcd_info.language == (language_t)3)
        GotoScreen((DGUSLCD_Screens)76);
        else if(lcd_info.language == (language_t)4)
        GotoScreen((DGUSLCD_Screens)116);
        else if(lcd_info.language == (language_t)5)
        GotoScreen((DGUSLCD_Screens)151);
        else if(lcd_info.language == (language_t)6)
        GotoScreen(DGUSLCD_SCREEN_PY_SDFILELIST);
    }
  }

  void DGUSScreenHandler::SDCardRemoved() {
    if (current_screen == DGUSLCD_SCREEN_SDFILELIST
        // || (current_screen == DGUSLCD_SCREEN_CONFIRM && (ConfirmVP == VP_SD_AbortPrintConfirmed || ConfirmVP == VP_SD_FileSelectConfirm))
        // || current_screen == DGUSLCD_SCREEN_SDPRINTMANIPULATION
    )
    {
      GotoScreen(DGUSLCD_SCREEN_MAIN);
    }
      if(current_screen == DGUSLCD_SCREEN_PRINTING)
      GotoScreen(DGUSLCD_SCREEN_MAIN);
      else if(current_screen == DGUSLCD_SCREEN_EN_PRINTING)
      GotoScreen(DGUSLCD_SCREEN_EN_MAIN);
      else if(current_screen == DGUSLCD_SCREEN_DE_PRINTING)
      GotoScreen(DGUSLCD_SCREEN_DE_MAIN);
      else if(current_screen == DGUSLCD_SCREEN_ES_PRINTING)
      GotoScreen(DGUSLCD_SCREEN_ES_MAIN);
      else if(current_screen == DGUSLCD_SCREEN_PY_PRINTING)
      GotoScreen(DGUSLCD_SCREEN_PY_MAIN);
      else if(current_screen == DGUSLCD_SCREEN_FR_PRINTING)
      GotoScreen(DGUSLCD_SCREEN_FR_MAIN);

  }

#endif // SDSUPPORT

void DGUSScreenHandler::ScreenChangeHook(DGUS_VP_Variable &var, void *val_ptr) {
  uint8_t *tmp = (uint8_t*)val_ptr;

  // The keycode in target is coded as <from-frame><to-frame>, so 0x0100A means
  // from screen 1 (main) to 10 (temperature). DGUSLCD_SCREEN_POPUP is special,
  // meaning "return to previous screen"
  DGUSLCD_Screens target = (DGUSLCD_Screens)tmp[1];

  // DEBUG_ECHOLNPGM("\n DEBUG target", target);

  // if (target == DGUSLCD_SCREEN_POPUP) {
  //   // Special handling for popup is to return to previous menu
  //   if (current_screen == DGUSLCD_SCREEN_POPUP && confirm_action_cb) confirm_action_cb();
  //   PopToOldScreen();
  //   return;
  // }

  UpdateNewScreen(target);

  #ifdef DEBUG_DGUSLCD
    if (!DGUSLCD_FindScreenVPMapList(target)) DEBUG_ECHOLNPGM("WARNING: No screen Mapping found for ", target);
  #endif
}

void DGUSScreenHandler::HandleSendChangeScreen(DGUS_VP_Variable &var, void *val_ptr)
{

  int16_t movevalue = swap16(*(uint16_t*)val_ptr);
    if(lcd_info.level_start==1)
    {

    }
    else
    {
        dgusdisplay.RequestScreen(DGUSLCD_Screens(movevalue));
        UpdateNewScreen(DGUSLCD_Screens(movevalue), 0);
    }
}

#define DWIN_LANGUAGE_EEPROM_ADDRESS 0x01   // Between 0x01 and 0x63 (EEPROM_OFFSET-1)

void set_chinese_to_eeprom(void) {
  lcd_info.language = language_t(1);
  BL24CXX::write(DWIN_LANGUAGE_EEPROM_ADDRESS, (uint8_t*)&lcd_info.language, sizeof(lcd_info.language));
}

void set_english_to_eeprom(void) {
  lcd_info.language = language_t(2);
  BL24CXX::write(DWIN_LANGUAGE_EEPROM_ADDRESS, (uint8_t*)&lcd_info.language, sizeof(lcd_info.language));
}

void set_espanol_to_eeprom(void){
  lcd_info.language = language_t(3);
  BL24CXX::write(DWIN_LANGUAGE_EEPROM_ADDRESS, (uint8_t*)&lcd_info.language, sizeof(lcd_info.language));
}

void set_fran_to_eeprom(void){
  lcd_info.language = language_t(4);
  BL24CXX::write(DWIN_LANGUAGE_EEPROM_ADDRESS, (uint8_t*)&lcd_info.language, sizeof(lcd_info.language));
}

void set_deutsch_to_eeprom(void){
  lcd_info.language = language_t(5);
  BL24CXX::write(DWIN_LANGUAGE_EEPROM_ADDRESS, (uint8_t*)&lcd_info.language, sizeof(lcd_info.language));
}

void set_pycc_to_eeprom(void){
  lcd_info.language = language_t(6);
  BL24CXX::write(DWIN_LANGUAGE_EEPROM_ADDRESS, (uint8_t*)&lcd_info.language, sizeof(lcd_info.language));
}

void DGUSScreenHandler::lcd_select_language(void) {
  BL24CXX::read(DWIN_LANGUAGE_EEPROM_ADDRESS, (uint8_t*)&lcd_info.language, sizeof(lcd_info.language));

  if(lcd_info.language>6)
  {
     lcd_info.language = (language_t)1;
  }
      if(recovery.valid())
      {
          if(lcd_info.language == (language_t)1)
          {
            GotoScreen(DGUSLCD_SCREEN_POWER_LOSS);
          }
          else if(lcd_info.language == (language_t)2)
          {
            GotoScreen((DGUSLCD_Screens)69);
          }
           else if(lcd_info.language == (language_t)3)
          {
            GotoScreen((DGUSLCD_Screens)106);
          }
           else if(lcd_info.language == (language_t)4)
          {
            GotoScreen((DGUSLCD_Screens)145);
          }
             else if(lcd_info.language == (language_t)5)
          {
            GotoScreen((DGUSLCD_Screens)180);
          }
          else if(lcd_info.language == (language_t)6)
          {
            GotoScreen(DGUSLCD_SCREEN_PY_POWER_LOSS);
          }
      }
      else
      {
          if(lcd_info.language == (language_t)1)
          {
            GotoScreen(DGUSLCD_SCREEN_MAIN);
          }
          else if(lcd_info.language == (language_t)2)
          {
            GotoScreen((DGUSLCD_Screens)40);
          }
          else if(lcd_info.language == (language_t)3)
          {
            GotoScreen((DGUSLCD_Screens)75);
          }
           else if(lcd_info.language == (language_t)4)
          {
            GotoScreen((DGUSLCD_Screens)115);
          }
           else if(lcd_info.language == (language_t)5)
          {
            GotoScreen((DGUSLCD_Screens)150);
          }
           else if(lcd_info.language == (language_t)6)
          {
             GotoScreen(DGUSLCD_SCREEN_PY_MAIN);
          }
      }
}

void DGUSScreenHandler::HandlelangScreen(DGUS_VP_Variable &var, void *val_ptr)
{

   int16_t page = swap16(*(uint16_t*)val_ptr);

   switch (page)
   {
          case 1:
                set_chinese_to_eeprom();
                dgusdisplay.RequestScreen(DGUSLCD_Screens(27));
                UpdateNewScreen(DGUSLCD_Screens(27), 0);

          break;
          case 2:
                set_english_to_eeprom();
                dgusdisplay.RequestScreen(DGUSLCD_Screens(63));
                UpdateNewScreen(DGUSLCD_Screens(63), 0);
          break;
          case 3:
                set_espanol_to_eeprom();
                dgusdisplay.RequestScreen(DGUSLCD_Screens(100));
                UpdateNewScreen(DGUSLCD_Screens(100), 0);
                break;
          case 4:
                set_fran_to_eeprom();
                dgusdisplay.RequestScreen(DGUSLCD_Screens(137));
                UpdateNewScreen(DGUSLCD_Screens(137), 0);
            break;
          case 5:
                set_deutsch_to_eeprom();
                dgusdisplay.RequestScreen(DGUSLCD_Screens(174));
                UpdateNewScreen(DGUSLCD_Screens(174), 0);
            break;
          case 6:
                set_pycc_to_eeprom();
                dgusdisplay.RequestScreen(DGUSLCD_Screens(214));
                UpdateNewScreen(DGUSLCD_Screens(214), 0);
            break;
          default:
          break;
   }

}

void DGUSScreenHandler::HandlePauseScreen(DGUS_VP_Variable &var, void *val_ptr)
{
    if (!ExtUI::isPrintingFromMediaPaused()) {

      if(lcd_info.language == (language_t)1)
      {
        dgusdisplay.RequestScreen(DGUSLCD_Screens(32));
        UpdateNewScreen(DGUSLCD_Screens(35), 2);
      }
      else if(lcd_info.language == (language_t)2)
      {
        dgusdisplay.RequestScreen(DGUSLCD_Screens(68));
          UpdateNewScreen(DGUSLCD_Screens(68), 0);
      }
      else if(lcd_info.language == (language_t)3)
      {
          dgusdisplay.RequestScreen(DGUSLCD_Screens(105));
          UpdateNewScreen(DGUSLCD_Screens(105), 0);
      }
      else if(lcd_info.language == (language_t)4)
      {
           dgusdisplay.RequestScreen(DGUSLCD_Screens(142));
          UpdateNewScreen(DGUSLCD_Screens(142), 0);
      }
      else if(lcd_info.language == (language_t)5)
      {
          dgusdisplay.RequestScreen(DGUSLCD_Screens(179));
          UpdateNewScreen(DGUSLCD_Screens(179), 0);
      }
      else if(lcd_info.language == (language_t)6)
      {
          dgusdisplay.RequestScreen(DGUSLCD_Screens(217));
          UpdateNewScreen(DGUSLCD_Screens(217), 0);
      }

    }
    else
    {

        if(lcd_info.language == (language_t)1)
        {
            dgusdisplay.RequestScreen(DGUSLCD_Screens(35));
            UpdateNewScreen(DGUSLCD_Screens(38), 0);
        }
        else if(lcd_info.language == (language_t)2)
        {
            dgusdisplay.RequestScreen(DGUSLCD_Screens(70));
            UpdateNewScreen(DGUSLCD_Screens(70), 0);
        }
        else if(lcd_info.language == (language_t)3)
        {
          dgusdisplay.RequestScreen(DGUSLCD_Screens(107));
          UpdateNewScreen(DGUSLCD_Screens(107), 0);
        }
        else if(lcd_info.language == (language_t)4)
        {
           dgusdisplay.RequestScreen(DGUSLCD_Screens(143));
          UpdateNewScreen(DGUSLCD_Screens(143), 0);
        }
        else if(lcd_info.language == (language_t)5)
        {
          dgusdisplay.RequestScreen(DGUSLCD_Screens(178));
          UpdateNewScreen(DGUSLCD_Screens(181), 0);
        }
        else if(lcd_info.language == (language_t)6)
        {
          dgusdisplay.RequestScreen(DGUSLCD_Screens(218));
          UpdateNewScreen(DGUSLCD_Screens(218), 0);
        }
    }
}



void DGUSScreenHandler::HandleSendCancelChangeScreen(DGUS_VP_Variable &var, void *val_ptr)
{

    load_flag=0;
    unload_flag=0;
    wait_for_heatup = false;
    thermalManager.disable_all_heaters();
    //queue.clear();
    // quickstop_stepper();
    quickstop_stepper();
    print_job_timer.stop();
    int16_t movevalue = swap16(*(uint16_t*)val_ptr);
    dgusdisplay.RequestScreen(DGUSLCD_Screens(movevalue));
    UpdateNewScreen(DGUSLCD_Screens(movevalue), 0);
}


void DGUSScreenHandler::HandleManualZOffSet(DGUS_VP_Variable &var, void *val_ptr)
{
      static float offset_temp;
      static long offset_z;
      int16_t   steps;


       int16_t offset = swap16(*(uint16_t*)val_ptr);
        switch (offset)
        {
        case 1/* constant-expression */:
            steps  =-20;
            ExtUI::smartAdjustAxis_steps(steps, ExtUI::axis_t::Z, true);
            ForceCompleteUpdate();
            offset_temp= ExtUI:: getZOffset_mm() ;
            if(offset_temp>=0)
            {
                offset_z = offset_temp*100+0.5;
            }
            else
            {
                offset_z = offset_temp*100-0.5;
            }
            settings.save();
            dgusdisplay.WriteVariable(VP_ProbeOffsetZ,(long)offset_z);
          break;
        case 2:
          steps =  20;
          ExtUI::smartAdjustAxis_steps(steps, ExtUI::axis_t::Z, true);
          ForceCompleteUpdate();
          offset_temp= ExtUI:: getZOffset_mm() ;
          if(offset_temp>=0)
          {
              offset_z = offset_temp*100+0.5;
          }
          else
          {
              offset_z = offset_temp*100-0.5;
          }
          settings.save();
          dgusdisplay.WriteVariable(VP_ProbeOffsetZ, (long)offset_z);
          break;
        case 3:
              offset_z = 0;
              gcode.process_subcommands_now(PSTR("M851 Z0"));
              gcode.process_subcommands_now(PSTR("G28 Z"));
              settings.save();
              dgusdisplay.WriteVariable(VP_ProbeOffsetZ, (long)offset_z);
          break;
        default:
          break;
        }
}

void DGUSScreenHandler::HandleManualFactory(DGUS_VP_Variable &var, void *val_ptr)
{
  int16_t movevalue = swap16(*(uint16_t*)val_ptr);
   settings.reset();
}


void DGUSScreenHandler::CompletedLeveling()
{
    dgusdisplay.WriteVariable(0x5270,(uint16_t)1);
}

void DGUSScreenHandler::HandleManualLevel(DGUS_VP_Variable &var, void *val_ptr)
{
      lcd_info.level_flag  = 1;
      lcd_info.level_pos = 0;
      lcd_info.level_start = 1;
      if(lcd_info.language == (language_t)1)
      {
        GotoScreen(DGUSLCD_SCREEN_LEVEL);
        dgusdisplay.WriteVariable(0x3300,(uint16_t)0);
      }
      else if(lcd_info.language == (language_t)2)
      {
        GotoScreen((DGUSLCD_Screens)DGUSLCD_SCREEN_EN_LEVEL);
        dgusdisplay.WriteVariable(0x3302,(uint16_t)0);
      }
      else if(lcd_info.language == (language_t)3)
      {
         GotoScreen((DGUSLCD_Screens)92);
         dgusdisplay.WriteVariable(0x3304,(uint16_t)0);
      }
      else if(lcd_info.language == (language_t)4)
      {
         GotoScreen((DGUSLCD_Screens)131);
          dgusdisplay.WriteVariable(0x3306,(uint16_t)0);
      }
        else if(lcd_info.language == (language_t)5)
      {
         GotoScreen((DGUSLCD_Screens)167);
          dgusdisplay.WriteVariable(0x3308,(uint16_t)0);
      }
        else if(lcd_info.language == (language_t)6)
      {
            GotoScreen((DGUSLCD_Screens)206);
            dgusdisplay.WriteVariable(0x330A,(uint16_t)0);
      }
      dgusdisplay.WriteVariable(0x5700,(uint16_t)0);
      queue.inject_P(PSTR("M851 Z0"));
      queue.enqueue_now_P(PSTR("G28"));
      queue.enqueue_now_P(PSTR("G29"));
      queue.enqueue_now_P(PSTR("M500"));
      queue.enqueue_now_P(PSTR("G28"));
      queue.enqueue_now_P(PSTR("M420 S1"));
      queue.enqueue_now_P(PSTR("M104 S0"));
      queue.enqueue_now_P(PSTR("M140 S0"));

}

void DGUSScreenHandler::HandleManualHome(DGUS_VP_Variable &var, void *val_ptr)
{

  int16_t movevalue = swap16(*(uint16_t*)val_ptr);
  lcd_info.Screen_now = Screen_control;
  queue.inject_P(PSTR("G28")); // G28 will set home_flag
  ExtUI::getAxisPosition_mm(ExtUI::axis_t::X);
  ExtUI::getAxisPosition_mm(ExtUI::axis_t::Y);
  ExtUI::getAxisPosition_mm(ExtUI::axis_t::Z);
  dgusdisplay.WriteVariable(0x3230, (long)current_position.x);
  dgusdisplay.WriteVariable(0x3234, (long)current_position.y);
  dgusdisplay.WriteVariable(0x3238, (long)current_position.z);
}

void DGUSScreenHandler::HandleManualMove(DGUS_VP_Variable &var, void *val_ptr) {
  // DEBUG_ECHOLNPGM("HandleManualMove");
  static float move_dis = 1.0f;
  int16_t movevalue = swap16(*(uint16_t*)val_ptr);


  #if ENABLED(DGUS_UI_MOVE_DIS_OPTION)
    if (movevalue) {
      const uint16_t choice = *(uint16_t*)var.memadr;
      movevalue = movevalue < 0 ? -choice : choice;
    }
  #endif
  char axiscode;
  unsigned int speed = 1500; // FIXME: get default feedrate for manual moves, don't hardcode.

  switch (var.VP) {
    default: return;
        case VP_MOVE_DIS_A_BUTTON:
              move_dis = 0.1f ;
        break;

         case VP_MOVE_DIS_B_BUTTON:
              move_dis = 1.0f ;
        break;

         case VP_MOVE_DIS_C_BUTTON:
               move_dis = 10.0f ;
        break;
    // case VP_MOVE_X:
    //   axiscode = 'X';
    //   if (!ExtUI::canMove(ExtUI::axis_t::X)) goto cannotmove;
    //   break;

    // case VP_MOVE_Y:
    //   axiscode = 'Y';
    //   if (!ExtUI::canMove(ExtUI::axis_t::Y)) goto cannotmove;
    //   break;

    // case VP_MOVE_Z:
    //   axiscode = 'Z';
    //   speed = 300; // default to 5mm/s
    //   if (!ExtUI::canMove(ExtUI::axis_t::Z)) goto cannotmove;
    //   break;

    // case VP_HOME_ALL: // only used for homing
    //   axiscode  = '\0';
    //   movevalue = 0; // ignore value sent from display, this VP is _ONLY_ for homing.
    //   break;
//     constexpr uint16_t VP_MOVE_X_Positive_BUTTON = 0x1501; // 2 Byte Integer4
// constexpr uint16_t VP_MOVE_X_Negative_BUTTON = 0x1502; // 2 Byte Integer4
// constexpr uint16_t VP_MOVE_Y_Positive_BUTTON = 0x1503; // 2 Byte Integer4
// constexpr uint16_t VP_MOVE_Y_Negative_BUTTON = 0x1504; // 2 Byte Integer4
// constexpr uint16_t VP_MOVE_Z_Positive_BUTTON = 0x1505; // 2 Byte Integer4
// constexpr uint16_t VP_MOVE_Z_Negative_BUTTON = 0x1506; // 2 Byte Integer4
    case VP_MOVE_X_Positive_BUTTON:
      if (!ExtUI::canMove(ExtUI::axis_t::X)) goto cannotmove;
       ExtUI::setAxisPosition_mm(ExtUI::getAxisPosition_mm(ExtUI::axis_t::X) + move_dis, ExtUI::axis_t::X, 50);

    break;
    case VP_MOVE_X_Negative_BUTTON:
      if (!ExtUI::canMove(ExtUI::axis_t::X)) goto cannotmove;
    ExtUI::setAxisPosition_mm(ExtUI::getAxisPosition_mm(ExtUI::axis_t::X) - move_dis, ExtUI::axis_t::X, 50);

    break;
    case VP_MOVE_Y_Positive_BUTTON:
      if (!ExtUI::canMove(ExtUI::axis_t::X)) goto cannotmove;
      ExtUI::setAxisPosition_mm(ExtUI::getAxisPosition_mm(ExtUI::axis_t::Y) + move_dis, ExtUI::axis_t::Y, 50);

    break;
    case VP_MOVE_Y_Negative_BUTTON:
      if (!ExtUI::canMove(ExtUI::axis_t::X)) goto cannotmove;
        ExtUI::setAxisPosition_mm(ExtUI::getAxisPosition_mm(ExtUI::axis_t::Y) - move_dis, ExtUI::axis_t::Y, 50);

    break;
    case VP_MOVE_Z_Positive_BUTTON:
      if (!ExtUI::canMove(ExtUI::axis_t::X)) goto cannotmove;
        ExtUI::setAxisPosition_mm(ExtUI::getAxisPosition_mm(ExtUI::axis_t::Z) + move_dis, ExtUI::axis_t::Z, 8);

    break;
    case VP_MOVE_Z_Negative_BUTTON:
      if (!ExtUI::canMove(ExtUI::axis_t::X)) goto cannotmove;
     ExtUI::setAxisPosition_mm(ExtUI::getAxisPosition_mm(ExtUI::axis_t::Z) - move_dis, ExtUI::axis_t::Z, 8);

    break;
  }
    ExtUI::getAxisPosition_mm(ExtUI::axis_t::X);
    ExtUI::getAxisPosition_mm(ExtUI::axis_t::Y);
    ExtUI::getAxisPosition_mm(ExtUI::axis_t::Z);
    dgusdisplay.WriteVariable(0x3230, (long)current_position.x);
    dgusdisplay.WriteVariable(0x3234, (long)current_position.y);
    dgusdisplay.WriteVariable(0x3238, (long)current_position.z);
  ForceCompleteUpdate();
  return;
  cannotmove:
    DEBUG_ECHOLNPGM(" cannot move ", C(axiscode));
    return;
}

#if HAS_PID_HEATING
  // void DGUSScreenHandler::HandleTemperaturePIDChanged(DGUS_VP_Variable &var, void *val_ptr) {
  //   uint16_t rawvalue = swap16(*(uint16_t*)val_ptr);
  //   DEBUG_ECHOLNPGM("V1:", rawvalue);
  //   float value = (float)rawvalue / 10;
  //   DEBUG_ECHOLNPGM("V2:", value);
  //   float newvalue = 0;

  //   switch (var.VP) {
  //     default: return;
  //       #if HAS_HOTEND
  //         case VP_E0_PID_P: newvalue = value; break;
  //         case VP_E0_PID_I: newvalue = scalePID_i(value); break;
  //         case VP_E0_PID_D: newvalue = scalePID_d(value); break;
  //       #endif
  //       #if HAS_MULTI_HOTEND
  //         case VP_E1_PID_P: newvalue = value; break;
  //         case VP_E1_PID_I: newvalue = scalePID_i(value); break;
  //         case VP_E1_PID_D: newvalue = scalePID_d(value); break;
  //       #endif
  //       #if HAS_HEATED_BED
  //         case VP_BED_PID_P: newvalue = value; break;
  //         case VP_BED_PID_I: newvalue = scalePID_i(value); break;
  //         case VP_BED_PID_D: newvalue = scalePID_d(value); break;
  //       #endif
  //   }

  //   DEBUG_ECHOLNPAIR_F("V3:", newvalue);
  //   *(float *)var.memadr = newvalue;

  //   skipVP = var.VP; // don't overwrite value the next update time as the display might autoincrement in parallel
  // }
#endif // HAS_PID_HEATING

#if ENABLED(BABYSTEPPING)
  void DGUSScreenHandler::HandleLiveAdjustZ(DGUS_VP_Variable &var, void *val_ptr) {
    int16_t flag  = swap16(*(uint16_t*)val_ptr),
            steps = flag ? -20 : 20;
    ExtUI::smartAdjustAxis_steps(steps, ExtUI::axis_t::Z, true);
    ForceCompleteUpdate();
  }
#endif

#if ENABLED(DGUS_FILAMENT_LOADUNLOAD)

  void DGUSScreenHandler::HandleFilamentOption(DGUS_VP_Variable &var, void *val_ptr) {
    DEBUG_ECHOLNPGM("HandleFilamentOption");

    uint8_t e_temp = 0;
    filament_data.heated = false;
    uint16_t preheat_option = swap16(*(uint16_t*)val_ptr);
    if (preheat_option <= 8) {      // Load filament type
      filament_data.action = 1;
    }
    else if (preheat_option >= 10) { // Unload filament type
      preheat_option -= 10;
      filament_data.action = 2;
      filament_data.purge_length = DGUS_FILAMENT_PURGE_LENGTH;
    }
    else {                          // Cancel filament operation
      filament_data.action = 0;
    }

    switch (preheat_option) {
      case 0: // Load PLA
        #ifdef PREHEAT_1_TEMP_HOTEND
          e_temp = PREHEAT_1_TEMP_HOTEND;
        #endif
        break;
      case 1: // Load ABS
        TERN_(PREHEAT_2_TEMP_HOTEND, e_temp = PREHEAT_2_TEMP_HOTEND);
        break;
      case 2: // Load PET
        #ifdef PREHEAT_3_TEMP_HOTEND
          e_temp = PREHEAT_3_TEMP_HOTEND;
        #endif
        break;
      case 3: // Load FLEX
        #ifdef PREHEAT_4_TEMP_HOTEND
          e_temp = PREHEAT_4_TEMP_HOTEND;
        #endif
        break;
      case 9: // Cool down
      default:
        e_temp = 0;
        break;
    }

    if (filament_data.action == 0) { // Go back to utility screen
      #if HAS_HOTEND
        thermalManager.setTargetHotend(e_temp, ExtUI::extruder_t::E0);
        #if HAS_MULTI_HOTEND
          thermalManager.setTargetHotend(e_temp, ExtUI::extruder_t::E1);
        #endif
      #endif
      GotoScreen(DGUSLCD_SCREEN_UTILITY);
    }
    else { // Go to the preheat screen to show the heating progress
      switch (var.VP) {
        default: return;
          #if HAS_HOTEND
            case VP_E0_FILAMENT_LOAD_UNLOAD:
              filament_data.extruder = ExtUI::extruder_t::E0;
              thermalManager.setTargetHotend(e_temp, filament_data.extruder);
              break;
          #endif
          #if HAS_MULTI_HOTEND
            case VP_E1_FILAMENT_LOAD_UNLOAD:
              filament_data.extruder = ExtUI::extruder_t::E1;
              thermalManager.setTargetHotend(e_temp, filament_data.extruder);
              break;
          #endif
      }
      GotoScreen(DGUSLCD_SCREEN_FILAMENT_HEATING);
    }
  }

  void DGUSScreenHandler::HandleFilamentLoadUnload(DGUS_VP_Variable &var) {
    DEBUG_ECHOLNPGM("HandleFilamentLoadUnload");
    if (filament_data.action <= 0) return;

    // If we close to the target temperature, we can start load or unload the filament
    if (thermalManager.hotEnoughToExtrude(filament_data.extruder) && \
        thermalManager.targetHotEnoughToExtrude(filament_data.extruder)) {
      float movevalue = DGUS_FILAMENT_LOAD_LENGTH_PER_TIME;

      if (filament_data.action == 1) { // load filament
        if (!filament_data.heated) {
          //GotoScreen(DGUSLCD_SCREEN_FILAMENT_LOADING);
          filament_data.heated = true;
        }
        movevalue = ExtUI::getAxisPosition_mm(filament_data.extruder) + movevalue;
      }
      else { // unload filament
        if (!filament_data.heated) {
          GotoScreen(DGUSLCD_SCREEN_FILAMENT_UNLOADING);
          filament_data.heated = true;
        }
        // Before unloading extrude to prevent jamming
        if (filament_data.purge_length >= 0) {
          movevalue = ExtUI::getAxisPosition_mm(filament_data.extruder) + movevalue;
          filament_data.purge_length -= movevalue;
        }
        else {
          movevalue = ExtUI::getAxisPosition_mm(filament_data.extruder) - movevalue;
        }
      }
      ExtUI::setAxisPosition_mm(movevalue, filament_data.extruder);
    }
  }
#endif // DGUS_FILAMENT_LOADUNLOAD

bool DGUSScreenHandler::loop() {
  dgusdisplay.loop();

  const millis_t ms = millis();
  static millis_t next_event_ms = 0;

  if (!IsScreenComplete() || ELAPSED(ms, next_event_ms)) {
    next_event_ms = ms + DGUS_UPDATE_INTERVAL_MS;
    UpdateScreenVPData();
  }

  #if ENABLED(SHOW_BOOTSCREEN)
    static bool booted = false;

    // if (!booted && TERN0(POWER_LOSS_RECOVERY, recovery.valid()))
    //   booted = true;

    if (!booted && ELAPSED(ms, BOOTSCREEN_TIMEOUT)) {
      booted = true;
      recovery.load();
      if(recovery.valid())
      {
          if(lcd_info.language == (language_t)1)
          {
            GotoScreen(DGUSLCD_SCREEN_POWER_LOSS);
          }
          else if(lcd_info.language == (language_t)2)
          {
            GotoScreen(DGUSLCD_SCREEN_EN_POWER_LOSS);
          }
           else if(lcd_info.language == (language_t)3)
          {
            GotoScreen((DGUSLCD_Screens)106);
          }
           else if(lcd_info.language == (language_t)4)
          {
            GotoScreen((DGUSLCD_Screens)145);
          }
           else if(lcd_info.language == (language_t)5)
          {
            GotoScreen((DGUSLCD_Screens)180);
          }
           else if(lcd_info.language == (language_t)6)
          {
            GotoScreen(DGUSLCD_SCREEN_PY_POWER_LOSS);
          }
      }
    }
  #endif

  return IsScreenComplete();
}

#endif // DGUS_LCD_UI_ORIGIN
