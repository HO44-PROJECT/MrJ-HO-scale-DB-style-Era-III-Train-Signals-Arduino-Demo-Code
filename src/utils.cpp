//
// Railway HO project: DB_Signals: MrJ's Deutsche Bahn (DB) Era III Style Train Signals with POV Lamp Effect Prototype Using Arduino in Co-Working Mode (i.e., thread emulation)
// https://github.com/HO44-PROJECT/db_signals_demo
//
// This code is provided under the GNU GENERAL PUBLIC LICENSE courtesy of MrJ (ho44project@gmail.com) - 2024-10-01
//
// This code applies to the Arduino Nano platform.
//
// This code demonstrates how to drive HO-scale train signals. LEDs are wired to the Arduino with a resistor.
// The program applies a "lamp" effect on any LED using digital output in co-working mode.
// Based on POV, it gives the human eye the impression of a fading effect.
// This effect is applied in cooperative mode, which means fast-switching to emulate threads using the excellent AceRoutine library.
//
// This code drives 3 DB Signals in demo mode, cycling through available states on and off with fading effects.
//
// See README.md for hardware, configuration, references, and explanations.
//
// db_signal.cpp: source code for the utilities
//
#include "utils.h"

/// @brief Duplicate memory zone
/// @param in
/// @param size
/// @return
void *duplicate(const void *in, const size_t size) {

  void *out = malloc(size);
  memcpy(out, in, size);
  return out;
}

// EOF