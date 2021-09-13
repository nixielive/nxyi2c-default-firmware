/**
 * @file nxyi2c_defs.h
 * @author Takeshi Mori
 * @brief types and statics
 * 
 * @copyright Copyright (c) 2021 Takeshi Mori All Rights reserved.
 * 
 */
#pragma once

/**
 * @struct NXYI2C_CMD
 * @brief I2C command data
 * 
 */
typedef struct _nxyi2c_cmd
{
  unsigned char command;
  signed short value;
} NXYI2C_CMD;

/**
 * @enum nxyi2c_commands
 * @brief Type of commands
 * 
 */
enum nxyi2c_commands {
    nxyi2c_start = 0,
    nxyi2c_set_pattern = 1,
    nxyi2c_set_duration = 2,
    nxyi2c_set_number = 3,
    nxyi2c_set_dot = 4,
};
