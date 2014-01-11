#ifndef DIFFICULTY_CTRLR
#define DIFFICULTY_CTRLR

class DifficultyCtrlr
{
public:
	// Singleton =================

	static DifficultyCtrlr* GetInstance();		// Public singleton instance getter

	// Game Sturcture ============

	void InitializeDifficulty();				// Initialize in beginning of program
	void LoopDifficulty();						// During game loop
	void FinalizeDifficulty();					// During release of program

private:
	// Singleton =================

	static DifficultyCtrlr* privGetInstance();	// Private singleton handler
	DifficultyCtrlr();							// Private constructor

	// Data ======================

	float spawnTimeOffset;						// Offset for enemy spawn time

};

#endif // !DifficultyCtrlr
