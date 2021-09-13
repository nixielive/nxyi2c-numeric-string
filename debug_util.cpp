/**
 * @file debug_util.cpp
 * @author Takeshi Mori
 * @brief Utility for debugging output on a serial monitor
 * @note If you like to output debug string to serial monitor, enable "#include __DEBUG" line in debug_util.h. 
 * 
 * @copyright Copyright (c) 2021 Takeshi Mori All Rights reserved.
 */
#include <stdio.h>
#include <stdarg.h>
#include "Arduino.h"

#include "debug_util.h"

static char _debug_util_buf_l[256];
static char _debug_util_buf_s[32];

/**
 * @brief Output of formatted string to serial monitor
 * 
 * @param format format
 * @param ... arguments
 * @note Floating point formatting is not available. Use "%s" and d2f of this class to make it a string.
 */
void DebugUtil::print(const char *format, ...) {
#ifdef __DEBUG
  va_list args;
  va_start(args, format);
  vsprintf(_debug_util_buf_l, format, args);
  Serial.print(_debug_util_buf_l);
  va_end(args);
#endif
}

/**
 * @brief Instead of dtostrf
 * 
 * @param value 
 * @param d 
 * @return char* A string of floating number
 */
char* DebugUtil::d2f(const float value, unsigned char d) {
#ifdef __DEBUG
  dtostrf(value, -1, d, _debug_util_buf_s);
  return _debug_util_buf_s;
#endif
}
