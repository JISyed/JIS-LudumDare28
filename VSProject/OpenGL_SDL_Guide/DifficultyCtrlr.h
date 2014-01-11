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

	// Routines ==================

	float GetSpawnTimeOffset();					// Offset for enemy spawn time
	float GetSpawnSizeOffset();					// Offset for spawned enemy size
	int GetSpawnQuantityOffset();				// Offset for how many enemies to spawn
	float GetSpawnSpeedOffset();				// Offset of enemy's start speed
	float GetSpawnAccelOffset();				// Offset of enemy's acceleration

private:
	// Singleton =================

	static DifficultyCtrlr* privGetInstance();	// Private singleton handler
	DifficultyCtrlr();							// Private constructor

	// Data ======================

	float spawnTimeOffset;						// Offset for enemy spawn time
	float spawnSizeOffset;						// Offset for spawned enemy size
	int spawnQuantityOffset;					// Offset for how many enemies to spawn
	float spawnSpeedOffset;						// Offset of enemy's start speed
	float spawnAccelOffset;						// Offset of enemy's acceleration

	float spawnTimeLimit;						// Limit to the offset of enemy spawn time
	float spawnSizeLimit;						// Max enemy scaling offset
	float spawnQuantityLimit;					// Max additional enemy spawn amount
	float spawnSpeedLimit;						// Max limit to spawn speed offset
	float spawnAccelLimit;						// Max limit to spawn acceleration offset

	float spawnTimeRate;						// Rate to change time offset every dt
	float spawnSizeRate;						// Rate to change size offset every dt
	float spawnQuantityRate;					// Rate to increase spawn quantity (gets rounded)
	float spawnSpeedRate;						// Rate to change initial spawn speed every dt
	float spawnAccelRate;						// Rate to change spawn acceleratoin every dt

	float spawnQuantityRateAccumulator;			// Used to accumulate the quantity rate which gets rounded

};

#endif // !DifficultyCtrlr
