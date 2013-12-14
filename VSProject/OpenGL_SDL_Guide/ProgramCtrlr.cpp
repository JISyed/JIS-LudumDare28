#include "ProgramCtrlr.h"

#include "GraphicsCtrlr.h"

#include <iostream>

// Ctor
ProgramCtrlr::ProgramCtrlr()
{

}

// Dtor
ProgramCtrlr::~ProgramCtrlr()
{

}

// Setup the program components
void ProgramCtrlr::InitializeProgram()
{
	// Start SDL
	SDL_Init(SDL_INIT_VIDEO);

	int width = 800;
	int height = 600;

	// Make a window
	this->theWindow = SDL_CreateWindow("OpenGL Tutorial", 100, 100, width, height, SDL_WINDOW_OPENGL);

	// Make a graphics canvas (OpenGL context)
	this->theGLContext = SDL_GL_CreateContext(this->theWindow);

	// Make a OpenGL graphics manager
	this->graphicsCtrlr = GraphicsCtrlr::GetInstance();
	graphicsCtrlr->SetWindowSize(width, height);

	// Initilaize everything for graphics
	graphicsCtrlr->InitializeGraphics();
}

// Run the program every frame
void ProgramCtrlr::LoopProgram(bool& shouldQuit)
{
	// Poll for window events
	if (SDL_PollEvent(&(this->windowEvent)))
		{
			// Leave main loop when X on window corner is pressed
			if (this->windowEvent.type == SDL_QUIT)
			{
				shouldQuit = true;
				return;
			}

			// Leave main loop if escape key was released
			if (this->windowEvent.type == SDL_KEYUP && 
				this->windowEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				shouldQuit = true;
				return;
			}
		}

		// Clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// The Graphics Loop
		graphicsCtrlr->LoopGraphics();

		// glSwapBuffers - swap between the front and back render buffer
		SDL_GL_SwapWindow(this->theWindow);
}

// Deallocate everything in the program
void ProgramCtrlr::FinalizeProgram()
{
	// Delete everything for graphics
	graphicsCtrlr->ReleaseGraphics();

	// Delete graphics canvas (OpenGL context)
	SDL_GL_DeleteContext(this->theGLContext);

	// Free SDL
	SDL_Quit();
}