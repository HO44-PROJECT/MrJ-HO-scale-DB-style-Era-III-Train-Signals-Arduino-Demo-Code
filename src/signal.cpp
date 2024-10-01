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
// db_signal.cpp: source code for the general signal class
//
#include "signal.h"

/// @brief Signals main loop. Used to manage all signals from the program main loop
void Signal::loop() {

    // Loop over configured signals and trigger their own loop method.
    for (int s = 0; s < _signal_count; s++) {
        _signals[s]->_loop();
    }
}

/// @brief Signal loop. Used to trigger pins and changes.
void Signal::_loop()
{

    // If a transition is in progress, don't disturb it
    if (changing()) return;

    // If desired state is the actual state, nothing has to be done
    if (_actual_state == _desired_state) return;

    // If the signal is not off, switch it off first
    if (!is_off()) {

        // Once the worker has finished, the signal will be in the desired_state
        _actual_state = _off_state_id;

        // Trigger a transition to the 'off' state
        worker->switch_off();

        return;
    }

    // Once the worker has finished, the signal will be in the desired_state
    _actual_state = _desired_state;

    // The signal is actually off and a new state is required
    SIGNAL_STATE desired_state_definition = _signal_states[_desired_state];

    // Loop over pins. Initialize L or Z states.
    // Record H state. Give the worker the pin list. Initialize them to L (starting state)

    // reset active pins from the worker point of view
    worker->pin_count = 0;

    // loop over wired pins
    for (int pin_no = 0; pin_no < _wired_pins_count; pin_no++) {
        if (desired_state_definition.pin_states[pin_no] == H) {
            _pin_it(_wired_pins[pin_no], L); // init to LOW
            _active_worker_pins[worker->pin_count++] = _wired_pins[pin_no]; // record
        } else {
            _pin_it(_wired_pins[pin_no], desired_state_definition.pin_states[pin_no]);
        }
    }

    // start the transition
    worker->switch_on();

}

/// @brief User has asked for a change
/// @param new_state
void Signal::change(int new_state) {
    _desired_state = new_state;
}

/// @brief Send hardware signals to the pin
/// @param pin pin number on the Arduino
/// @param state state definition
void Signal::_pin_it(int pin, PIN_STATE state) {
    if (pin == NOPIN) return;

    pinMode(pin, state.mode);
    digitalWrite(pin, state.value);
}

/// @brief Signal constructor
/// @param description user name for this signal
/// @param definition signal definition
/// @param wiring physical pins list
Signal::Signal(String description, const SIGNAL_DEFINITION *definition, PIN_ID *wiring) {

    // User label for this signal
    _description = description;

    // Number of wired pins
    _wired_pins_count = definition->pins;

    // Physical wiring (ie list of pin ids on the Arduino)
    _wired_pins = wiring;

    // All possible signal states
    _signal_states = definition->states;
    // Number of available states
    _signal_states_count = definition->state_count;

    // internal variables, working state, desired state, id of the off state
    _actual_state = _desired_state = _off_state_id = definition->off_state;

    // Allocate space to communicate with the worker to tell it which pins are used for transition
    _active_worker_pins = (PIN_ID*)malloc(_wired_pins_count*sizeof(PIN_ID));

    // Allocate a new worker
    worker = new Coroutine_Led_Lamp_Fx(_active_worker_pins);

    // A new signal to manage
    Signal::_signals[Signal::_signal_count] = this;
    Signal::_signal_count++;

}

/// @brief Trigger the demo mode
void Signal::demo(long min_delay, long max_delay, long off_delay) {

    // Loop over known signals
    for (int s = 0; s < _signal_count; s++) {

        // change in progress?
        if (_signals[s]->changing()) continue;

        // New state choosen randomly
        int r = random(0, _signals[s]->_signal_states_count);

        // Delay after each change
        _signals[s]->worker->turn_off_end_delay = r == _signals[s]->_off_state_id ? off_delay : 0;
        _signals[s]->worker->light_up_end_delay = r == _signals[s]->_off_state_id ? 0 : random(min_delay, max_delay);

        _signals[s]->change(r);

    }
}

// Initialization of static data
int Signal::_signal_count = 0;
Signal **Signal::_signals = (Signal **)malloc(sizeof(Signal *)*MAX_SIGNALS);

// EOF
