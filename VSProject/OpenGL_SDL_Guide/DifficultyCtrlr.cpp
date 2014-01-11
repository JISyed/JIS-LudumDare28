#include "DifficultyCtrlr.h"

#include "TimeCtrlr.h"

#include <iostream>

// Singleton =============================================

// Constructor
DifficultyCtrlr::DifficultyCtrlr()
{
	// Setup stuff here
}

// Public singleton instance getter
DifficultyCtrlr* DifficultyCtrlr::GetInstance()
{
	return DifficultyCtrlr::privGetInstance();
}

// Private singleton handler
DifficultyCtrlr* DifficultyCtrlr::privGetInstance()
{
	// Static object only initializes once
	static DifficultyCtrlr instance;
	return &instance;
}

// Game Sturcture =========================================

// Initialize in beginning of program
void DifficultyCtrlr::InitializeDifficulty()
{
	this->spawnTimeOffset = 0.0f;
}

// During game loop
void DifficultyCtrlr::LoopDifficulty()
{
	float dt = TimeCtrlr::GetInstance()->GetDeltaTime();
	this->spawnTimeOffset += 0.001f * dt;
	//std::cout << "STO: " << this->spawnTimeOffset << std::endl;
}

// During release of program
void DifficultyCtrlr::FinalizeDifficulty()
{
	this->spawnTimeOffset = 0.0f;
}