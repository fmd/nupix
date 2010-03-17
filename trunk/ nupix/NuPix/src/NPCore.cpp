#include "NPCore.h"

using namespace newPix;

NPCore* NPCore::mInstance = 0;

NPCore::NPCore()
{

}

bool NPCore::initialise(const VideoSettings& vidset)
{
	printf("Initialising newPix Core:\n");

	mVideoMgr = new VideoMgr();
	if (!mVideoMgr->initialise(vidset))
		return false;

	mInputMgr = new InputMgr();
	if (!mInputMgr->initialise())
		return false;

	mGeometryMgr = new GeometryMgr();
	if (!mGeometryMgr->initialise())
		return false;

	mTextureMgr = new TextureMgr();
	if (!mTextureMgr->initialise())
		return false;

	mRootNode = new Node();
	mPreviousTime = SDL_GetTicks();
	mTimeSinceLastFrame = 0;
	printf("Initialised newPix Core.\n\n");
	return true;
}

void NPCore::shutdown()
{
	//PROFILER_OUTPUT("out.txt");
	printf("Shutting down newPix Core:\n");
	delete this;
}

NPCore::~NPCore()
{
	delete mGeometryMgr;
	delete mTextureMgr;
	delete mInputMgr;
	delete mVideoMgr;
	printf("  -Nodes... ");
	Node::destroyAll();
	printf("Done.\n");
	SDL_Quit();
	printf("Shut down newPix Core.\n\n");
}

NPCore* NPCore::getPtr()
{
	if (!mInstance)
		mInstance = new NPCore();

	return mInstance;
}

VideoMgr* NPCore::getVideoMgr()
{
	return mVideoMgr;
}

InputMgr* NPCore::getInputMgr()
{
	return mInputMgr;
}

TextureMgr* NPCore::getTextureMgr()
{
	return mTextureMgr;
}

Node* NPCore::getRootNode()
{
	return mRootNode;
}

uint32 NPCore::getTimeSinceLastFrame()
{
	return mTimeSinceLastFrame;
}

void NPCore::processOneFrame()
{
		uint32 currTime = SDL_GetTicks();
		mTimeSinceLastFrame = currTime - mPreviousTime;
		mPreviousTime = currTime;

		//PROFILE_BEGIN(buffers);
		mInputMgr->processBuffers();
		//PROFILE_END();

		//PROFILE_BEGIN(swap_window);
		SDL_GL_SwapBuffers();
		//PROFILE_END();

		//PROFILE_BEGIN(sdl_event);
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
					mInputMgr->keyPressed(event.key.keysym.sym);
				break;

				case SDL_KEYUP:
					mInputMgr->keyReleased(event.key.keysym.sym);
				break;

				case SDL_MOUSEMOTION:
					mInputMgr->mouseMoved(event.motion);
				break;

				case SDL_MOUSEBUTTONDOWN:
					mInputMgr->mousePressed(event.button.button);
				break;

				case SDL_MOUSEBUTTONUP:
					mInputMgr->mouseReleased(event.button.button);
				break;
			}
		}
		//PROFILE_END();

		//PROFILE_BEGIN(gl_ident_and_clear);
		glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//PROFILE_END();

		mGeometryMgr->render();

		//PROFILER_UPDATE();

}

GeometryMgr* NPCore::getGeometryMgr()
{
	return mGeometryMgr;
}