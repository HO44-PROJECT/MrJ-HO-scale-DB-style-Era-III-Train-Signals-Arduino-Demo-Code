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
// signal.h: header file for the general signal class
//
#ifndef __SIGNALS_H__
#define __SIGNALS_H__

#include "pin_state.h"
#include "coroutine_led_lamp_fx.h"

#define MAX_SIGNALS 10

typedef struct
{
    int id; // id for this state
    const PIN_STATE *pin_states; // states for each pin must match wired_pins
    const char *description;     // description for this state
} SIGNAL_STATE;

typedef struct
{
    const int pins;
    const int state_count;
    const int off_state;
    const SIGNAL_STATE *states;
} SIGNAL_DEFINITION;

/// @brief This class describes a physical signal
class Signal
{

private:

    const char * _description;
    uint16_t _address;

    int _desired_state; // The state the user is asking for
    int _actual_state; // The state the worker is working on (asked or off if change from another on state)

    // states definition
    int _signal_states_count; // number of states available
    const SIGNAL_STATE *_signal_states; // states definitions
    int _off_state_id; // id of the 'off' state

    int _wired_pins_count; // number of wired pins
    const PIN_ID *_wired_pins; // Ardino pin numbers

    PIN_ID *_active_worker_pins; // allocated by the constructor

    // transition instance
    Coroutine_Led_Lamp_Fx *worker;

    // drive the hardware
    void _pin_it(int pin, PIN_STATE state);
    void _switch(int state);
    void _loop();

public:
    Signal(uint16_t _address, const char *description, const SIGNAL_DEFINITION *definition, const PIN_ID *wiring);

    static void loop();
    static void demo_random(long min_delay, long max_delay, long off_delay);
    static void demo_random() { demo_random(0, 0, 0); };
    static void demo_seq(long min_delay, long max_delay, long off_delay);
    static void demo_seq() { demo_seq(0, 0, 0); };
    void change(int new_state);
    static void change(uint16_t address, int new_state);
    bool changing() { return worker->running(); };
    bool is_off() { return _actual_state == _off_state_id; };
    void switch_off() { _desired_state = _off_state_id; };
    int wired_pins() { return _wired_pins_count; };
    int desired_state() { return _desired_state; };
    const char *description() { return _description; };
    uint16_t address() { return _address; };

    static Signal **_signals; // pointer to all signals created
    static int _signal_count; // grand total of signal instances created
};

#endif // __SIGNALS_H__
