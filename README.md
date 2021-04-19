# Daylight Simulator

RGB led strip controller library for the Arduino. 

## Configurations
### Time

You can set time length in `color.cpp`

	const int sunriseBegin = 2520; // 07:00
	const int dawnBegin    = 2880; // 08:00
	const int dayBegin     = 3240; // 09:00
	const int sunsetBegin  = 6840; // 19:00
	const int duskBegin    = 7200; // 20:00
	const int nightBegin   = 7920; // 22:00
	
### Colors
You can set RGB colors  in `color.cpp`

	const byte nightLED[] = {0, 0, 0};
	const byte sunLED[]   = {255, 157, 64};
	const byte dayLED[]   = {255, 255, 164};

## Requirements

* [Arduino IDE Version 1.8.13 or later](http://www.arduino.cc/en/Main/Software)* 
* Ardunio board
* 5V RGB LED Strip
* Real-Time Clock Module (DS3231)
* NPN Transistor (2N2222)

\* Earlier versions of the Arduino IDE may work but have not been tested.

## Wiring Diagram

![](https://raw.githubusercontent.com/kozmixb/daylight_simulator/master/wiring.png)