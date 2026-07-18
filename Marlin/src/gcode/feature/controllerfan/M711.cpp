/**
 * Fan Kickstart settings
 * Author: wlkmanist
 * Date: 2024/04/04
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

#if ENABLED(FAN_KICKSTART_EDITABLE)

#include "../../gcode.h"
#include "../../../feature/controllerfan.h"

/**
 * M711: Set Fan Kickstart settings
 *
 *  R         : Reset to defaults
 *  S[0-255]  : Fan speed when fans first start
 *  D         : Set Kickstart duration (ms)
 *  E[0|1]    : Turn Kickstart feature on or off
 *
 * Examples:
 *   M711               : Report current Settings
 *   M711 R             : Reset SDE to defaults
 *   M711 S255          : Set Kickstart fan speed to 100%
 *   M711 E1 S180 D100  : Set Kickstart to ON, Kickstart fan speed 70%, duration to 100 milliseconds
 *   M711 E0            : Set Kickstart to OFF
 */
void GcodeSuite::M711() {
  if (!parser.seen("DERS")) return M711_report();

  const bool seenR = parser.seen('R');
  const bool seenS = parser.seenval('S');
  const bool seenD = parser.seenval('D');
  const bool seenE = parser.seenval('E');

  if (seenR) kickstart.reset();
  if (seenS) kickstart.settings.speed = parser.value_byte();
  if (seenD) kickstart.settings.duration = parser.value_ushort();
  if (seenE) kickstart.settings.enabled = parser.value_bool();
}

void GcodeSuite::M711_report(const bool forReplay/*=true*/) {
  TERN_(MARLIN_SMALL_BUILD, return);

  report_heading_etc(forReplay, F(STR_FAN_KICKSTART));
  SERIAL_ECHOLNPGM("  M711"
    " S", int(kickstart.settings.speed),
    " D", int(kickstart.settings.duration),
    " E", int(kickstart.settings.enabled),
    " ; (", (int(kickstart.settings.speed) * 100) / 255, "%)"
  );
}

#endif // FAN_KICKSTART_EDITABLE
