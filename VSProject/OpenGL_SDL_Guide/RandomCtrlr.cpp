#include "RandomCtrlr.h"

#include <random>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <chrono>

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
	/*
	std::cout << "Init Rand" << std::endl;
	std::default_random_engine randEng;
	std::cout << "Min: " << randEng.min() << std::endl;
	std::cout << "Max: " << randEng.max() << std::endl;

	std::cout << "A rand: " << randEng() << std::endl;
	std::cout << "A rand: " << randEng() << std::endl;

	std::stringstream state;
	state << randEng;		// Save current state

	std::cout << "A rand: " << randEng() << std::endl;
	std::cout << "A rand: " << randEng() << std::endl;

	state >> randEng;		// Restore current state

	std::cout << "A rand: " << randEng() << std::endl;
	std::cout << "A rand: " << randEng() << std::endl;

	std::default_random_engine ee;
	std::default_random_engine ee2;

	for(int i=0; i<10; i++)
	{
		std::cout << ee() << std::endl;
	}
	std::cout << std::endl;

	for(int i=0; i<10; i++)
	{
		std::cout << ee2() << std::endl;
	}
	std::cout << std::endl;

	// Define a seed for the randomizers to use
	

	std::default_random_engine ee3(this->NewSeed());

	for(int i=0; i<10; i++)
	{
		std::cout << ee3() << std::endl;
	}
	std::cout << std::endl;

	for(int i=0; i<10; i++)
	{
		std::cout << this->Range(1, 256) << std::endl;
	}
	std::cout << std::endl;

	for(int i=0; i<10; i++)
	{
		std::cout << this->Range(0.0f, 1.0f) << std::endl;
	}
	std::cout << std::endl;

	*/
	
}

// During game loop
void RandomCtrlr::LoopRand()
{
	
}

// During release of program
void RandomCtrlr::FinalizeRand()
{
	
}

// Helpers =================================================

// Get a new time-based seed
unsigned long RandomCtrlr::NewSeed()
{
	return (unsigned long) std::chrono::steady_clock::now().time_since_epoch().count();
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