/**
 * DWIN Enhanced implementation for PRO UI
 * Based on the original work of: Miguel A. Risco-Castillo (MRISCOC)
 * Version: 3.12.1
 * Date: 2022/04/03
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#include "../../../inc/MarlinConfigPre.h"

#if ENABLED(DWIN_LCD_PROUI)

#include "../../../MarlinCore.h" // for wait_for_user
#include "dwin_popup.h"

popupDrawFunc_t Draw_Popup = nullptr;
popupClickFunc_t ClickPopup = nullptr;

uint16_t HighlightYPos = 280;

void Draw_Select_Highlight(const bool sel, const uint16_t ypos) {
  HighlightYPos = ypos;
  HMI_flag.select_flag = sel;
  const uint16_t c1 = sel ? HMI_data.Cursor_Color  : HMI_data.PopupBg_Color,
                 c2 = sel ? HMI_data.PopupBg_Color : HMI_data.Cursor_Color;
  DWIN_Draw_Rectangle(0, c1,  25, ypos - 1, 126, ypos + 38);
  DWIN_Draw_Rectangle(0, c1,  24, ypos - 2, 127, ypos + 39);
  DWIN_Draw_Rectangle(0, c2, 145, ypos - 1, 246, ypos + 38);
  DWIN_Draw_Rectangle(0, c2, 144, ypos - 2, 247, ypos + 39);
}

void Popup_ConfirmCancel(const uint8_t icon, FSTR_P const fmsg2) {
  DWIN_Show_Popup(icon, F("Please confirm"), fmsg2);
  DWINUI::Draw_Button(BTN_Confirm, 26, 280);
  DWINUI::Draw_Button(BTN_Cancel, 146, 280);
  Draw_Select_Highlight(HMI_flag.select_flag);
  DWIN_UpdateLCD();
}

#if ENABLED(ADVANCED_PAUSE_FEATURE)
  void Popup_Pause(FSTR_P const fmsg, uint8_t button/*=0*/) {
    HMI_SaveProcessID(button ? WaitResponse : NothingToDo);
    DWIN_Show_Popup(ICON_Pause_1, GET_TEXT_F(MSG_ADVANCED_PAUSE), fmsg, button);
  }
#endif

#if HAS_HOTEND || HAS_HEATED_BED || HAS_HEATED_CHAMBER
  void Popup_Temperature(const int_fast8_t heater_id, const uint8_t state) {
    HMI_SaveProcessID(WaitResponse);
    FSTR_P heaterstr = nullptr;
    if      (TERN0(HAS_HEATED_CHAMBER, heater_id == H_CHAMBER)) heaterstr = F("Chamber");
    else if (TERN0(HAS_HEATED_BED,     heater_id == H_BED))     heaterstr = F("Bed");
    else if (TERN0(HAS_HOTEND,         heater_id >= 0))         heaterstr = F("Nozzle");
    FSTR_P errorstr;
    uint8_t icon;
    switch (state) {
      case 0:  errorstr = GET_TEXT_F(DGUS_MSG_TEMP_TOO_LOW);       icon = ICON_TempTooLow;  break;
      case 1:  errorstr = GET_TEXT_F(DGUS_MSG_TEMP_TOO_HIGH);      icon = ICON_TempTooHigh; break;
      default: errorstr = GET_TEXT_F(MSG_ERR_HEATING_FAILED); icon = ICON_Info_1;      break; // May be thermal runaway, temp malfunction, etc.
    }
      Popup_Confirm(icon, heaterstr, errorstr);
  }
#endif

void Goto_Popup(const popupDrawFunc_t fnDraw, const popupClickFunc_t fnClick/*=nullptr*/) {
  Draw_Popup = fnDraw;
  ClickPopup = fnClick;
  HMI_SaveProcessID(Popup);
  HMI_flag.select_flag = false;
  Draw_Popup();
}

void HMI_Popup() {
  if (!wait_for_user) {
    if (ClickPopup) ClickPopup();
    return;
  }
  else {
    EncoderState encoder_diffState = get_encoder_state();
    if (encoder_diffState == ENCODER_DIFF_CW || encoder_diffState == ENCODER_DIFF_CCW) {
      const bool change = encoder_diffState != ENCODER_DIFF_CW;
      Draw_Select_Highlight(change, HighlightYPos);
      DWIN_UpdateLCD();
    }
  }
}

#endif // DWIN_LCD_PROUI
