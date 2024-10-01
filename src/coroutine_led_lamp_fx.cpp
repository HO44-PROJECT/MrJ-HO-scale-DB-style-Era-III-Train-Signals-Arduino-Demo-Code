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
// coroutine_led_lamp_fx.cpp: source code for co-working based on AceRoutine (https://github.com/bxparks/AceRoutine)
//
#include "coroutine_led_lamp_fx.h"

/// @brief pin triggering
/// @param on a flag to trigger the pin HIGH or LOW
void Coroutine_Led_Lamp_Fx::_trigger(bool on)
{
    if (on)
        for (int i = 0; i < pin_count; i++)
            digitalWrite(_pins[i], HIGH);
    else
        for (int i = pin_count-1; i >=0; i--)
            digitalWrite(_pins[i], LOW);

}

/// @brief start the lamp effect as specified
/// @param light_up true to light up or false to turn off
void Coroutine_Led_Lamp_Fx::start(bool light_up)
{
    // kind of fading
    _lighting_up = light_up;

    // Flag used by the worker to start its work
    _started = true;
}

/// @brief internal coroutine worker. See https://github.com/bxparks/AceRoutine/blob/develop/examples/HelloManualCoroutine/HelloManualCoroutine.ino
/// @return don't know
int Coroutine_Led_Lamp_Fx::runCoroutine()
{
    COROUTINE_LOOP() {

        // wait for triggering
        COROUTINE_AWAIT(_started);

        // apply delay at startup
        COROUTINE_DELAY(_lighting_up ? light_up_start_delay : turn_off_start_delay);

        // Given the total time to light up and the time for a POV effect, compute the number of iterations needed to complete the job
        _iterations = round(1000UL * (_lighting_up ? light_up_duration : turn_off_duration) / POV_MICROS);

        // Within each iteration, the delay varies by a value in micro-seconds
        _base_delay_micros = round(POV_MICROS / _iterations);

        // Loop over given iterations applying POV effect
        // For this to work in COROUTINE mode, every variable should be static or class properties
        for (_i = 0, _delay = 0; _i < _iterations; _i++, _delay += _base_delay_micros)
        {
            _trigger(!_lighting_up); // from
            COROUTINE_DELAY_MICROS(POV_MICROS - _delay);

            _trigger(_lighting_up); // to
            COROUTINE_DELAY_MICROS(_delay);
        }

        // apply delay at ending
        COROUTINE_DELAY(_lighting_up ? light_up_end_delay : turn_off_end_delay);

        // Job done
        _started = false;
    }

};

/// @brief Constructor
/// @param pins_definition an allocated array of physical pin references. MUST match definition.pins
Coroutine_Led_Lamp_Fx::Coroutine_Led_Lamp_Fx(PIN_ID *pins_definition)
{
    _pins = pins_definition;
    pin_count = 0;
}

// EOF
