#include "TimeCtrlr.h"

#include <iostream>

// Singleton =============================================

// Private ctor
TimeCtrlr::TimeCtrlr()
{
	// Setup stuff here
}

// Singleton Instance Getter
TimeCtrlr* TimeCtrlr::GetInstance()
{
	return TimeCtrlr::privGetInstance();
}

// Private Instance Getter
TimeCtrlr* TimeCtrlr::privGetInstance()
{
	static TimeCtrlr instance;
	return &instance;
}

// Game Sturcture =========================================

// Initialize in beginning of program
void TimeCtrlr::InitializeTime()
{
	this->updateStartTime = StandardClock::now();
	this->gameStartTime = StandardClock::now();
}

// During game loop
void TimeCtrlr::LoopTime()
{
	// Get the current time
	PointInTime currentTime = StandardClock::now();

	// Calculate the loop's time duration
	this->loopDuration = currentTime - this->updateStartTime;

	// Set new update start time
	this->updateStartTime = currentTime;
}

// During release of program
void TimeCtrlr::FinalizeTime()
{
	this->updateStartTime = StandardClock::now();
	this->gameStartTime = StandardClock::now();
}

// Routines ================================================

// Get time last loop completed	(in seconds)
float TimeCtrlr::GetDeltaTime()
{
	return this->loopDuration.count();
}

//Get time since launched game (in seconds)
float TimeCtrlr::GetRunTime()
{
	PointInTime currentTime = StandardClock::now();
	TimeDuration gameRunTime = currentTime - this->gameStartTime;

	return gameRunTime.count();
}