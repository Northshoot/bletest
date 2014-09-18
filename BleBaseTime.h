/*
 * BaseTime.h
 *
 *  Created on: Sep 15, 2014
 *      Author: lauril
 */

#ifndef BASETIME_H_
#define BASETIME_H_
#include <Arduino.h>

typedef enum {UNKNOWN=0x0,	JAN=0x1,			FEB=0x2,			MAR=0x3,
				APR=0x4,	MAY=0x5,			JUN=0x6,			JUL=0x7,
				AUG=0x8,	SEP=0x9,			OCTB=0xA, 			NOV = 0xB,
				DECEM=0xC
			} Month;

typedef struct {
	/***
	 * Name: Date Time
Type: org.bluetooth.characteristic.date_timeDownload / View
Assigned Number: 0x2A08
Abstract:
The Date Time characteristic is used to represent time.

Summary:
The Date Time characteristic contains fields
or year, month, day, hours, minutes and seconds.
Calendar days in Date Time are represented using Gregorian calendar.
Hours in Date Time are represented in the 24h system.
 */
	uint16_t year; //0	Year is not known
/**	0	Month is not known
	1	January
	2	February
	3	March
	4	April
	5	May
	6	June
	7	July
	8	August
	9	September
	10	October
	11	November
	12	December*/
	Month month;
	uint8_t day; //0	Day is not known
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
} BaseTime;


class BleBaseTime {
	public:
		BleBaseTime(int x);
		BaseTime getNow();
		void printT();
		virtual ~BleBaseTime();
	private:
		BaseTime currentdatetime;
};

#endif /* BASETIME_H_ */
