#pragma once

#include "stdafx.h"

namespace newPix
{

	class VideoSettings
	{
	public:
		VideoSettings(	bool fs = false,
						uint16 sw = 800,
						uint16 sh = 600,
						const char* cap = "newPix Client"):
			fullscreen(fs),
			screenW(sw),
			screenH(sh),
			caption(cap)
		{}

		bool fullscreen;
		uint16 screenW;
		uint16 screenH;
		const char* caption;
	};

	class VideoMgr
	{
	public:
		__declspec(dllexport) VideoMgr();
		__declspec(dllexport) ~VideoMgr();
		__declspec(dllexport) bool initialise(VideoSettings settings);				
		__declspec(dllexport) SDL_Surface* getScreen();

	private:
		SDL_Surface* mScreen;
	};

}
