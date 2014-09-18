/*
 * BleBaseTime.cpp
 *
 *  Created on: Sep 15, 2014
 *      Author: lauril
 */

#include <Arduino.h>
#include "Time/Time.h"
#include "BleBaseTime.h"


BleBaseTime::BleBaseTime(int x) {

	//just optimization during play time
	// in deployment should be made cleaner.
	Serial.print("BleBaseTime up");
	Serial.println(x, HEX);
	currentdatetime.year=2014;
	currentdatetime.month = SEP;
	currentdatetime.day = 16;

}

void
BleBaseTime::printT(){
	Serial.println("Time now");
}

BaseTime
BleBaseTime::getNow(){
	currentdatetime.hours=hour();
	currentdatetime.minutes=minute();
	currentdatetime.seconds=second();
	return currentdatetime;

}


BleBaseTime::~BleBaseTime() {
	// TODO Auto-generated destructor stub

}

