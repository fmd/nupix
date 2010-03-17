#include "VideoMgr.h"
#include <iostream>
using namespace newPix;

VideoMgr::VideoMgr()
{
	
}

VideoMgr::~VideoMgr()
{
	printf("  -VideoMgr... ");

	printf("Done.\n");
}

bool VideoMgr::initialise(VideoSettings settings)
{
	printf("  -VideoMgr... ");
	
	SDL_Init(SDL_INIT_VIDEO);

    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 16);
	//SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 16);
	//SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 16);
	//SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);

	uint32 flags = SDL_OPENGL;

	if (settings.fullscreen)
		flags ^= SDL_FULLSCREEN;

	mScreen = SDL_SetVideoMode(	settings.screenW, 
								settings.screenH, 
								0,
								flags);

	if (mScreen == NULL)
	{
		printf("Can't get video mode:%s\n",SDL_GetError());
		return false;
	}

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return false;
	}

	printf("\n    -Vendor: %s", glGetString(GL_VENDOR));
	printf("\n    -Renderer: %s\n", glGetString(GL_RENDERER));
	printf("\n    -Version: %s\n", glGetString(GL_VERSION));
	printf("\n    -Extensions: %s\n", glGetString(GL_EXTENSIONS));

	glClearColor(0.0,0.0,0.0,1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, mScreen->w, mScreen->h);
	gluOrtho2D(-mScreen->w/2, mScreen->w/2, -mScreen->h/2, mScreen->h/2);

	//Required for per-pixel placing.
	glTranslatef (0.375, 0.375, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_DITHER);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); 

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_BLEND);
	//glEnable(GL_ALPHA_TEST);
	//glDepthFunc(GL_LEQUAL);	

	glDisable(GL_DEPTH_TEST);
	printf("Done.\n");

	return true;
}

SDL_Surface* VideoMgr::getScreen()
{
	return mScreen;
}