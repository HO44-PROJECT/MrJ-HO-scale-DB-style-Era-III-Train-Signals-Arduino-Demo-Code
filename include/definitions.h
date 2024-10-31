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
// definitions.h: header file for signal mast wiring
//
#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#define DCC_PIN 2           // DCC wiring, input pin for DCC signal

// #define DEBUG            // Useful for diagnosis

// Signal definitions, MAX_SIGNALS from 0 to n-1
// Undefined signal number x should be set to
// #define Signal_Ax NOTDEFINED
// #define Signal_Tx DB_NO_DEFINITION
// #define Signal_Px NOPIN

#define Signal_A0 10
#define Signal_T0 DB_ENTRY_DEFINITION
#define Signal_P0 3, 4, 5

#define Signal_A1 11
#define Signal_T1 DB_BLOC_DEFINITION
#define Signal_P1 6, 7

#define Signal_A2 12
#define Signal_T2 DB_EXIT_DEFINITION
#define Signal_P2 9, 10, 11, 12

#define Signal_A3 13
#define Signal_T3 DB_BLOC_DEFINITION
#define Signal_P3 A4, A5

#define Signal_A4 NOTDEFINED
#define Signal_T4 DB_NO_DEFINITION
#define Signal_P4 NOPIN

#define Signal_A5 NOTDEFINED
#define Signal_T5 DB_NO_DEFINITION
#define Signal_P5 NOPIN

#define Signal_A6 NOTDEFINED
#define Signal_T6 DB_NO_DEFINITION
#define Signal_P6 NOPIN

#define Signal_A7 NOTDEFINED
#define Signal_T7 DB_NO_DEFINITION
#define Signal_P7 NOPIN

#define Signal_A8 NOTDEFINED
#define Signal_T8 DB_NO_DEFINITION
#define Signal_P8 NOPIN

#define Signal_A9 NOTDEFINED
#define Signal_T9 DB_NO_DEFINITION
#define Signal_P9 NOPIN

#endif // __DEFINITIONS_H__