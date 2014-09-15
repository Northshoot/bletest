/*
 * InsulinePump.cpp
 *
 *  Created on: Sep 10, 2014
 *      Author: lauril
 */

#include "InsulinePump.h"

InsulinePump::InsulinePump() {
	 this->mGlucoseCurrent=0;
	 this->mInsulineBasalVal=0;
	 this->mInsulineBasalInterval=0;
	 this->mInsulineTemporalVal=0;
	 this->mInsulineTemporalInterval=0;
	 this->mActivityLevel=0;
	 this->mWeight=0;
	 this->mAge=0;
	 this->mGender=0;
	 this->mKetons=0;
	 this-> mFast=0;
	 this->mTravel=0;
	 this->mDraving=0;
	 this->mSleep=0;

}

InsulinePump::~InsulinePump() {
	// TODO Auto-generated destructor stub
}

uint16_t InsulinePump::getActivityLevel() const {
	return mActivityLevel;
}

void InsulinePump::setActivityLevel(uint16_t activityLevel) {
	mActivityLevel = activityLevel;
}

uint16_t InsulinePump::getAge() const {
	return mAge;
}

void InsulinePump::setAge(uint16_t age) {
	mAge = age;
}

uint16_t InsulinePump::getDraving() const {
	return mDraving;
}

void InsulinePump::setDraving(uint16_t draving) {
	mDraving = draving;
}

uint16_t InsulinePump::getFast() const {
	return mFast;
}

void InsulinePump::setFast(uint16_t fast) {
	mFast = fast;
}

uint16_t InsulinePump::getGender() const {
	return mGender;
}

void InsulinePump::setGender(uint16_t gender) {
	mGender = gender;
}

uint16_t InsulinePump::getGlucoseCurrent() const {
	return mGlucoseCurrent;
}

void InsulinePump::setGlucoseCurrent(uint16_t glucoseCurrent) {
	mGlucoseCurrent = glucoseCurrent;
}

uint16_t InsulinePump::getInsulineBasalInterval() const {
	return mInsulineBasalInterval;
}

void InsulinePump::setInsulineBasalInterval(uint16_t insulineBasalInterval) {
	mInsulineBasalInterval = insulineBasalInterval;
}

uint16_t InsulinePump::getInsulineBasalVal() const {
	return mInsulineBasalVal;
}

void InsulinePump::setInsulineBasalVal(uint16_t insulineBasalVal) {
	mInsulineBasalVal = insulineBasalVal;
}

uint16_t InsulinePump::getInsulineTemporalInterval() const {
	return mInsulineTemporalInterval;
}

void InsulinePump::setInsulineTemporalInterval(
		uint16_t insulineTemporalInterval) {
	mInsulineTemporalInterval = insulineTemporalInterval;
}

uint16_t InsulinePump::getInsulineTemporalVal() const {
	return mInsulineTemporalVal;
}

void InsulinePump::setInsulineTemporalVal(uint16_t insulineTemporalVal) {
	mInsulineTemporalVal = insulineTemporalVal;
}

uint16_t InsulinePump::getKetons() const {
	return mKetons;
}

void InsulinePump::setKetons(uint16_t ketons) {
	mKetons = ketons;
}

uint16_t InsulinePump::getTravel() const {
	return mTravel;
}

void InsulinePump::setTravel(uint16_t travel) {
	mTravel = travel;
}

uint16_t InsulinePump::getWeight() const {
	return mWeight;
}

void InsulinePump::setWeight(uint16_t weight) {
	mWeight = weight;
}

uint16_t InsulinePump::getSleep() const {
	return mSleep;
}

void InsulinePump::setSleep(uint16_t sleep) {
	mSleep = sleep;
}
