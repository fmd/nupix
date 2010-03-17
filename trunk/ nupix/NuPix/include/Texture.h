#pragma once

#include "stdafx.h"
#include "Frame.h"

namespace newPix
{
	struct Animation
	{
		Animation(const char* _tag, uint16 _start_frame, uint16 _end_frame, uint16 _fps = 20, const char* _start_tag = "__bad", const char* _end_tag = "__bad"):
			tag(_tag),
			start_tag(_start_tag),
			end_tag(_end_tag),
			start_frame(_start_frame),
			end_frame(_end_frame),
			fps(_fps)
		{inv_fps = (1/float(fps))*1000;}

		Animation():
			tag("__bad"),
			start_tag("__bad"),
			end_tag("__bad"),
			start_frame(0),
			end_frame(0),
			fps(20)
		{inv_fps = (1/float(fps))*1000;}

		const char	* tag,
					* start_tag,
					* end_tag;
		uint16	start_frame,
				end_frame,
				fps;
		float inv_fps;
	};
	class Texture
	{
	public:
		__declspec(dllexport) Texture();
		__declspec(dllexport) Texture(uint32 id, uint16 w, uint16 h);
		__declspec(dllexport) ~Texture();
		__declspec(dllexport) void loadFrame(FrameInfo frame);
		__declspec(dllexport) void loadAnimation(Animation anim);

		__declspec(dllexport) Frame* getFrame(uint16 n);
		__declspec(dllexport) Frame* getFrame(std::string c);
		__declspec(dllexport) std::vector<Frame>* getFrameList();
		__declspec(dllexport) std::map<std::string, uint16>* getTagMap();

		std::map<std::string, uint16> mTagMap;
		std::vector<Frame> mFrames;
		std::map<std::string, Animation> mAnimations;

		uint32 mID;
		uint16 mWidth;
		uint16 mHeight;
	};

}