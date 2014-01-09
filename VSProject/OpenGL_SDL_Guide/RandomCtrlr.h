#ifndef RANDOM_CTRLR
#define RANDOM_CTRLR

#include <random>
#include <cstdlib>

class RandomCtrlr
{
public:
	// Singleton =================

	static RandomCtrlr* GetInstance();		// Singleton Instance Getter

	// Game Sturcture ============

	void InitializeRand();					// Initialize in beginning of program
	void LoopRand();						// During game loop
	void FinalizeRand();					// During release of program

	// Routines ==================

	

private:
	// Singleton =================

	static RandomCtrlr* privGetInstance();	// Private Instance Getter
	RandomCtrlr();							// Private ctor

	// Data ======================

	
};

#endif