#include "NPCore.h"
#include "GeometryMgr.h"
#include "TextureMgr.h"
#include "Geometry.h"

using namespace newPix;

Geometry::Geometry(GeometryDef def)
{	
	mDynamic = def.dynamic;

	VBOInfo* v = NPCore::getPtr()->getGeometryMgr()->mVBOs.back();
	mIndex = v->mCurrentIndex;
	mVertexVBO = v->mVertexVBO;
	mTexCoordVBO = v->mTexCoordVBO;


	if (strcmp(def.t,"__bad"))
	{
		mTexture = NPCore::getPtr()->getTextureMgr()->getTexture(def.t);
		if (strcmp(def.f,"__bad"))
			mFrame = mTexture->getFrame(def.f);
		else
			mFrame = mTexture->getFrame(def.f_num);
	}
	else
	{
		mTexture = NPCore::getPtr()->getTextureMgr()->getTexture("null");
		mFrame = NPCore::getPtr()->getTextureMgr()->getTexture("null")->getFrame(0);
	}

	if (!mDynamic)
	{
		mWidth = def.w;
		mHeight = def.h;

		float v_lx = 0.0f - mWidth/2;
		float v_by = 0.0f - mHeight/2;
		float v_rx = v_lx + mWidth;
		float v_ty = v_by + mHeight;
		
		float v[] = {v_lx,v_by,v_rx,v_by,v_rx,v_ty,v_lx,v_ty};
		float t[] = {mFrame->t_lx,mFrame->t_by,mFrame->t_rx,mFrame->t_by,mFrame->t_rx,mFrame->t_ty,mFrame->t_lx,mFrame->t_ty};

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, mTexCoordVBO);
		glBufferSubDataARB(GL_ARRAY_BUFFER_ARB,sizeof(float)*2*mIndex, sizeof(float)*8, t);

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, mVertexVBO);
		glBufferSubDataARB(GL_ARRAY_BUFFER_ARB,sizeof(float)*2*mIndex, sizeof(float)*8, v);
	}
}

Geometry::~Geometry()
{

}

/*
void Geometry::update()
{
	PROFILE_FUNC();


	
	float _lx = 0.0f - mWidth/2;
	float _by = 0.0f - mHeight/2;
	float _rx = _lx + mWidth;
	float _ty = _by + mHeight;

	float coord[16] = {	 1, 0, 0, 0,
					 	 0, 1, 0, 0,
					 	 0, 0, 1, 0,
					  	 _lx, _by, 0, 1};
	
	float m[16];

	glPushMatrix();
	glMultMatrixf(coord);
	glGetFloatv(GL_MODELVIEW_MATRIX,m);
	glPopMatrix();

	(*mIt).bl_x = m[12];
	(*mIt).bl_y = m[13];

	coord[12] = _rx;

	glPushMatrix();
	glMultMatrixf(coord);
	glGetFloatv(GL_MODELVIEW_MATRIX,m);
	glPopMatrix();

	(*mIt).br_x = m[12];
	(*mIt).br_y = m[13];

	coord[12] = _rx;
	coord[13] = _ty;

	glPushMatrix();
	glMultMatrixf(coord);
	glGetFloatv(GL_MODELVIEW_MATRIX,m);
	glPopMatrix();

	(*mIt).tr_x = m[12];
	(*mIt).tr_y = m[13];

	coord[12] = _lx;
	coord[13] = _ty;

	glPushMatrix();
	glMultMatrixf(coord);
	glGetFloatv(GL_MODELVIEW_MATRIX,m);
	glPopMatrix();

	(*mIt).tl_x = m[12];
	(*mIt).tl_y = m[13];
}*/