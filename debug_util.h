/**
 * @file debug_util.h
 * @author Takeshi Mori
 * @brief Utility for debugging output on a serial monitor
 * 
 * @copyright Copyright (c) 2021 Takeshi Mori All Rights reserved.
 */
#pragma once

// Please comment out the following line, if you don't like to output debug messages
#define __DEBUG

/**
 * @class DebugUtil
 * @brief Utility for debug output on the serial monitor
 * 
 */
class DebugUtil
{
public:
  DebugUtil();
  ~DebugUtil();
  static void print(const char *format, ...);
  static char *d2f(const float value, unsigned char p);
};
