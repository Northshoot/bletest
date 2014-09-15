/*
 * InsulinePump.h
 *
 *  Created on: Sep 10, 2014
 *      Author: lauril
 */

#ifndef INSULINEPUMP_H_
#define INSULINEPUMP_H_
#include <Arduino.h>

class InsulinePump {
public:
	InsulinePump();
	virtual ~InsulinePump();

	uint16_t getActivityLevel() const;
	void setActivityLevel(uint16_t activityLevel);
	uint16_t getAge() const;
	void setAge(uint16_t age);
	uint16_t getDraving() const;
	void setDraving(uint16_t draving);
	uint16_t getFast() const;
	void setFast(uint16_t fast);
	uint16_t getGender() const;
	void setGender(uint16_t gender);
	uint16_t getGlucoseCurrent() const;
	void setGlucoseCurrent(uint16_t glucoseCurrent);
	uint16_t getInsulineBasalInterval() const;

	uint16_t getInsulineBasalVal() const;
	void setInsulineBasalVal(uint16_t insulineBasalVal);
	uint16_t getInsulineTemporalInterval() const;

	uint16_t getInsulineTemporalVal() const;
	void setInsulineTemporalVal(uint16_t insulineTemporalVal);
	uint16_t getKetons() const;
	void setKetons(uint16_t ketons);
	uint16_t getTravel() const;
	void setTravel(uint16_t travel);
	uint16_t getWeight() const;
	void setWeight(uint16_t weight);
	uint16_t getSleep() const;
	void setSleep(uint16_t weight);

private:
	uint16_t mGlucoseCurrent;
	uint16_t mInsulineBasalVal;
	uint16_t mInsulineBasalInterval;
	uint16_t mInsulineTemporalVal;
	uint16_t mInsulineTemporalInterval;
	uint16_t mActivityLevel;
	uint16_t mWeight;
	uint16_t mAge;
	uint16_t mGender;
	uint16_t mKetons;
	uint16_t mFast;
	uint16_t mTravel;
	uint16_t mDraving;
	uint16_t mSleep;

	uint16_t administrate();
	uint16_t updateInsuline();
	void setInsulineBasalInterval(uint16_t insulineBasalInterval);
	void setInsulineTemporalInterval(uint16_t insulineTemporalInterval);
};

#endif /* INSULINEPUMP_H_ */
