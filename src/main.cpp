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
// main.cpp: source code for the main part of this demo. You can configure your own setup from line 30 to line 37
//
#include "main.h"

/// @brief Standard initialization method for Arduino micro-controllers
void setup()
{

  // Signal class are self-registerd into a static for used in main loops
  #pragma GCC diagnostic ignored "-Wunused-variable"

  const PIN_ID my_entry_wiring[DB_ENTRY_DEFINITION.pins] = { 3, 4, 5 };
  new Signal("demo entry signal", &DB_ENTRY_DEFINITION, (PIN_ID *)duplicate(my_entry_wiring, sizeof(my_entry_wiring)));

  const PIN_ID my_bloc_wiring[DB_BLOC_DEFINITION.pins] = { 6, 7 };
  new Signal("demo bloc signal", &DB_BLOC_DEFINITION, (PIN_ID *)duplicate(my_bloc_wiring, sizeof(my_bloc_wiring)));

  const PIN_ID my_exit_wiring[DB_EXIT_DEFINITION.pins] = { 9, 10, 11, 12 };
  new Signal("demo exit signal", &DB_EXIT_DEFINITION, (PIN_ID *)duplicate(my_exit_wiring, sizeof(my_exit_wiring)));

  // See https://github.com/bxparks/AceRoutine/tree/develop/examples/HelloScheduler
  CoroutineScheduler::setup();
}

/// @brief Standard run method for Arduino micro-controllers
void loop()
{

  // Thread emulation main loop
  CoroutineScheduler::loop();

  // Signal management main loop
  Signal::loop();

  // Demo mode with random signal changes and a delay applied between changes from 1s to 3.
  Signal::demo(1000, 3000, 2000);

}

// EOF
