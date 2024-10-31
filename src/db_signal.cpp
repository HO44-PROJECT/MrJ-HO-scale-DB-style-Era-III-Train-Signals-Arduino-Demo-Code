
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
// db_signal.cpp: source file for DB signals definitions
//

#include "db_signal.h"

static const PIN_STATE DB_ENTRY_SIGNAL_PIN_STATES0[] = { Z, Z, Z };
static const PIN_STATE DB_ENTRY_SIGNAL_PIN_STATES1[] = { H, L, L };
static const PIN_STATE DB_ENTRY_SIGNAL_PIN_STATES2[] = { L, H, Z };
static const PIN_STATE DB_ENTRY_SIGNAL_PIN_STATES3[] = { L, L, H };

// This read-only structure describes the electrical states for each visual for each kind of sinals
const int DB_ENTRY_SIGNAL_PIN_COUNT = 3;
const SIGNAL_STATE DB_ENTRY_SIGNAL_PIN_STATES[] = {
    { .id=0, .pin_states = DB_ENTRY_SIGNAL_PIN_STATES0, .description="OFF" },
    { .id=1, .pin_states = DB_ENTRY_SIGNAL_PIN_STATES1, .description="ENTRY_HP1_GREEN" },
    { .id=2, .pin_states = DB_ENTRY_SIGNAL_PIN_STATES2, .description="ENTRY_HP0_RED" },
    { .id=3, .pin_states = DB_ENTRY_SIGNAL_PIN_STATES3, .description="ENTRY_HP2_YELLOW" },
    {}
};
const SIGNAL_DEFINITION DB_ENTRY_DEFINITION = {
    .pins = DB_ENTRY_SIGNAL_PIN_COUNT, .state_count = 4, .off_state = 0, .states = DB_ENTRY_SIGNAL_PIN_STATES
};

static const PIN_STATE DB_BLOC_SIGNAL_PIN_COUNT0[] = { Z, Z };
static const PIN_STATE DB_BLOC_SIGNAL_PIN_COUNT1[] = { L, H };
static const PIN_STATE DB_BLOC_SIGNAL_PIN_COUNT2[] = { H, L };

// This read-only structure describes the electrical states for each visual for each kind of sinals
const int DB_BLOC_SIGNAL_PIN_COUNT = 2;
const SIGNAL_STATE DB_BLOC_SIGNAL_PIN_STATES[] = {
    { .id=0, .pin_states = DB_BLOC_SIGNAL_PIN_COUNT0, .description="OFF" },
    { .id=1, .pin_states = DB_BLOC_SIGNAL_PIN_COUNT1, .description="BLOC_HP0_RED" },
    { .id=2, .pin_states = DB_BLOC_SIGNAL_PIN_COUNT2, .description="BLOC_HP1_GREEN" },
    {}
};
const SIGNAL_DEFINITION DB_BLOC_DEFINITION = {
    .pins = DB_BLOC_SIGNAL_PIN_COUNT, .state_count = 3, .off_state = 0, .states = DB_BLOC_SIGNAL_PIN_STATES
};

static const PIN_STATE DB_EXIT_SIGNAL_PIN_COUNT0[] = {Z, Z, Z, Z};
static const PIN_STATE DB_EXIT_SIGNAL_PIN_COUNT1[] = {H, L, L, H};
static const PIN_STATE DB_EXIT_SIGNAL_PIN_COUNT2[] = {L, H, L, L};
static const PIN_STATE DB_EXIT_SIGNAL_PIN_COUNT3[] = {L, H, H, L};
static const PIN_STATE DB_EXIT_SIGNAL_PIN_COUNT4[] = {H, L, H, H};

const int DB_EXIT_SIGNAL_PIN_COUNT = 4;
const SIGNAL_STATE DB_EXIT_SIGNAL_PIN_STATES[] = {
    { .id=0, .pin_states = DB_EXIT_SIGNAL_PIN_COUNT0, .description = "No lamp selected" },
    { .id=1, .pin_states = DB_EXIT_SIGNAL_PIN_COUNT1, .description = "Hp00 - Hp_Rt_L Main signal Red left + Hp_Rt_R Main signal Red right" },
    { .id=2, .pin_states = DB_EXIT_SIGNAL_PIN_COUNT2, .description = "Hp1 - Hp_Gr Main signal Green" },
    { .id=3, .pin_states = DB_EXIT_SIGNAL_PIN_COUNT3, .description = "Hp2 - Hp_Gr Main signal Green + Hp_Ge Main signal Yellow" },
    { .id=4, .pin_states = DB_EXIT_SIGNAL_PIN_COUNT4, .description = "Hp0/Sh1 - Hp_Rt_L Main signal Red left + Hp_Ws_L Main signal White left + Hp_Ws_R Main signal White right" },
    {} // valid C++ way to zero-out a block-scope a4ray; valid in C since C23 - https://en.cppreference.com/w/c/language/array_initialization
};

const SIGNAL_DEFINITION DB_EXIT_DEFINITION = {
    .pins = DB_EXIT_SIGNAL_PIN_COUNT, .state_count = 5, .off_state = 0, .states = DB_EXIT_SIGNAL_PIN_STATES
};

const SIGNAL_DEFINITION DB_NO_DEFINITION = {
    .pins = 0, .state_count = 5, .off_state = 0, .states = NULL
};
