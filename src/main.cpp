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
// main.cpp: source code for the main part of this demo. You can configure your own setup from line 30 to line 37
//
#include "main.h"

NmraDcc Dcc; // DCC management

/// @brief Standard initialization method for Arduino micro-controllers
void setup()
{
  // Only for diagnosis not production
#ifdef DEBUG
  Serial.begin(9600);
#endif

  // Build signal structures from definitions
  setup_dcc_signals();

  // See https://github.com/bxparks/AceRoutine/tree/develop/examples/HelloScheduler
  CoroutineScheduler::setup();

  Dcc.pin(DCC_PIN, 1);  // Enable Pullup
  Dcc.init(MAN_ID_DIY, 3, FLAGS_DCC_ACCESSORY_DECODER, 0); // Version 3, OpsModeAddressBaseCV=0
}

/// @brief Standard run method for Arduino micro-controllers
void loop()
{

  // DCC main loop
  Dcc.process();

  // Thread emulation main loop
  CoroutineScheduler::loop();

  // Signal management main loop
  Signal::loop();

  // Demo mode with random signal changes and a delay applied between changes from 1s to 3.
  // Signal::demo_seq(1000, 3000, 2000);

}

// EOF
