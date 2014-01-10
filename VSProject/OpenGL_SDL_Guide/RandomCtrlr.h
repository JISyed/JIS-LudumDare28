#ifndef RANDOM_CTRLR
#define RANDOM_CTRLR

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

	int Range(int min, int max);			// Get an int between min and max
	float Range(float min, float max);		// Get a float between min and max

private:
	// Singleton =================

	static RandomCtrlr* privGetInstance();	// Private Instance Getter
	RandomCtrlr();							// Private ctor

	// Helpers ===================

	unsigned long NewSeed();				// Get a new time-based seed

	// Data ======================

	unsigned long timeSeed;					// Time since epoch
};

#endif