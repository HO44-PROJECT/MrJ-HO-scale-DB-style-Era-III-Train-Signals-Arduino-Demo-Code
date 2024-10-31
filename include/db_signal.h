//
// Railway HO project: DB_Signals: MrJ's Bundesbahn Bahn (DB) Era III Style Train Signals with POV Lamp Effect Prototype Using Arduino in Co-Working Mode (i.e., thread emulation)
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
// db_signal.h: header file for DB signals definitions
//
#ifndef __DB_SIGNALS_H__
#define __DB_SIGNALS_H__

#include "pin_state.h"
#include "signal.h"

// This read-only structure describes the electrical states for each visual for each kind of sinals
extern const int DB_ENTRY_SIGNAL_PIN_COUNT;
extern const SIGNAL_STATE DB_ENTRY_SIGNAL_PIN_STATES[];
extern const SIGNAL_DEFINITION DB_ENTRY_DEFINITION;

// This read-only structure describes the electrical states for each visual for each kind of sinals
extern const int DB_BLOC_SIGNAL_PIN_COUNT;
extern const SIGNAL_STATE DB_BLOC_SIGNAL_PIN_STATES[];
extern const SIGNAL_DEFINITION DB_BLOC_DEFINITION;

extern const int DB_EXIT_SIGNAL_PIN_COUNT;
extern const SIGNAL_STATE DB_EXIT_SIGNAL_PIN_STATES[];
extern const SIGNAL_DEFINITION DB_EXIT_DEFINITION;

extern const SIGNAL_DEFINITION DB_NO_DEFINITION;

#endif // __DB_SIGNALS_H__

// EOF
