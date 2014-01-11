#include "RandomCtrlr.h"

#include <random>
#include <chrono>
#include <iostream>

// Singleton =============================================

// Private ctor
RandomCtrlr::RandomCtrlr()
{
	// Setup stuff here

}

// Singleton Instance Getter
RandomCtrlr* RandomCtrlr::GetInstance()
{
	return RandomCtrlr::privGetInstance();
}

// Private Instance Getter
RandomCtrlr* RandomCtrlr::privGetInstance()
{
	static RandomCtrlr instance;
	return &instance;
}

// Game Sturcture =========================================

// Initialize in beginning of program
void RandomCtrlr::InitializeRand()
{
	// Set the time seed
	this->timeSeed = (unsigned long) std::chrono::steady_clock::now().time_since_epoch().count();
}

// During game loop
void RandomCtrlr::LoopRand()
{
	// Set the time seed
	this->timeSeed = (unsigned long) std::chrono::steady_clock::now().time_since_epoch().count();
}

// During release of program
void RandomCtrlr::FinalizeRand()
{
	
}

// Helpers =================================================

// Get a new time-based seed
unsigned long RandomCtrlr::NewSeed()
{
	std::mt19937 seedGen(this->timeSeed++);

	unsigned long newSeed = (unsigned long) seedGen();

	return newSeed;
}

// Routines ================================================

// Get an int between min and max
int RandomCtrlr::Range(int min, int max)
{
	int result;

	// Create random gemerator engine
	std::mt19937 generator(this->NewSeed());

	// Create a uniform distributor between the desired range
	std::uniform_int_distribution<> distributor(min, max);

	// Generate a random number
	result = distributor(generator);

	return result;
}

// Get a float between min and max
float RandomCtrlr::Range(float min, float max)
{
	float result;

	// Create random gemerator engine
	std::mt19937 generator(this->NewSeed());

	// Create a uniform distributor between the desired range
	std::uniform_real_distribution<float> distributor(min, max);

	// Generate a random number
	result = distributor(generator);

	return result;
}