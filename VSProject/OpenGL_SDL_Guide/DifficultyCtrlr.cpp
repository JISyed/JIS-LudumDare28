#include "DifficultyCtrlr.h"

#include "TimeCtrlr.h"

#include <iostream>

// Singleton =============================================

// Constructor
DifficultyCtrlr::DifficultyCtrlr()
{
	// Setup stuff here
	this->spawnTimeLimit = 0.275f;
	this->spawnSizeLimit = 2.0f;
	this->spawnQuantityLimit = 4.0f;
	this->spawnSpeedLimit = 3.0f;
	this->spawnAccelLimit = 6.0f;

	this->spawnTimeRate = 0.008f;
	this->spawnSizeRate = 0.02f;
	this->spawnQuantityRate = 0.015f;
	this->spawnSpeedRate = 0.0005f;
	this->spawnAccelRate = 0.001f;
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
	this->spawnSizeOffset = 0.0f;
	this->spawnQuantityOffset = 0;
	this->spawnQuantityRateAccumulator = 0.0f;
}

// During game loop
void DifficultyCtrlr::LoopDifficulty()
{
	float dt = TimeCtrlr::GetInstance()->GetDeltaTime();

	if(this->spawnTimeOffset < this->spawnTimeLimit)
	{
		this->spawnTimeOffset += this->spawnTimeRate * dt;
	}

	if(this->spawnSizeOffset < this->spawnSizeLimit)
	{
		this->spawnSizeOffset += this->spawnSizeRate * dt;
	}

	if(this->spawnQuantityRateAccumulator < this->spawnQuantityLimit)
	{
		this->spawnQuantityRateAccumulator += this->spawnQuantityRate * dt;
	}

	this->spawnQuantityOffset = (int) spawnQuantityRateAccumulator;

	if(this->spawnSpeedOffset < this->spawnSpeedLimit)
	{
		this->spawnSpeedOffset += this->spawnSpeedRate * dt;
	}

	if(this->spawnAccelOffset < this->spawnAccelLimit)
	{
		this->spawnAccelOffset += this->spawnAccelRate * dt;
	}
}

// During release of program
void DifficultyCtrlr::FinalizeDifficulty()
{
	this->spawnTimeOffset = 0.0f;
	this->spawnSizeOffset = 0.0f;
	this->spawnQuantityOffset = 0;
	this->spawnQuantityRateAccumulator = 0.0f;
}

// Routines =================================================

// Offset for enemy spawn time
float DifficultyCtrlr::GetSpawnTimeOffset()
{
	return this->spawnTimeOffset;
}

// Offset for spawned enemy size
float DifficultyCtrlr::GetSpawnSizeOffset()
{
	return this->spawnSizeOffset;
}

// Offset for how many enemies to spawn
int DifficultyCtrlr::GetSpawnQuantityOffset()
{
	return this->spawnQuantityOffset;
}

// Offset of enemy's start speed
float DifficultyCtrlr::GetSpawnSpeedOffset()
{
	return this->spawnSpeedOffset;
}

// Offset of enemy's acceleration
float DifficultyCtrlr::GetSpawnAccelOffset()
{
	return this->spawnAccelOffset;
}