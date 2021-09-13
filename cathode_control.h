/**
 * @file cathode_control.h
 * @author Takeshi Mori
 * @brief cathod control
 * 
 * @copyright Copyright (c) 2021 Takeshi Mori All Rights reserved.
 */
#pragma once

/**
 * @class CathodeControl
 * @brief cathod control class
 */
class CathodeControl {
  public:
    static void init();
    static void glow(signed short number, signed short dot, bool glow);
    static void glowAll(bool glow);
};
