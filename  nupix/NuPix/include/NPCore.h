#pragma once

#include "stdafx.h"

#include "Node.h"
#include "GeometryMgr.h"
#include "VideoMgr.h"
#include "InputMgr.h"
#include "TextureMgr.h"

namespace newPix
{
	class NPCore
	{
	public:
		__declspec(dllexport) ~NPCore();
		__declspec(dllexport) bool initialise(const VideoSettings& vidset = VideoSettings());
		__declspec(dllexport) void shutdown();
		__declspec(dllexport) static NPCore* getPtr();
		__declspec(dllexport) GeometryMgr* getGeometryMgr();
		__declspec(dllexport) VideoMgr* getVideoMgr();
		__declspec(dllexport) InputMgr* getInputMgr();
		__declspec(dllexport) TextureMgr* getTextureMgr();
		__declspec(dllexport) void processOneFrame();
		__declspec(dllexport) uint32 getTimeSinceLastFrame();
		__declspec(dllexport) Node* getRootNode();

	private:
		__declspec(dllexport) NPCore();

		uint32 	mPreviousTime,
				mTimeSinceLastFrame;
		static NPCore* mInstance;
		GeometryMgr* mGeometryMgr;
		VideoMgr* mVideoMgr;
		InputMgr* mInputMgr;
		TextureMgr* mTextureMgr;
		Node* mRootNode;
	};
}