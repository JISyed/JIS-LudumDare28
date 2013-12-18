// Program Controller (ProgramCtrlr)
// Handles application level tasks with SDL
//
// Written by Jibran Syed

#ifndef PROGRAM_CTRLR
#define PROGRAM_CTRLR

#if defined(_MSC_VER)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

class GraphicsCtrlr;
class GameObjectCtrlr;
class GameLogicCtrlr;
class TimeCtrlr;

// This should be made in the stack
class ProgramCtrlr
{
public:
	// Singleton =================

	static ProgramCtrlr* GetInstance();	// Singleton Instance Getter

	// Program Structure =========

	void InitializeProgram();			// Setup the program components
	void LoopProgram(bool& shouldQuit);	// Run the program every frame
	void FinalizeProgram();				// Deallocate everything in the program

	// Routines ===================

	static void MarkProgramForReset();	// Marks the program for resetting

private:
	// Data ======================

	GraphicsCtrlr* graphicsCtrlr;		// STATIC instance of graphics wrapper
	GameObjectCtrlr* gameObjectCtrlr;	// STATIC instance of GameObject manager
	GameLogicCtrlr* gameLogicCtrlr;		// STATIC instance of game's logic
	TimeCtrlr* timeCtrlr;				// STATIC instance to time functionality
	SDL_Window* theWindow;				// Game window handled by SDL
	SDL_GLContext theGLContext;			// OpenGL graphics context
	SDL_Event windowEvent;				// Program event handled by SDL per frame

	static bool shouldReset;			// Flag if program should reset

	// Helpers ===================

	void ResetProgram();				// Actually resets the program
	static ProgramCtrlr* privGetInstance();	// Private Instance Getter
	ProgramCtrlr();						// Ctor

};


#endif