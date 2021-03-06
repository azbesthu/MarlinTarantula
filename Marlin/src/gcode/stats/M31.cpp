/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "../gcode.h"
#include "../../core/serial.h"
#include "../../module/printcounter.h"
#include "../../libs/duration_t.h"
#include "../../lcd/ultralcd.h"

#if NUM_SERIAL > 1
  #include "../../gcode/queue.h"
#endif

/**
 * M31: Get the time since the start of SD Print (or last M109)
 */
void GcodeSuite::M31() {
  #if NUM_SERIAL > 1
    const int16_t port = command_queue_port[cmd_queue_index_r];
  #endif
  char buffer[21];
  duration_t elapsed = print_job_timer.duration();
  elapsed.toString(buffer);
  ui.setstatus(buffer);

  SERIAL_ECHO_START_P(port);
  SERIAL_ECHOLNPAIR_P(port, "Print time: ", buffer);
}
