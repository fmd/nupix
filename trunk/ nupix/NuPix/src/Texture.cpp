#include "NPCore.h"
#include "GeometryMgr.h"
#include "Texture.h"

using namespace newPix;

Texture::Texture()
{

}

Texture::Texture(uint32 id, uint16 w, uint16 h):
	mID(id),
	mWidth(w),
	mHeight(h)
{
	FrameInfo f;
	f.tag = "null";
	f.w = mWidth;
	f.h = mHeight;

	loadFrame(f);
}

Texture::~Texture()
{

}

void Texture::loadAnimation(Animation anim)
{
	if (strcmp(anim.start_tag,"__bad"))
		anim.start_frame = mTagMap[std::string(anim.start_tag)];
	if (strcmp(anim.end_tag,"__bad"))
		anim.start_frame = mTagMap[std::string(anim.end_tag)];

	mAnimations[std::string(anim.tag)] = anim;
}

void Texture::loadFrame(FrameInfo frame)
{
	GeometryMgr* gm = NPCore::getPtr()->getGeometryMgr();
	VBOInfo* v = gm->mVBOs.back();

	if (v->mCurrentIndex >= 4096)
	{
		v = new VBOInfo();
		gm->mVBOs.push_back(v);
	}
	Frame f = Frame(v->mVertexVBO, v->mTexCoordVBO, v->mCurrentIndex, mWidth,mHeight,frame);
	mFrames.push_back(f);
	v->mCurrentIndex += 4;

	float _t[] = {f.t_lx,f.t_ty,f.t_rx,f.t_ty,f.t_rx, f.t_by, f.t_lx, f.t_by};
	float _v[] = {f.v_lx,f.v_by,f.v_rx,f.v_by,f.v_rx, f.v_ty, f.v_lx, f.v_ty};
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f.mTexCoordVBO);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(float)*2*f.mIndex, sizeof(float)*8, _t);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f.mVertexVBO);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(float)*2*f.mIndex, sizeof(float)*8, _v);

	if (strcmp(frame.tag,"__bad"))
		mTagMap[std::string(frame.tag)] = uint16(mFrames.size()-1);
}

Frame* Texture::getFrame(uint16 n)
{
	return &mFrames.at(n);
}

Frame* Texture::getFrame(std::string c)
{
	return &mFrames.at(mTagMap[c]);
}

std::vector<Frame>* Texture::getFrameList()
{
	return &mFrames;
}
std::map<std::string, uint16>* Texture::getTagMap()
{
	return &mTagMap;
}
