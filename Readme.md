# **NXYI2C Numeric string sample sketch for Arduino**

This sketch displays numeric string on 5 NXYI2C and tubes.

For more information about NXYI2C, please visit [here](https://www.nixielive.com).

This sketch requires 5 NXYI2Cs with I2C addresses 21 to 25 written on it.
See the following for how to write NXYI2C and I2C addresses.

* [I2C nixietube control module (NXYI2C)](https://www.nixielive.com/docs/nxyi2c_module)
* [How to upload your sketch to NXYI2C](https://www.nixielive.com/docs/nxyi2c_upload)
* [Default firmware sketch of NXYI2C](https://github.com/nixielive/nxyi2c-default-firmware)

# **Sketch Description**
This sketch is an example of how to display a numeric string such as "123" or "0.12" on a Nixie tube. 
From the commented out lines below, select the pattern you want to display and uncomment it.

```
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
```

You can see the results below.
* [integerSample(false)](https://youtu.be/dh0cqmpei_Q)
* [integerSample(true)](https://youtu.be/QwO9uGRaaz4)
* [leftDotSample(1, false)](https://youtu.be/hHLyr7JiZ3c)
* [leftDotSample(1, true)](https://youtu.be/g-puIw9k3wQ)
* [leftDotSample(4, false)](https://youtu.be/Qs5MtxfdvYE)
* [leftDotSample(4, true)](https://youtu.be/Ngh3ocMUyi4)
* [rightDotSample(1, false)](https://youtu.be/YusI9QI6lWM)
* [rightDotSample(1, true)](https://youtu.be/yJxbi7RmPMw)
* [rightDotSample(4, false)](https://youtu.be/SgW78QPVQUw)
* [rightDotSample(4, true)](https://youtu.be/Is0l27c05hY)

|Function|description|
|:---|:---|
|integerSample|1st arg : right justified(true)/left justified(false)|
|leftDotSample|1st arg : Number of digits to be displayed after the decimal point<br/>2nd arg : right justified(true)/left justified(false)|
|rightDotSample|1st arg : Number of digits to be displayed after the decimal point<br/>2nd arg : right justified(true)/left justified(false)|

# **About serial debug**
If you want to check what number is currently being displayed, you can output the current number to serial monitor. If you want to stop this output, comment out the following line in `debug_util.h`.

```
#define __DEBUG
```