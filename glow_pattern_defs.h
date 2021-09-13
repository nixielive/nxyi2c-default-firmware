/**
 * @file glow_pattern_defs.h
 * @author Takeshi Mori
 * @brief types and statics
 * 
 * @copyright Copyright (c) 2021 Takeshi Mori All Rights reserved.
 */
#pragma once

/**
 * @enum nxyi2c_patterns
 * @brief Lighting pattern of Nixie tube
 */
enum nxyi2c_patterns {
    nxyi2c_pattern_off = 0,
    nxyi2c_pattern_show = 1,
    nxyi2c_pattern_fade_in = 2,
    nxyi2c_pattern_fade_out = 3,
    nxyi2c_pattern_fade_change = 4,
    nxyi2c_pattern_patapata = 5,
    nxyi2c_pattern_from_cloud = 6,
    nxyi2c_pattern_into_cloud = 7,
};

/**
 * @enum nxyi2c_statuses
 * @brief status of display transision
 */
enum nxyi2c_statuses {
    nxyi2c_status_none = 0,
    nxyi2c_status_starting = 1,
    nxyi2c_status_running = 2,
};

#define NXYI2C_PTN_FADE_STEPS (50)
#define NXYI2C_PTN_PATAPATA_INTERVAL_MS (100)

