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

// This should be made in the stack
class ProgramCtrlr
{
public:
	// Ctor/Dtor =================
	ProgramCtrlr();
	~ProgramCtrlr();

	// Program Structure =========
	void InitializeProgram();			// Setup the program components
	void LoopProgram(bool& shouldQuit);	// Run the program every frame
	void FinalizeProgram();				// Deallocate everything in the program

private:
	// Data ======================
	GraphicsCtrlr* graphicsCtrlr;		// STATIC instance of graphics wrapper
	GameObjectCtrlr* gameObjectCtrlr;	// STATIC instance of GameObject manager
	SDL_Window* theWindow;				// Game window handled by SDL
	SDL_GLContext theGLContext;			// OpenGL graphics context
	SDL_Event windowEvent;				// Program event handled by SDL per frame

};


#endif