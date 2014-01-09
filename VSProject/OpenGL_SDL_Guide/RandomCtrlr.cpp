#include "RandomCtrlr.h"

#include <iostream>
#include <ctime>

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
	
}

// During game loop
void RandomCtrlr::LoopRand()
{
	
}

// During release of program
void RandomCtrlr::FinalizeRand()
{
	
}

// Routines ================================================

