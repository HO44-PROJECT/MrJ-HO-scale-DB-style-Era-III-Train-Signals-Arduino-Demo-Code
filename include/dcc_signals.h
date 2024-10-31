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
// dcc_signals.h: header file for the dcc management for signals
//

#ifndef __DCC_SIGNALS_H__
#define __DCC_SIGNALS_H__

#include <assert.h>
#include <Arduino.h>
#include <stdarg.h>

#include "signal.h"

#include "utils.h"
#include "db_signal.h"
#include <NmraDcc.h> // needed to register the callback
#include "definitions.h" // user masts definitions
#include <boost/preprocessor/repetition/repeat_from_to.hpp> // meta programming to loop over definitions

// Macros used for initialization
#define A(i) Signal_A ## i // Macro for Signal Mast #i Address
#define T(i) Signal_T ## i // Macro for Signal Mast #i Type
#define P(i) Signal_P ## i // Macro for Signal Mast #i Pin Wiring
#define init_signal_wiring(i) _init_signal_wiring ## i  // Local variable name for pin array init. local means duplicate, see init_signal

#define NOTDEFINED 0

// signal init helper.
#define INIT_SIGNAL(i) init_dcc_signal(A(i), &T(i), P(i), NOPIN)

// link between loop item from boost and signal init helper
#define INIT_SIGNAL_LOOP_THIS(z,x,_) INIT_SIGNAL(x);

void setup_dcc_signals();

#endif // __DCC_SIGNALS_H__
