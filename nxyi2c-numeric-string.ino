/**
 * @file nxyi2c_numeric_string_template.ino
 * @author Takeshi Mori
 * @brief Command transmission utility for hosts that use NXYI2C
 * 
 * @copyright Copyright (c) 2021 Takeshi Mori All Rights reserved.
 * 
 */
#include <Wire.h>
#include "debug_util.h"
#include "nxyi2c_numeric_string.h"

// ====================
// configuration
// ====================
const unsigned short i2c_addresses[5] = {21, 22, 23, 24, 25};
const unsigned short TUBES_COUNT = 5;

static unsigned short g_ptn_index;
static NXYI2CNumericString g_numStr;

const long l_patterns[10] = {
    1,
    12,
    123,
    1234,
    12345,
    123456,
    1234567,
    12345678,
    123456789,
    1234567890};
const unsigned short L_PTN_CNT = 10;

void integerSample(const bool align_right)
{
  g_numStr.update(l_patterns[g_ptn_index], align_right);
  g_ptn_index++;
  if (g_ptn_index >= L_PTN_CNT)
  {
    g_ptn_index = 0;
  }
}

const float f_patterns[13] = {
    0.000123456789,
    0.00123456789,
    0.0123456789,
    0.123456789,
    1.23456789,
    12.3456789,
    123.456789,
    1234.56789,
    12345.6789,
    123456.789,
    1234567.89,
    12345678.9,
    123456789};
const unsigned short F_PTN_CNT = 13;

void leftDotSample(const unsigned short point, const bool align_right)
{
  g_numStr.updateLD(f_patterns[g_ptn_index], point, align_right);
  g_ptn_index++;
  if (g_ptn_index >= F_PTN_CNT)
  {
    g_ptn_index = 0;
  }
}

void rightDotSample(const unsigned short point, const bool align_right)
{
  g_numStr.updateRD(f_patterns[g_ptn_index], point, align_right);
  g_ptn_index++;
  if (g_ptn_index >= F_PTN_CNT)
  {
    g_ptn_index = 0;
  }
}

void setup()
{
  Wire.begin();
#ifdef __DEBUG
  Serial.begin(115200);
#endif
  g_numStr.initializeTubes(i2c_addresses, TUBES_COUNT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  DebugUtil::print("PTN %u : ", g_ptn_index);

  // ==================
  // Integer sample
  // ==================
  // integerSample(false); // 1---- => 12345
  // integerSample(true);  // ----1 => 67890

  // ==================
  // Float sample (Left dot like IN-12)
  // ==================
  // leftDotSample(1, false); // 0.0--- => 12345
  // leftDotSample(1, true);  // ---0.0 => 6790.0
  // leftDotSample(4, false); // 0.0001 => 12345
  // leftDotSample(4, true);  // 0.0001 => 0.0000

  // ==================
  // Float sample (Right dot like IN-8-2)
  // ==================
  // rightDotSample(1, false); // 0.0--- => 12345
  // rightDotSample(1, true);  // ---0.0 => 6790.0
  // rightDotSample(4, false); // 0.0001 => 12345
  // rightDotSample(4, true);  // 0.0001 => 0.0000

  DebugUtil::print("\r\n");
  delay(500);
}
