#pragma once

#include "stdafx.h"
#include "InputInfo.h"

namespace newPix
{

	class InputMgr
	{
	public:
		__declspec(dllexport) InputMgr();
		__declspec(dllexport) ~InputMgr();
		__declspec(dllexport) bool initialise();

		__declspec(dllexport) InputInfo* getInputInfo();
		__declspec(dllexport) void keyPressed(SDLKey key);
		__declspec(dllexport) void keyReleased(SDLKey key);
		__declspec(dllexport) void mousePressed(uint16 id);
		__declspec(dllexport) void mouseReleased(uint16 id);
		__declspec(dllexport) void mouseMoved(SDL_MouseMotionEvent evt);
		__declspec(dllexport) void processBuffers();

	private:
		InputInfo* mInputInfo;
		std::vector<uint16> mKeyBuffer;
		std::vector<uint16> mMouseBuffer;
	};

}