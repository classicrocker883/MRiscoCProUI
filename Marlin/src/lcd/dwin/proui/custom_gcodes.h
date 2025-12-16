/**
 * Custom G-code implementation for PRO UI
 * Author: Miguel A. Risco-Castillo (MRISCOC)
 * Version: 1.4.0
 * Date: 2023/05/03
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

#pragma once

void custom_gcode(const int16_t codenum);
#if PROUI_EX
  void custom_gcode_report(const bool forReplay=true);
#endif
void CError();
#if HAS_CUSTOM_COLORS
  void C11();
#endif
#if ENABLED(PROUI_ITEM_TRAM)
  void C35();
#endif
void C108();
#if HAS_GCODE_PREVIEW
  void C250();
#endif
#if HAS_LOCKSCREEN
  void C510();
#endif
#if DEBUG_DWIN
  void C997();
#endif
