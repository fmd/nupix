#pragma once

#include "stdafx.h" 

namespace newPix
{	
	class Node;
	class Frame;
	class Texture;
	struct StaticVBO;
	struct DynamicVBO;

	struct GeometryDef
	{
		GeometryDef::GeometryDef():
			dynamic(false),
			t("__bad"),
			f("__bad"),
			f_num(0),
			w(2.0f),
			h(2.0f)
			{}

		const char* t;
		const char* f;
		uint32 f_num;
		float w, h;
		bool dynamic;
	};

	class Geometry
	{
	public:
		Geometry(GeometryDef def);
		~Geometry();

		uint32	mIndex,
				mVertexVBO,
				mTexCoordVBO;
		bool mDynamic;
		Texture* mTexture;
		Frame* mFrame; //Default frame for dynamics, only frame for statics.
		float	mWidth,
				mHeight;
	};
}
