/**
 * @file glow_patterns.cpp
 * @author Takeshi Mori
 * @brief Nixie tube lighting control
 * 
 * @copyright Copyright (c) 2021 Takeshi Mori All Rights reserved.
 */
#include "glow_pattern_defs.h"
#include "cathode_control.h"
#include "cathode_control_defs.h"
#include "glow_patterns.h"

/**
 * @brief Construct a new Glow Patterns:: Glow Patterns object
 */
GlowPatterns::GlowPatterns()
{
  this->m_pattern = nxyi2c_pattern_show;
  this->m_number = 0;
  this->m_dot = nxyi2c_dots_none;
  this->m_durationMs = 500;
  this->m_status = nxyi2c_status_none;
  this->_currentUs = 0;
  this->_currentSteps = 0;
  this->_pattern = nxyi2c_pattern_show;
  this->_currentNumber = nxyi2c_nums_none;
  this->_nextNumber = nxyi2c_nums_none;
  this->_currentDot = nxyi2c_dots_none;
  this->_nextDot = nxyi2c_dots_none;
}

/**
 * @brief Destroy the Glow Patterns:: Glow Patterns object
 */
GlowPatterns::~GlowPatterns()
{
}

/**
 * @brief instance initialize
 */
void GlowPatterns::init()
{
  CathodeControl::init();
}

/**
 * @brief start pattern
 */
void GlowPatterns::start()
{
  // Shared variables to local variables
  this->_pattern = this->m_pattern;                              // 1. pattern
  this->_nextNumber = this->m_number;                            // 2. Number
  this->_nextDot = this->m_dot;                                  // 3. Dot
  this->_durationUs = ((signed long)this->m_durationMs) * 1000L; // 4. duration - milli sec to micro sec
  this->_stepUs = this->_durationUs / NXYI2C_PTN_FADE_STEPS;
  this->_currentSteps = 0;

  switch (_pattern)
  {
  case nxyi2c_pattern_off:
    this->startOff();
    break;
  case nxyi2c_pattern_show:
    this->startShow();
    break;
  case nxyi2c_pattern_fade_in:
    this->startFadeIn();
    break;
  case nxyi2c_pattern_fade_out:
    this->startFadeOut();
    break;
  case nxyi2c_pattern_fade_change:
    this->startFadeChange();
    break;
  case nxyi2c_pattern_patapata:
    this->startPataPata();
    break;
  case nxyi2c_pattern_from_cloud:
    this->startFromCloud();
    break;
  case nxyi2c_pattern_into_cloud:
    this->startIntoCloud();
    break;
  default:
    break;
  }
  this->m_status = nxyi2c_status_running;
}

/**
 * @brief method for loop event of arduino main loop
 */
void GlowPatterns::loop()
{
  if (this->m_status == nxyi2c_status_starting)
  {
    this->start();
    return;
  }
  else if (this->m_status == nxyi2c_status_running)
  {
    switch (this->_pattern)
    {
    case nxyi2c_pattern_off:
      this->loopOff();
      break;
    case nxyi2c_pattern_show:
      this->loopShow();
      break;
    case nxyi2c_pattern_fade_in:
      this->loopFadeIn();
      break;
    case nxyi2c_pattern_fade_out:
      this->loopFadeOut();
      break;
    case nxyi2c_pattern_fade_change:
      this->loopFadeChange();
      break;
    case nxyi2c_pattern_patapata:
      this->loopPataPata();
      break;
    case nxyi2c_pattern_from_cloud:
      this->loopFromCloud();
      break;
    case nxyi2c_pattern_into_cloud:
      this->loopIntoCloud();
      break;
    default:
      break;
    }
  }
}

/**
 * @brief next lighting pattern
 */
void GlowPatterns::next()
{
  this->_currentNumber = this->_nextNumber;
  this->_currentDot = this->_nextDot;
}

// ==========
// pattern - off
// ==========
/**
 * @brief Start transision control of the tube (Turn off)
 */
void GlowPatterns::startOff()
{
  CathodeControl::glowAll(false);
  this->next();
}

/**
 * @brief Transision control of the tube for loop event (Turn off)
 */
void GlowPatterns::loopOff()
{
}

// ==========
// pattern - show
// ==========
/**
 * @brief Start transision control of the tube (show number-immediately)
 */
void GlowPatterns::startShow()
{
  CathodeControl::glowAll(false);
  this->next();
}

/**
 * @brief Transision control of the tube for loop event (show number-immediately)
 */
void GlowPatterns::loopShow()
{
  CathodeControl::glow(this->_currentNumber, this->_currentDot, true);
  this->m_status == nxyi2c_status_none;
}

// ==========
// pattern - fade in
// ==========
/**
 * @brief Start transision control of the tube (fade in)
 */
void GlowPatterns::startFadeIn()
{
  CathodeControl::glowAll(false);
  this->next();
}

/**
 * @brief Transision control of the tube for loop event (fade in)
 */
void GlowPatterns::loopFadeIn()
{
  if (this->_currentSteps < NXYI2C_PTN_FADE_STEPS)
  {
    this->updateGlowRatios();
    CathodeControl::glow(this->_currentNumber, this->_currentDot, false);
    delayMicroseconds(this->_currentUs);
    CathodeControl::glow(this->_currentNumber, this->_currentDot, true);
    delayMicroseconds(this->_nextUs);
    this->_currentSteps++;
  }
  else
  {
    this->m_status == nxyi2c_status_none;
  }
}

// ==========
// pattern - fade out
// ==========
/**
 * @brief Start transision control of the tube (fade out)
 */
void GlowPatterns::startFadeOut()
{
  CathodeControl::glowAll(false);
  this->next();
}

/**
 * @brief Transision control of the tube for loop event (fade out)
 */
void GlowPatterns::loopFadeOut()
{
  if (this->_currentSteps < NXYI2C_PTN_FADE_STEPS)
  {
    this->updateGlowRatios();
    CathodeControl::glow(this->_currentNumber, this->_currentDot, true);
    delayMicroseconds(this->_currentUs);
    CathodeControl::glow(this->_currentNumber, this->_currentDot, false);
    delayMicroseconds(this->_nextUs);
    this->_currentSteps++;
  }
  else
  {
    this->m_status == nxyi2c_status_none;
  }
}

// ==========
// pattern - fade change
// ==========
/**
 * @brief Start transision control of the tube (fade change)
 */
void GlowPatterns::startFadeChange()
{
  if (this->_currentNumber != this->_nextNumber) {
    CathodeControl::glow(this->_currentNumber, nxyi2c_dots_none, false);
  }
  if (this->_currentDot != this->_nextDot) {
    CathodeControl::glow(nxyi2c_nums_none, this->_currentDot, false);
  }
}

/**
 * @brief Transision control of the tube for loop event (fade change)
 */
void GlowPatterns::loopFadeChange()
{
  if (this->_currentSteps < NXYI2C_PTN_FADE_STEPS)
  {
    signed short currentNumber = this->_currentNumber;
    signed short nextNumber = this->_nextNumber;
    signed short currentDot = this->_currentDot;
    signed short nextDot = this->_nextDot;

    this->updateGlowRatios();
    if (this->_currentNumber == this->_nextNumber) {
      // Don't operate number
      currentNumber = nxyi2c_nums_none;
      nextNumber = nxyi2c_nums_none;
    }
    if (this->_currentDot == this->_nextDot) {
      // Don't operate dots
      currentDot = nxyi2c_dots_none;
      nextDot = nxyi2c_dots_none;
    }
    CathodeControl::glow(currentNumber, currentDot, true);
    CathodeControl::glow(nextNumber, nextDot, false);
    delayMicroseconds(this->_currentUs);
    CathodeControl::glow(currentNumber, currentDot, false);
    CathodeControl::glow(nextNumber, nextDot, true);
    delayMicroseconds(this->_nextUs);
    this->_currentSteps++;
  }
  else
  {
    this->m_status == nxyi2c_status_none;
    this->next();
  }
}

// ==========
// pattern - patapata
// ==========
/**
 * @brief Start transision control of the tube (patapata)
 * 
 */
void GlowPatterns::startPataPata()
{
  CathodeControl::glowAll(false);
  if (this->_currentNumber != this->_nextNumber)
  {
    this->_patapataStep = 1;  // NOTE : increment rotate
    
    # if 0
    // NOTE : nearest
    if (this->_currentNumber > this->_nextNumber)
    {
      if (this->_nextNumber + 10 - this->_currentNumber < this->_currentNumber - this->_nextNumber)
      {
        // e.g. 8 => 2
        this->_patapataStep = 1;
      }
      else
      {
        // e.g. 6 => 4
        this->_patapataStep = -1;
      }
    }
    else
    {
      if (this->_currentNumber + 10 - this->_nextNumber < this->_nextNumber - this->_currentNumber)
      {
        // e.g. 2 => 8
        this->_patapataStep = -1;
      }
      else
      {
        // e.g. 4 => 6
        this->_patapataStep = 1;
      }
    }
    #endif
  }
  else
  {
    CathodeControl::glow(this->_currentNumber, this->_currentDot, true);
    this->m_status == nxyi2c_status_none;
  }
}

/**
 * @brief Transision control of the tube for loop event (patapata)
 */
void GlowPatterns::loopPataPata()
{
  if (this->_currentNumber != this->_nextNumber)
  {
    CathodeControl::glow(this->_currentNumber, this->_currentDot, false);
    this->_currentNumber += this->_patapataStep;
    this->_currentDot += this->_patapataStep;
    if (this->_currentNumber > 9)
    {
      this->_currentNumber = nxyi2c_nums_none;
    }
    else if (this->_currentNumber < nxyi2c_nums_none)
    {
      this->_currentNumber = 9;
    }
    if (this->_currentDot > 1)
    {
      this->_currentDot = nxyi2c_dots_none;
    }
    else if (this->_currentDot < nxyi2c_dots_none)
    {
      this->_currentDot = 1;
    }
    CathodeControl::glow(this->_currentNumber, this->_currentDot, true);
    delay(NXYI2C_PTN_PATAPATA_INTERVAL_MS);
  }
  else
  {
    CathodeControl::glow(this->_currentNumber, this->_currentDot, false);
    CathodeControl::glow(this->_nextNumber, this->_nextDot, true);
    this->next();
    this->m_status == nxyi2c_status_none;
  }
}

// ==========
// pattern - from cloud
// ==========
/**
 * @brief Start transision control of the tube (from cloud)
 */
void GlowPatterns::startFromCloud()
{
  CathodeControl::glowAll(false);
  this->next();
}

/**
 * @brief Transision control of the tube for loop event (from cloud)
 */
void GlowPatterns::loopFromCloud()
{
  if (this->_currentSteps < NXYI2C_PTN_FADE_STEPS)
  {
    this->updateGlowRatios();
    CathodeControl::glowAll(true);
    delayMicroseconds(this->_currentUs);
    CathodeControl::glowAll(false);
    CathodeControl::glow(this->_currentNumber, this->_currentDot, true);
    delayMicroseconds(this->_nextUs);
    this->_currentSteps++;
  }
  else
  {
    this->m_status == nxyi2c_status_none;
  }
}

// ==========
// pattern - into cloud
// ==========

/**
 * @brief Start transision control of the tube (into cloud)
 */
void GlowPatterns::startIntoCloud()
{
  CathodeControl::glowAll(false);
  this->next();
}

/**
 * @brief Transision control of the tube for loop event (into cloud)
 */
void GlowPatterns::loopIntoCloud()
{
  if (this->_currentSteps < NXYI2C_PTN_FADE_STEPS)
  {
    this->updateGlowRatios();
    CathodeControl::glowAll(false);
    CathodeControl::glow(this->_currentNumber, this->_currentDot, true);
    delayMicroseconds(this->_currentUs);
    CathodeControl::glowAll(true);
    delayMicroseconds(this->_nextUs);
    this->_currentSteps++;
  }
  else
  {
    this->m_status == nxyi2c_status_none;
  }
}

/**
 * @brief Brightness calculation
 */
void GlowPatterns::updateGlowRatios()
{
  this->_currentUs = (this->_stepUs * (NXYI2C_PTN_FADE_STEPS - (unsigned long)this->_currentSteps)) / NXYI2C_PTN_FADE_STEPS;
  this->_nextUs = (this->_stepUs * (unsigned long)this->_currentSteps) / NXYI2C_PTN_FADE_STEPS;
}
