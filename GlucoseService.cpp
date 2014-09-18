/*
 * GlucoseService.cpp
 *
 *  Created on: Sep 15, 2014
 *      Author: lauril
 */

#include <Arduino.h>
#include <SPI.h>
#include <stdlib.h>
#include "GlucoseService.h"


GlucoseService::GlucoseService(int x) {
	// TODO Auto-generated constructor stub
	Serial.println("GlucoseService::GlucoseService inited");
	this->mSequence = 0;
	this->mglucoseConcentration=81.2;
	mglucoseConcentration_MAX=75.0;
	mglucoseConcentration_MIN=85.0;
	this->initGlucoseFeature();
	this->initGlucoseMeasurementContext();
	this->initGlucoseMeasurment();
	this->initRecordAccessControlPoint();
}
void
GlucoseService::initGlucoseFeature(void) {
	mGlucoseFeature.bitfield = 0x0;
}

void GlucoseService::initGlucoseMeasurementContext(void) {
	mGlucoseMeasurementContext.flags=0xF7;
	mGlucoseMeasurementContext.extendedFlags=0xff; //Reserved for future use
	mGlucoseMeasurementContext.carbohydrateID=SNACK;
	mGlucoseMeasurementContext.carbohydrateAmount=111;
	mGlucoseMeasurementContext.meal=PREPRANDIAL;
	mGlucoseMeasurementContext.tester=HEALTHCAREPRO;
	mGlucoseMeasurementContext.health=STRESS; //65535	Overrun
	mGlucoseMeasurementContext.exerciseDuration=55555; //0 - 65534	Exercise Duration in seconds
	mGlucoseMeasurementContext.exerciseIntensity=8;
	mGlucoseMeasurementContext.medicationID=PREMIXED;
	mGlucoseMeasurementContext.medicationAmount=2; //Medication - units of liters
	mGlucoseMeasurementContext.HbA1c=12.4;
}

void GlucoseService::initGlucoseMeasurment(void) {
	BleBaseTime bt(0);
	mGlucoseMeasurment.flags = 0x1B;//0x7;
	mGlucoseMeasurment.sequencenumber = this->mSequence;
	mGlucoseMeasurment.data_time = bt.getNow();
	mGlucoseMeasurment.time_offsett=-1;
	mGlucoseMeasurment.glucose_concentration=this->glucoseSampleSimulator(RANDOM);

	mGlucoseMeasurment.GlucoseTypeNSampleLocation = FINGER;
	mGlucoseMeasurment.SensorStatusAnnunciation = 1;

}

void GlucoseService::initRecordAccessControlPoint(void) {
	mRecordAccessControlPoint.opcode = (OpCode)RESERVED;
	mRecordAccessControlPoint.operand =NA;
	mRecordAccessControlPoint.opertr = NULL_;
}

GlucoseService::~GlucoseService() {
	// TODO Auto-generated destructor stub
}

GlucoseFeature
GlucoseService::getGlucoseFeature()  {
	return mGlucoseFeature;
}

void
GlucoseService::setGlucoseFeature(GlucoseFeature glucoseFeature) {
	mGlucoseFeature = glucoseFeature;
}

 GlucoseMeasurementContext
 GlucoseService::getGlucoseMeasurementContext()  {
	return mGlucoseMeasurementContext;
}

void GlucoseService::setGlucoseMeasurementContext(
		 GlucoseMeasurementContext glucoseMeasurementContext) {
	mGlucoseMeasurementContext = glucoseMeasurementContext;
}

GlucoseMeasurment
GlucoseService::getGlucoseMeasurment()  {
	BleBaseTime bt(0);
	mSequence++;
	mGlucoseMeasurment.sequencenumber = this->mSequence;
	mGlucoseMeasurment.data_time = bt.getNow();
	mGlucoseMeasurment.glucose_concentration=this->glucoseSampleSimulator(RANDOM);
	return mGlucoseMeasurment;
}

void GlucoseService::setGlucoseMeasurment(
		 GlucoseMeasurment glucoseMeasurment) {
	mGlucoseMeasurment = glucoseMeasurment;
}

RecordAccessControlPoint
GlucoseService::getRecordAccessControlPoint()  {
	return mRecordAccessControlPoint;
}

void GlucoseService::setRecordAccessControlPoint(
		 RecordAccessControlPoint recordAccessControlPoint) {
	mRecordAccessControlPoint = recordAccessControlPoint;
}

float
GlucoseService::glucoseSampleSimulator(SimulationType stp){
	float mTmp=this->mglucoseConcentration;
	switch (stp) {
		case RANDOM:
			mTmp = random(60, 160) +0.2;
			break;
		case CONSTANT:
			break;
		case SMOOTH:
			if (mTmp == mglucoseConcentration_MAX)
				mTmp=mglucoseConcentration_MIN;
			else
				mTmp+=3;
			break;
		default:
			break;
	}
	this->mglucoseConcentration=mTmp;
	return mglucoseConcentration;
}
