/**
 * @file nxyi2c_numeric_string.cpp
 * @author Takeshi Mori
 * @brief Display control class to NXYI2C (for master side)
 * 
 * @copyright Copyright (c) 2021 Takeshi Mori All Rights reserved.
 * 
 */
#include <Wire.h>
#include "debug_util.h"
#include "nxyi2c_numeric_string.h"
#include "from_nxyi2c_default.h"

/**
 * @brief Construct a new NXYI2CNumericString::NXYI2CNumericString object
 * 
 */
NXYI2CNumericString::NXYI2CNumericString()
{
  this->_addresses = NULL;
  this->_tubes_count = 0;
}

/**
 * @brief Destroy the NXYI2CNumericString::NXYI2CNumericString object
 * 
 */
NXYI2CNumericString::~NXYI2CNumericString()
{
  if (this->_addresses != NULL)
  {
    ::free(this->_addresses);
    this->_addresses = NULL;
    this->_tubes_count = 0;
  }
}

/**
 * @brief Set up and initialize the Nixie tubes to be controlled.
 * 
 * @param addresses I2C addresses of NXYI2C
 * @param tubes_count number of tubes
 * @note Calling this method will turn off the display of the Nixie tubes
 */
void NXYI2CNumericString::initializeTubes(const unsigned short *addresses, const unsigned short tubes_count)
{
  if (this->_addresses != NULL)
  {
    ::free(this->_addresses);
    this->_addresses = NULL;
    this->_tubes_count = 0;
  }
  this->_addresses = (unsigned short *)::calloc(sizeof(unsigned short *), tubes_count);
  this->_tubes_count = tubes_count;
  ::memcpy(this->_addresses, addresses, sizeof(unsigned short) * tubes_count);

  unsigned short target;
  for (unsigned short index = 0; index < this->_tubes_count; index++)
  {

    target = this->_addresses[index];

    // Set pattern
    this->_cmd.command = nxyi2c_set_pattern;
    this->_cmd.value = nxyi2c_pattern_show;
    sendCommand(target, this->_cmd);

    // Set duration
    this->_cmd.command = nxyi2c_set_duration;
    this->_cmd.value = 0; // 'show' doesn't use duration param
    sendCommand(target, this->_cmd);

    // Set number
    this->_cmd.command = nxyi2c_set_number;
    this->_cmd.value = nxyi2c_nums_none;
    sendCommand(target, this->_cmd);

    // Set dot
    this->_cmd.command = nxyi2c_set_dot;
    this->_cmd.value = nxyi2c_dots_none;
    sendCommand(target, this->_cmd);

    // Start
    this->_cmd.command = nxyi2c_start;
    sendCommand(target, this->_cmd);
  }
}

/**
 * @brief Display a number (integer)
 * 
 * @param value Number to be displayed
 */
void NXYI2CNumericString::update(const long value, const bool to_right)
{
  char disp[64] = {0};
  short cIndex;
  short tIndex;
  sprintf(disp, "%ld", value);
  DebugUtil::print("%s", disp);

  if (!to_right)
  {
    // align left
    tIndex = 0;
    cIndex = 0;
    while (tIndex < this->_tubes_count)
    {
      this->updateADigit(this->_addresses[tIndex], disp[cIndex]);
      tIndex++;
      cIndex++;
    }
  }
  else
  {
    // align right
    tIndex = this->_tubes_count - 1;
    cIndex = strlen(disp) - 1;
    while (tIndex >= 0)
    {
      if (cIndex >= 0) {
        this->updateADigit(this->_addresses[tIndex], disp[cIndex]);      
      }
      else {
        this->updateADigit(this->_addresses[tIndex], NULL);  
      }
      tIndex--;
      cIndex--;
    }
  }
}

/**
 * @brief Display a number (float)
 * 
 * @param value Number to be displayed
 * @note For tubes with a dot to the left of the number. (Like IN-12)
 */
void NXYI2CNumericString::updateLD(const float value, const unsigned short point, const bool to_right)
{
  char disp[64] = {0};
  short cIndex;
  short tIndex;
  dtostrf(value, -1, point, disp);
  DebugUtil::print("%s", disp);

  if (to_right == false)
  {
    // align left
    tIndex = 0;
    cIndex = 0;
    while (tIndex < this->_tubes_count)
    {
      if (disp[cIndex] == '-')
      {
        cIndex++;
        continue;
      }
      
      if (disp[cIndex] == '.')
      {
        cIndex++;
        this->updateADigitLD(this->_addresses[tIndex], disp[cIndex], true);
      }
      else
      {
        this->updateADigitLD(this->_addresses[tIndex], disp[cIndex], false);
      }
      cIndex++;
      tIndex++;
    }
  }
  else
  {
    // align right
    tIndex = this->_tubes_count - 1;
    cIndex = strlen(disp) - 1;
    while (tIndex >= 0)
    {
      if (disp[cIndex-1] == '.')
      {
        this->updateADigitLD(this->_addresses[tIndex], cIndex >= 0 ? disp[cIndex] : ' ', true);
        cIndex--;
      }
      else
      {
        this->updateADigitLD(this->_addresses[tIndex], cIndex >= 0 ? disp[cIndex] : ' ', false);
      }
      cIndex--;
      tIndex--;
    }
  }
}

/**
 * @brief Display a number (float)
 * 
 * @param value Number to be displayed
 * @note For tubes with a dot to the left of the number. (Like IN-8)
 */
void NXYI2CNumericString::updateRD(const float value, const unsigned short right, const bool to_right)
{
  char disp[64] = {0};
  short cIndex;
  short tIndex;
  dtostrf(value, -1, right, disp);
  DebugUtil::print("%s", disp);

  if (to_right == false)
  {
    // align left
    tIndex = 0;
    cIndex = 0;
    while (tIndex < this->_tubes_count)
    {
      if (disp[cIndex] == '-')
      {
        cIndex++;
        continue;
      }
      
      if (disp[cIndex+1] == '.')
      {
        this->updateADigitRD(this->_addresses[tIndex], disp[cIndex], true);
        cIndex++;
      }
      else
      {
        this->updateADigitRD(this->_addresses[tIndex], disp[cIndex], false);
      }
      cIndex++;
      tIndex++;
    }
  }
  else
  {
    // align right
    tIndex = this->_tubes_count - 1;
    cIndex = strlen(disp) - 1;
    while (tIndex >= 0)
    { 
      if (disp[cIndex] == '.')
      {
        this->updateADigitRD(this->_addresses[tIndex], cIndex >= 0 ? disp[cIndex-1] : ' ', true);
        cIndex--;
      }
      else
      {
        this->updateADigitRD(this->_addresses[tIndex], cIndex >= 0 ? disp[cIndex] : ' ', false);
      }
      cIndex--;
      tIndex--;
    }
  }
}

void NXYI2CNumericString::updateADigit(const unsigned short target, const char c)
{
  // Set number
  this->_cmd.command = nxyi2c_set_number;
  this->_cmd.value = this->charToNum(c);
  sendCommand(target, this->_cmd);

  // Start
  this->_cmd.command = nxyi2c_start;
  sendCommand(target, this->_cmd);
}

void NXYI2CNumericString::updateADigitLD(const unsigned short target, const char c, bool dot)
{
  // Set number
  this->_cmd.command = nxyi2c_set_number;
  this->_cmd.value = this->charToNum(c);
  sendCommand(target, this->_cmd);

  // Set dot
  this->_cmd.command = nxyi2c_set_dot;
  this->_cmd.value = dot ? nxyi2c_dots_left : nxyi2c_dots_none;
  sendCommand(target, this->_cmd);

  // Start
  this->_cmd.command = nxyi2c_start;
  sendCommand(target, this->_cmd);
}

void NXYI2CNumericString::updateADigitRD(const unsigned short target, const char c, bool dot)
{
  // Set number
  this->_cmd.command = nxyi2c_set_number;
  this->_cmd.value = this->charToNum(c);
  sendCommand(target, this->_cmd);

  // Set dot
  this->_cmd.command = nxyi2c_set_dot;
  this->_cmd.value = dot ? nxyi2c_dots_right : nxyi2c_dots_none;
  sendCommand(target, this->_cmd);

  // Start
  this->_cmd.command = nxyi2c_start;
  sendCommand(target, this->_cmd);
}

signed short NXYI2CNumericString::charToNum(const char c)
{
  switch (c)
  {
  case '0':
    return 0;
  case '1':
    return 1;
  case '2':
    return 2;
  case '3':
    return 3;
  case '4':
    return 4;
  case '5':
    return 5;
  case '6':
    return 6;
  case '7':
    return 7;
  case '8':
    return 8;
  case '9':
    return 9;
  default:
    break;
  }
  return nxyi2c_nums_none;
}

/**
 * @brief Send command to NXYI2C
 * 
 * @param dest_addr I2C address of the destination NXYI2C
 * @param cmd command data
 */
void NXYI2CNumericString::sendCommand(const int dest_addr, const NXYI2C_CMD cmd)
{
  Wire.beginTransmission(dest_addr);
  Wire.write((unsigned char *)(&this->_cmd), sizeof(this->_cmd));
  Wire.endTransmission();
}
