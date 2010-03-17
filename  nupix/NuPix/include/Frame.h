#pragma once	

#include "stdafx.h"

namespace newPix
{
	struct FrameInfo
	{
		FrameInfo():
			x(0),
			y(0),
			w(1),
			h(1),
			x_offset(0.0f),
			y_offset(0.0f),
			tag("__bad")
			{}
		const char* tag;

		uint16	w,
				h;

		uint16	x,
				y;

		float	x_offset,
				y_offset;
	};

	class Frame
	{
	public:
		Frame(uint16 v_vbo, uint16 t_vbo, uint16 index, uint16 tw, uint16 th,FrameInfo frame);
		~Frame();

		uint16	mVertexVBO,
				mTexCoordVBO,
				mIndex;

		float	mXOffset,
				mYOffset,
				
				mWidth,
				mHeight;

		float	t_lx,
				t_rx,
				t_by,
				t_ty,

				v_lx,
				v_rx,
				v_by,
				v_ty;
	};
}