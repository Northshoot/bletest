/*
 * GlucoseService.h
 *
 *  Created on: Sep 15, 2014
 *      Author: lauril
 */

/***
 * https://developer.bluetooth.org/gatt/characteristics/Pages/CharacteristicViewer.aspx?u=org.bluetooth.characteristic.glucose_measurement.xml
 *
 */
#ifndef GLUCOSESERVICE_H_
#define GLUCOSESERVICE_H_
#include "glucose_service.h"

typedef enum {RANDOM, CONSTANT, SMOOTH} SimulationType;

class GlucoseService {
public:
	//Weird but in compilation, class goes not get initialized without constructor argument :S
	GlucoseService(int x);
	virtual ~GlucoseService();
	GlucoseFeature getGlucoseFeature() ;
	void setGlucoseFeature(GlucoseFeature glucoseFeature);
	 GlucoseMeasurementContext getGlucoseMeasurementContext() ;
	void setGlucoseMeasurementContext(
			 GlucoseMeasurementContext glucoseMeasurementContext);
	GlucoseMeasurment getGlucoseMeasurment() ;
	void setGlucoseMeasurment( GlucoseMeasurment glucoseMeasurment);
	 RecordAccessControlPoint getRecordAccessControlPoint() ;
	void setRecordAccessControlPoint(
			 RecordAccessControlPoint recordAccessControlPoint);



private:
	uint16_t mSequence;
	GlucoseMeasurment mGlucoseMeasurment;
	GlucoseMeasurementContext mGlucoseMeasurementContext;
	GlucoseFeature mGlucoseFeature;
	RecordAccessControlPoint mRecordAccessControlPoint;
	float mglucoseConcentration;
	float mglucoseConcentration_MAX;
	float mglucoseConcentration_MIN;
	void initGlucoseFeature(void);
	void initGlucoseMeasurementContext(void);
	void initGlucoseMeasurment(void);
	void initRecordAccessControlPoint(void);
	float glucoseSampleSimulator(SimulationType stp);

};

#endif /* GLUCOSESERVICE_H_ */
