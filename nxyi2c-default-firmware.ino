/**
 * @file nxyi2c_default.ino
 * @author Takeshi Mori
 * @brief 
 * 
 * @copyright Copyright (c) 2021 Takeshi Mori All Rights reserved.
 * 
 */
#include <Wire.h>

#include "nxyi2c_defs.h"
#include "cathode_control_defs.h"
#include "cathode_control.h"
#include "glow_pattern_defs.h"
#include "glow_patterns.h"

#define I2C_ADDRESS (20U) // NOTE : smbus 0x03(003) - 0x77(119)

static GlowPatterns g_pattern;
static NXYI2C_CMD g_cmdBuf;

/**
 * @brief For testing to display the specified value.
 * 
 * @param number number
 * @param dot dot
 * @param duration duration
 */
void glowTest(signed short number, signed short dot, unsigned long duration)
{
  CathodeControl::glowAll(false);
  CathodeControl::glow(number, dot, true);
  delay(duration);
  CathodeControl::glow(number, dot, false);
}

/**
 * @brief Sequential display of all numbers
 */
void showSelfCheck()
{
  glowTest(0, nxyi2c_dots_none, 500);
  glowTest(1, nxyi2c_dots_left, 500);
  glowTest(2, nxyi2c_dots_right, 500);
  glowTest(3, nxyi2c_dots_none, 500);
  glowTest(4, nxyi2c_dots_left, 500);
  glowTest(5, nxyi2c_dots_right, 500);
  glowTest(6, nxyi2c_dots_none, 500);
  glowTest(7, nxyi2c_dots_left, 500);
  glowTest(8, nxyi2c_dots_right, 500);
  glowTest(9, nxyi2c_dots_none, 500);
  glowTest(nxyi2c_nums_none, nxyi2c_dots_none, 500); // OFF
}

/**
 * @brief Display the I2C address of NXYI2C
 * 
 */
void showAddress()
{
  glowTest(I2C_ADDRESS / 100 % 10, nxyi2c_dots_none, 500);
  glowTest(I2C_ADDRESS / 10 % 10, nxyi2c_dots_none, 500);
  glowTest(I2C_ADDRESS % 10, nxyi2c_dots_none, 500);
  glowTest(nxyi2c_nums_none, nxyi2c_dots_none, 500); //OFF
}

/**
 * @brief I2C Receive Event Callback
 * @param len received data size
 */
void onReceive(int len)
{
  if (len == sizeof(NXYI2C_CMD))
  {
    unsigned char *pCmd = (unsigned char *)&g_cmdBuf;
    for (int idx = 0; idx < len; idx++)
    {
      *(pCmd + idx) = Wire.read();
    }
    switch (g_cmdBuf.command)
    {
    case nxyi2c_set_pattern:
      g_pattern.m_pattern = g_cmdBuf.value;
      break;
    case nxyi2c_set_duration:
      g_pattern.m_durationMs = g_cmdBuf.value;
      break;
    case nxyi2c_set_number:
      g_pattern.m_number = g_cmdBuf.value;
      break;
    case nxyi2c_set_dot:
      g_pattern.m_dot = g_cmdBuf.value;
      break;
    case nxyi2c_start:
      g_pattern.m_status = nxyi2c_status_starting;
      break;
    default:
      break;
    }
  }
}

/**
 * @brief setup
 */
void setup()
{
  // put your setup code here, to run once:
  g_pattern.init();
  g_pattern.m_pattern = nxyi2c_pattern_show;
  g_pattern.m_durationMs = 500;

  // Show numbers
  showSelfCheck();
  delay(1000);

  // Show I2C address
  showAddress();
  delay(1000);

  // Start I2C data receive procedure
  Wire.begin((int)I2C_ADDRESS);
  Wire.onReceive(onReceive);
}

/**
 * @brief loop
 */
void loop()
{
  g_pattern.loop();
}
