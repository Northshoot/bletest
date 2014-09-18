/*
 * glucose_service.h
 * The material contained on this page is informative only.
 * Authoritative compliance information is contained in the applicable Bluetooth specification .
 *
 *	Last Modified: 2012-1-17 Approved: Yes
 *	Name: Glucose
 *	Type: org.bluetooth.service.glucoseDownload / View
 *	Assigned Number: 0x1808
 *	https://developer.bluetooth.org/gatt/services/Pages/ServiceViewer.aspx?u=org.bluetooth.service.glucose.xml
 *	Abstract:
 *	This service exposes glucose and other data from a glucose sensor for use in consumer and professional healthcare applications.
 *
 *	Summary:
 *	The Glucose Service exposes glucose and other data related to a glucose sensor for consumer and professional healthcare applications.
 *
 *	Service Dependencies
 *	This service has no dependencies on other GATT-based services.
 *  Created on: Sep 15, 2014
 *      Author: Laurynas Riliskis
 *
 */

#ifndef GLUCOSE_SERVICE_H_
#define GLUCOSE_SERVICE_H_

#include <Arduino.h>
#include "BleBaseTime.h"

typedef enum {RESERVED=0x0, RESERVED1=0x1,
				RESERVED5=0x5, RESERVED6=0x6, RESERVED7=0x7,
				RESERVED10=0xA
			} Reserved;

typedef enum {/*RESERVED=0x0*/	BREAKFAST=0x1, 		LUNCH=0x2,			DINNER=0x3,
				SNACK=0x4, 	DRINK=0x5,		SUPPER=0x6, 		BRUNCH=0x7,
				RESERVED1_CID=0x8
			} CarbohydrateID;

typedef enum {	PREPRANDIAL=0x1,	POSTPRANDIAL=0x2, 	FASTING=0x3,
				CASUAL=0x4,	BEDTIME=0x5
			} Meal;

typedef enum {SELF=0x1,	HEALTHCAREPRO=0x2,	LABTEST=0x3,	NOTAVLB=0x4
			} Tester;

typedef enum { MINOR=0x1,	MAJOR=0x2, MENSES=0x3,
				STRESS=0x4,	NONE=0x5,	NOTAVAILABLE=0x6
			} Health;

typedef enum {RAPID=0x1, 	SHORT=0x2, 	INTERME=0x3, LONG=0x4, 	PREMIXED=0x5
			} MedicationID;

typedef enum {							CAPILLARY_WHOLE=0x1, 	CAPILLARY_PLASMA=0x2,	VENOUS_WHOLE=0x3,
			   VENOUS_PLASMA=0x4, 		ARTERIAL_WHOLE=0x5, 	ARTERIAL_PLASMA=0x6,	UNDETERMINED_WHOLE=0x7,
			   UNDETERMINED_PLASMA=0x8,	IFS=0x9, 				CONTROL=0xA, 			RESERVED11=0xB,
			   RESERVED12=0xC,			RESERVED13=0xD,			RESERVED14=0xE, 		RESERVED15=0xF,
			   RESERVED_S1=0x10,		FINGER=0x11,			AST=0x12,				EARLOBE=0x13,
			   CONROLSOLIUTION=0x14,	NOT_AVAILABLE=0x15
			} GlucoseTypeNSampleLocation;

typedef enum {					REPORT_SR=0x1, 		DELETE_SR=0x2,		ABORT=0x3,
			  NUMBER_SR=0x4, 	RESPONSE=0x5
			} OpCode;
typedef enum {NULL_=0x0,			ALL_RECORDS=0x1, LTEQ=0x2,		GTEQ=0x3,
	  	  	  WITHIN_RANGE=0x4,	FIRST=0x5,			LAST=0x6
			} Operator;

typedef enum {NA=0x0,				FILTER_PARAM1=0x1, 		FILTER_PARAM2=0x2, 	NOT_INCLUDED=0x3,
			  FILTER_PARAM3=0x4,	NUMBER_OF_RECORDS=0x5, 	RQ_OP_CODE
			} Operand;

typedef enum {						SUCCESS=0x1,		 NOT_SPRT_OP_CODE=0x2, INVD=0x3,
			  NOT_SPRT_OPERAND=0x4,	INVALID_OPERAND=0x5, NO_RECORDS=0x6, 		ABORT_UNSUCCESSFUL=0x7,
			  PROCEDURE_NOT_COMPLETED=0x8,  NOT_SUPPORTED_OPERAND_2=0x9
			}ResponseCodeValues;



typedef struct {
	/***
	Bit	Size	Name
	Definition
	Key	Value	Requires
	0	1	Time Offset Present
	0	False
	1	True	C1
	1	1	Glucose Concentration, Type and Sample Location Present
	0	False
	1	True	C2
	2	1	Glucose Concentration Units
	0	kg/L	C3
	1	mol/L	C4
	3	1	Sensor Status Annunciation Present
	0	False
	1	True	C5
	4	1	Context Information Follows
	0	False
	1	True
	5	3	Reserved for future use
	*/
	uint8_t flags;
	uint16_t sequencenumber;
	BaseTime data_time;
	int16_t time_offsett;
	/**
	 *
	 * Glucose Concentration - units of kg/L
	 * Information:
	 * C2: Field exists if the key of bit 1 of the Flags field is set to 1,
	 * C3: Field exists if the key of bit 2 of the Flags field is set to 0
	 */
	float glucose_concentration;
	/**
	 	first Nibble
		0	Reserved for future use
		1	Capillary Whole blood
		2	Capillary Plasma
		3	Venous Whole blood
		4	Venous Plasma
		5	Arterial Whole blood
		6	Arterial Plasma
		7	Undetermined Whole blood
		8	Undetermined Plasma
		9	Interstitial Fluid (ISF)
		10	Control Solution
		11 - 15	Reserved for future use
		Second Nibble
		Key	Value
		0	Reserved for future use
		1	Finger
		2	Alternate Site Test (AST)
		3	Earlobe
		4	Control solution
		15	Sample Location value not available
		5 - 14	Reserved for future use
	 */
	uint8_t GlucoseTypeNSampleLocation;
	uint16_t SensorStatusAnnunciation;
} GlucoseMeasurment;


/**
 * Name: Glucose Measurement Context
Type: org.bluetooth.characteristic.glucose_measurement_contextDownload / View
Assigned Number: 0x2A34
Summary:
The Glucose Measurement Context characteristic is a variable length structure
containing a Flags field, a Sequence Number field and, based upon the contents
of the Flags field, may contain a Carbohydrate ID field, Carbohydrate field,
Meal field, Tester-Health field, Exercise Duration field, Exercise Intensity field,
Medication ID field, Medication field and a HbA1c field.
 */
typedef struct {
	/**
	 Bit Field
		Bit	Size	Name
		Definition
		Key	Value	Requires
		0	1	Carbohydrate ID And Carbohydrate Present
		0	False
		1	True	C2
		1	1	Meal Present
		0	False
		1	True	C3
		2	1	Tester-Health Present
		0	False
		1	True	C4
		3	1	Exercise Duration And Exercise Intensity Present
		0	False
		1	True	C5
		4	1	Medication ID And Medication Present
		0	False
		1	True	C6
		5	1	Medication Value Units
		0	kilograms	C8
		1	liters	C9
		6	1	HbA1c Present
		0	False
		1	True	C7
		7	1	Extended Flags Present
		0	False
		1	True	C1
	 */
	uint8_t flags;
	uint8_t extendedFlags; //Reserved for future use
	/**
		0	Reserved for future use
		1	Breakfast
		2	Lunch
		3	Dinner
		4	Snack
		5	Drink
		6	Supper
		7	Brunch
		8 - 255	Reserved for future use
	 */
	CarbohydrateID carbohydrateID;
	/*
	 Key	Value
	0	Reserved for future use
	1	Preprandial (before meal)
	2	Postprandial (after meal)
	3	Fasting
	4	Casual (snacks, drinks, etc.)
	5	Bedtime
	6 - 255	Reserved for future use
	 */
	float carbohydrateAmount;
	Meal meal;
	/*
	 Key	Value
	0	Reserved for future use
	1	Self
	2	Health Care Professional
	3	Lab test
	15	Tester value not available
	4 - 14	Reserved for future use
	 */
	Tester tester;
	/*
	 Key	Value
	0	Reserved for future use
	1	Minor health issues
	2	Major health issues
	3	During menses
	4	Under stress
	5	No health issues
	15	Health value not available
	6 - 14	Reserved for future use
	 */
	Health health; //65535	Overrun
	uint16_t exerciseDuration; //0 - 65534	Exercise Duration in seconds
	uint8_t exerciseIntensity;
	/*
	 Key	Value
		0	Reserved for future use
		1	Rapid acting insulin
		2	Short acting insulin
		3	Intermediate acting insulin
		4	Long acting insulin
		5	Pre-mixed insulin
		6 - 255	Reserved for future use
	 */
	MedicationID medicationID;
	float medicationAmount; //Medication - units of liters
	float HbA1c;
} GlucoseMeasurementContext;

typedef struct {
	/*
	 Bit Field
		Bit	Size	Name
		Definition
		Key	Value
		0	1	Low Battery Detection During Measurement Supported
		0	False
		1	True
		1	1	Sensor Malfunction Detection Supported
		0	False
		1	True
		2	1	Sensor Sample Size Supported
		0	False
		1	True
		3	1	Sensor Strip Insertion Error Detection Supported
		0	False
		1	True
		4	1	Sensor Strip Type Error Detection Supported
		0	False
		1	True
		5	1	Sensor Result High-Low Detection Supported
		0	False
		1	True
		6	1	Sensor Temperature High-Low Detection Supported
		0	False
		1	True
		7	1	Sensor Read Interrupt Detection Supported
		0	False
		1	True
		8	1	General Device Fault Supported
		0	False
		1	True
		9	1	Time Fault Supported
		0	False
		1	True
		10	1	Multiple Bond Supported
		0	False
		1	True
		11	5	Reserved for future use
	 */
	uint16_t bitfield;
} GlucoseFeature;


typedef struct {
	/*
	 Key	Value
	0	Reserved for future use (Operator:N/A)
	1	Report stored records (Operator: Value from Operator Table)
	2	Delete stored records (Operator: Value from Operator Table)
	3	Abort operation (Operator: Null 'value of 0x00 from Operator Table')
	4	Report number of stored records (Operator: Value from Operator Table)
	5	Number of stored records response (Operator: Null 'value of 0x00 from Operator Table')
	6	Response Code (Operator: Null 'value of 0x00 from Operator Table')
	7 - 255	Reserved for future use
	 */
	OpCode opcode;
	/*
	 *Enumerations
		Key	Value
		0	Null
		1	All records
		2	Less than or equal to
		3	Greater than or equal to
		4	Within range of (inclusive)
		5	First record(i.e. oldest record)
		6	Last record (i.e. most recent record)
		7 - 255	Reserved for future use
	 */
	Operator opertr;
	/*
		Op Code / Operand Value Correspondence
		Key	Value
		0	N/A
		1	Filter parameters (as appropriate to Operator and Service)
		2	Filter parameters (as appropriate to Operator and Service)
		3	Not included
		4	Filter parameters (as appropriate to Operator and Service)k
		5	Number of Records (Field size defined per service)
		6	Request Op Code, Response Code Value
		7 - 255	Reserved for future use

		Response Code Values
		Key	Value	Description
		0	Reserved For Future Use	N/A
		1	Success	Normal response for successful operation
		2	Op Code not supported	Normal response if unsupported Op Code is received
		3	Invalid Operator	Normal response if Operator received does not meet the requirements of the service (e.g. Null was expected)
		4	Operator not supported	Normal response if unsupported Operator is received
		5	Invalid Operand	Normal response if Operand received does not meet the requirements of the service
		6	No records found	Normal response if request to report stored records or request to delete stored records resulted in no records meeting criteria.
		7	Abort unsuccessful	Normal response if request for Abort cannot be completed
		8	Procedure not completed	Normal response if unable to complete a procedure for any reason
		9	Operand not supported	Normal response if unsupported Operand is received
		10 - 255	Reserved for future use
	 */
	Operand operand;
}RecordAccessControlPoint;
#endif /* GLUCOSE_SERVICE_H_ */
