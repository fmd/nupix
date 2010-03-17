#pragma once

#include "stdafx.h"
#include "Geometry.h"

namespace newPix
{
	struct VBOInfo
	{
		VBOInfo():
			mCurrentIndex(0),
			mVertexVBO(0),
			mTexCoordVBO(0)
		{
			glGenBuffersARB(1, &mVertexVBO);
			glGenBuffersARB(1, &mTexCoordVBO);

			float t[4096];
			float v[4096];

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, mTexCoordVBO);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(float)*4096, t,GL_STATIC_DRAW);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, mVertexVBO);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(float)*4096, v,GL_STATIC_DRAW);
		}
		~VBOInfo()
		{
			glDeleteBuffers(1,&mVertexVBO);
			glDeleteBuffers(1,&mTexCoordVBO);

		}
		uint32 	mVertexVBO,
				mTexCoordVBO,
				mCurrentIndex;
	};

	class GeometryMgr
	{
	public:
		GeometryMgr();
		~GeometryMgr();
		__declspec(dllexport) Geometry* createGeometry(GeometryDef def);
		void render();
		bool initialise();
		
		std::vector<Geometry*> mGeometry;
		std::vector<VBOInfo*> mVBOs;
	};
}