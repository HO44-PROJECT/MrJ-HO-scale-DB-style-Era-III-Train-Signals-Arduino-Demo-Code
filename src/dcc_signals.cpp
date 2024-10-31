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
// dcc_signals.cpp: source code for the dcc management for signals
//

#include "dcc_signals.h"

/// @brief NmraDcc callback for signals
/// @param Addr Signal Masts DCC Accesory Address as Offset Address
/// @param State Aspect ID
void notifyDccSigOutputState (uint16_t Addr, uint8_t State) {

#ifdef DEBUG
  Serial.print("* [notifyDccSigOutputState] new accessory decoder packet received (BoardAddr=");
  Serial.print(Addr, DEC);
  Serial.print(", state=");
  Serial.println(State, DEC);
#endif

  Signal::change(Addr, State);
}

/// @brief dcc mast configuration from definitions.h
/// @param address
/// @param definition
/// @param wiring, NOPIN terminated
void init_dcc_signal(uint16_t address, const SIGNAL_DEFINITION *definition, ...) {

  if (address == NOTDEFINED) return;

  va_list pin_list;
  va_start(pin_list, definition);

#ifdef DEBUG
  Serial.print("Defining mast at address "); Serial.println(address, DEC);
  Serial.print("allocating "); Serial.print(definition->pins); Serial.println(" pins.");
#endif

  PIN_ID *pins = (PIN_ID *)malloc(sizeof(PIN_ID)*definition->pins);

  int p;
  for (p = 0; p < definition->pins; p++) {
    int pin = va_arg(pin_list, int);
    if (pin == NOPIN) {
      Serial.print("Signal definition error. Signal at address ");
      Serial.print(address, DEC);
      Serial.print(" has only "); Serial.print(p); Serial.print(" pins instead of "); Serial.println(definition->pins);
      return;
    }
    Serial.print("adding pin "); Serial.print(pin); Serial.print(" at position "); Serial.println(p);
    pins[p] = (PIN_ID)pin;
  }

  int last_pin = va_arg(pin_list, int);

  if (last_pin != NOPIN) {
    Serial.print("Signal definition error. Signal at address ");
    Serial.print(address, DEC);
    Serial.print(" has too many pins defined, should be "); Serial.println(definition->pins);
    return;
  }

  va_end(pin_list);

  // No description provided
  new Signal(address, "", definition, pins);
}

/// @brief based on definitions, used to setup all signal masts
void setup_dcc_signals() {

  // Initialize signal masts from definitions
  BOOST_PP_REPEAT_FROM_TO(0, MAX_SIGNALS, INIT_SIGNAL_LOOP_THIS, 0);
}
