/**
 * @file nxyi2c_numeric_string.h
 * @author Takeshi Mori
 * @brief Display control class to NXYI2C (for master side)
 * @note This class uses the Wire Library. Any method other than the constructor should be used after calling Wire.begin().
 * 
 * @copyright Copyright (c) 2021 Takeshi Mori All Rights reserved.
 * 
 */
#pragma once

#include "from_nxyi2c_default.h"

/**
 * @brief 
 * 
 */
class NXYI2CNumericString
{
public:
    NXYI2CNumericString();
    ~NXYI2CNumericString();

private:
    NXYI2C_CMD _cmd;
    unsigned short *_addresses;
    unsigned short _tubes_count;

public:
    void initializeTubes(const unsigned short *addresses, const unsigned short tubes_count);
    void update(const long value, const bool to_right);
    void updateLD(const float value, const unsigned short right, const bool to_right);
    void updateRD(const float value, const unsigned short right, const bool to_right);

private:
    void updateADigit(const unsigned short target, const char c);
    void updateADigitLD(const unsigned short target, const char c, bool dot);
    void updateADigitRD(const unsigned short target, const char c, bool dot);
    signed short charToNum(const char c);
    void sendCommand(const int dest_addr, const NXYI2C_CMD cmd);
};
