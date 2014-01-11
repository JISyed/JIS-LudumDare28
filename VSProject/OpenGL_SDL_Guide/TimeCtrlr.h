#ifndef TIME_CTRLR
#define TIME_CTRLR

#include <chrono>

typedef std::chrono::system_clock StandardClock;
typedef std::chrono::time_point<StandardClock> PointInTime;
typedef std::chrono::duration<float> TimeDuration;

class TimeCtrlr
{
public:
	// Singleton =================

	static TimeCtrlr* GetInstance();		// Singleton Instance Getter

	// Game Sturcture ============

	void InitializeTime();					// Initialize in beginning of program
	void LoopTime();						// During game loop
	void FinalizeTime();					// During release of program

	// Routines ==================

	float GetDeltaTime();					// Get time last loop completed (in seconds)
	float GetRunTime();						// Get time since launched game (in seconds)

private:
	// Singleton =================

	static TimeCtrlr* privGetInstance();	// Private Instance Getter
	TimeCtrlr();							// Private ctor

	// Data ======================

	PointInTime updateStartTime;			// Time Point when update started
	PointInTime gameStartTime;				// Time Point when game started running
	TimeDuration loopDuration;				// Time duration of program loop
};



#endif
