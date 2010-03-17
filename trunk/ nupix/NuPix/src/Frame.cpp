#include "Frame.h"

using namespace newPix;

Frame::Frame(uint16 v_vbo, uint16 t_vbo, uint16 index, uint16 tw, uint16 th, FrameInfo frame)
{
	mTexCoordVBO = t_vbo;
	mVertexVBO = v_vbo;
	mIndex = index;
	mWidth = float(frame.w);
	mHeight = float(frame.h);
	mXOffset = frame.x_offset;
	mYOffset = frame.y_offset;

	t_lx = (float(frame.x)/float(tw));
	t_by = float(frame.y)/float(th);
	t_rx = t_lx + (float(frame.w)/float(tw));
	t_ty = t_by + float(frame.h)/float(th);

	v_lx = 0.0f - mWidth/2;
	v_by = 0.0f - mHeight/2;
	v_rx = v_lx + mWidth;
	v_ty = v_by + mHeight;
}

Frame::~Frame()
{

}