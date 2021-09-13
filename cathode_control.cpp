/**
 * @file cathode_control.cpp
 * @author Takeshi Mori
 * @brief cathode control utility
 * 
 * @copyright Copyright (c) 2021 Takeshi Mori All Rights reserved.
 */
#include "cathode_control.h"
#include "cathode_control_defs.h"

/**
 * @brief initialize
 */
void CathodeControl::init()
{
  // init PORTs
  DDRB = DDRB | NXYI2C_INOUT_PORTB;
  DDRD = DDRD | NXYI2C_INOUT_PORTD;
  PORTB = B00000000; // reset
  PORTD = B00000000; // reset
}

/**
 * @brief turn on or off specified cathod
 * 
 * @param number number
 * @param dot dot
 * @param glow turn on / off
 */
void CathodeControl::glow(signed short number, signed short dot, bool glow)
{
  switch (number)
  {
  case 0:
    glow ? NXYI2C_CATHODE_0_ON : NXYI2C_CATHODE_0_OFF;
    break;
  case 1:
    glow ? NXYI2C_CATHODE_1_ON : NXYI2C_CATHODE_1_OFF;
    break;
  case 2:
    glow ? NXYI2C_CATHODE_2_ON : NXYI2C_CATHODE_2_OFF;
    break;
  case 3:
    glow ? NXYI2C_CATHODE_3_ON : NXYI2C_CATHODE_3_OFF;
    break;
  case 4:
    glow ? NXYI2C_CATHODE_4_ON : NXYI2C_CATHODE_4_OFF;
    break;
  case 5:
    glow ? NXYI2C_CATHODE_5_ON : NXYI2C_CATHODE_5_OFF;
    break;
  case 6:
    glow ? NXYI2C_CATHODE_6_ON : NXYI2C_CATHODE_6_OFF;
    break;
  case 7:
    glow ? NXYI2C_CATHODE_7_ON : NXYI2C_CATHODE_7_OFF;
    break;
  case 8:
    glow ? NXYI2C_CATHODE_8_ON : NXYI2C_CATHODE_8_OFF;
    break;
  case 9:
    glow ? NXYI2C_CATHODE_9_ON : NXYI2C_CATHODE_9_OFF;
    break;
  default:
    break;
  }

  switch (dot)
  {
  case nxyi2c_dots_left: // L Dot
    glow ? NXYI2C_CATHODE_L_ON : NXYI2C_CATHODE_L_OFF;
    break;
  case nxyi2c_dots_right: // R Dot
    glow ? NXYI2C_CATHODE_R_ON : NXYI2C_CATHODE_R_OFF;
    break;
  default:
    break;
  }
}

/**
 * @brief turn on or off all cathods
 * 
 * @param glow turn on / off
 */
void CathodeControl::glowAll(bool glow)
{
  for (unsigned short i = 0; i < 10; i++)
  {
    CathodeControl::glow(i, i % 2, glow);
  }
}
