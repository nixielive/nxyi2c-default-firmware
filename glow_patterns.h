/**
 * @file glow_patterns.h
 * @author Takeshi Mori
 * @brief Nixie tube lighting control
 * 
 * @copyright Copyright (c) 2021 Takeshi Mori All Rights reserved.
 */
#pragma once

/**
 * @class GlowPatterns
 * @brief Nixie tube lighting control class
 */
class GlowPatterns {

  public:
    unsigned short m_status;
    signed short m_pattern;
    signed short m_durationMs;
    signed short m_number;
    signed short m_dot;

  protected:
    signed long _durationUs;
    signed long _stepUs;
    signed long _currentUs;
    signed long _nextUs;
    signed short _currentSteps;
    signed short _pattern;
    signed short _currentNumber;
    signed short _nextNumber;
    signed short _currentDot;
    signed short _nextDot;
    signed short _patapataStep;

  public:
    GlowPatterns();
    ~GlowPatterns();

    void init();
    void start();
    void loop();
    void next();

  protected:
    // start
    void startOff();
    void startShow();
    void startFadeIn();
    void startFadeOut();
    void startFadeChange();
    void startPataPata();
    void startFromCloud();
    void startIntoCloud();

    // loop
    void loopOff();
    void loopShow();
    void loopFadeIn();
    void loopFadeOut();
    void loopFadeChange();
    void loopPataPata();
    void loopFromCloud();
    void loopIntoCloud();

    void updateGlowRatios();
};
