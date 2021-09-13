/**
 * @file cathode_control_defs.h
 * @author Takeshi Mori
 * @brief types and statics
 * 
 * @copyright Copyright (c) 2021 Takeshi Mori All Rights reserved.
 */
#pragma once

#include "Arduino.h"

// number and dots
enum nxyi2c_nums {
    nxyi2c_nums_none = -1
};

enum nxyi2c_dots {
    nxyi2c_dots_none = -1,
    nxyi2c_dots_left = 0,
    nxyi2c_dots_right = 1
};

// port output pins
#define NXYI2C_INOUT_PORTB (B11111111)
#define NXYI2C_INOUT_PORTD (B00001111)

// cathode control macros
#define NXYI2C_CATHODE_0_ON (PORTD |= _BV(1))
#define NXYI2C_CATHODE_0_OFF (PORTD &= ~_BV(1))
#define NXYI2C_CATHODE_1_ON (PORTB |= _BV(0))
#define NXYI2C_CATHODE_1_OFF (PORTB &= ~_BV(0))
#define NXYI2C_CATHODE_2_ON (PORTB |= _BV(1))
#define NXYI2C_CATHODE_2_OFF (PORTB &= ~_BV(1))
#define NXYI2C_CATHODE_3_ON (PORTB |= _BV(2))
#define NXYI2C_CATHODE_3_OFF (PORTB &= ~_BV(2))
#define NXYI2C_CATHODE_4_ON (PORTB |= _BV(3))
#define NXYI2C_CATHODE_4_OFF (PORTB &= ~_BV(3))
#define NXYI2C_CATHODE_5_ON (PORTB |= _BV(4))
#define NXYI2C_CATHODE_5_OFF (PORTB &= ~_BV(4))
#define NXYI2C_CATHODE_6_ON (PORTB |= _BV(5))
#define NXYI2C_CATHODE_6_OFF (PORTB &= ~_BV(5))
#define NXYI2C_CATHODE_7_ON (PORTB |= _BV(6))
#define NXYI2C_CATHODE_7_OFF (PORTB &= ~_BV(6))
#define NXYI2C_CATHODE_8_ON (PORTB |= _BV(7))
#define NXYI2C_CATHODE_8_OFF (PORTB &= ~_BV(7))
#define NXYI2C_CATHODE_9_ON (PORTD |= _BV(0))
#define NXYI2C_CATHODE_9_OFF (PORTD &= ~_BV(0))
#define NXYI2C_CATHODE_L_ON (PORTD |= _BV(2))
#define NXYI2C_CATHODE_L_OFF (PORTD &= ~_BV(2))
#define NXYI2C_CATHODE_R_ON (PORTD |= _BV(3))
#define NXYI2C_CATHODE_R_OFF (PORTD &= ~_BV(3))
