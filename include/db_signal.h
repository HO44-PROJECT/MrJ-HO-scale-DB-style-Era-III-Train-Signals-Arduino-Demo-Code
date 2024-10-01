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
// db_signal.h: header file for DB signals definitions
//
#ifndef __DB_SIGNALS_H__
#define __DB_SIGNALS_H__

#include "pin_state.h"
#include "signal.h"

// This read-only structure describes the electrical states for each visual for each kind of sinals
const int DB_ENTRY_SIGNAL_PIN_COUNT = 3;
const SIGNAL_STATE DB_ENTRY_SIGNAL_PIN_STATES[] = {
    { .id=0, .pin_states = (PIN_STATE[DB_ENTRY_SIGNAL_PIN_COUNT]){ Z, Z, Z }, .description="OFF" },
    { .id=1, .pin_states = (PIN_STATE[DB_ENTRY_SIGNAL_PIN_COUNT]){ H, L, L }, .description="ENTRY_HP1_GREEN" },
    { .id=2, .pin_states = (PIN_STATE[DB_ENTRY_SIGNAL_PIN_COUNT]){ L, H, Z }, .description="ENTRY_HP0_RED" },
    { .id=3, .pin_states = (PIN_STATE[DB_ENTRY_SIGNAL_PIN_COUNT]){ L, L, H }, .description="ENTRY_HP2_YELLOW" },
    {}
};
const SIGNAL_DEFINITION DB_ENTRY_DEFINITION = {
    .pins = DB_ENTRY_SIGNAL_PIN_COUNT, .state_count = 4, .off_state = 0, .states = DB_ENTRY_SIGNAL_PIN_STATES
};

// This read-only structure describes the electrical states for each visual for each kind of sinals
const int DB_BLOC_SIGNAL_PIN_COUNT = 2;
const SIGNAL_STATE DB_BLOC_SIGNAL_PIN_STATES[] = {
    { .id=0, .pin_states = (PIN_STATE[DB_BLOC_SIGNAL_PIN_COUNT]){ Z, Z }, .description="OFF" },
    { .id=1, .pin_states = (PIN_STATE[DB_BLOC_SIGNAL_PIN_COUNT]){ L, H }, .description="BLOC_HP0_RED" },
    { .id=2, .pin_states = (PIN_STATE[DB_BLOC_SIGNAL_PIN_COUNT]){ H, L }, .description="BLOC_HP1_GREEN" },
    {}
};
const SIGNAL_DEFINITION DB_BLOC_DEFINITION = {
    .pins = DB_BLOC_SIGNAL_PIN_COUNT, .state_count = 3, .off_state = 0, .states = DB_BLOC_SIGNAL_PIN_STATES
};

const int DB_EXIT_SIGNAL_PIN_COUNT = 4;
const SIGNAL_STATE DB_EXIT_SIGNAL_PIN_STATES[] = {
    { .id=0, .pin_states = (PIN_STATE[DB_EXIT_SIGNAL_PIN_COUNT]){Z, Z, Z, Z}, .description = "No lamp selected" },
    { .id=1, .pin_states = (PIN_STATE[DB_EXIT_SIGNAL_PIN_COUNT]){H, L, L, H}, .description = "Hp_Rt_L Main signal Red left + Hp_Rt_R Main signal Red right" },
    { .id=2, .pin_states = (PIN_STATE[DB_EXIT_SIGNAL_PIN_COUNT]){L, H, L, L}, .description = "Hp_Gr Main signal Green" },
    { .id=3, .pin_states = (PIN_STATE[DB_EXIT_SIGNAL_PIN_COUNT]){L, H, H, L}, .description = "Hp_Gr Main signal Green + Hp_Ge Main signal Yellow" },
    { .id=4, .pin_states = (PIN_STATE[DB_EXIT_SIGNAL_PIN_COUNT]){H, L, H, H}, .description = "Hp_Rt_L Main signal Red left + Hp_Ws_L Main signal White left + Hp_Ws_R Main signal White right" },
    {} // valid C++ way to zero-out a block-scope array; valid in C since C23 - https://en.cppreference.com/w/c/language/array_initialization
};
const SIGNAL_DEFINITION DB_EXIT_DEFINITION = {
    .pins = DB_EXIT_SIGNAL_PIN_COUNT, .state_count = 5, .off_state = 0, .states = DB_EXIT_SIGNAL_PIN_STATES
};

#endif // __DB_SIGNALS_H__

// EOF
