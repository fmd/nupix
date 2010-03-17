#include "GeometryMgr.h"
#include "Texture.h"
#include "Geometry.h"
#include "Node.h"

using namespace newPix;

GeometryMgr::GeometryMgr()
{

}

bool GeometryMgr::initialise()
{
	printf("  -GeometryMgr... ");
	VBOInfo* v = new VBOInfo();
	mVBOs.push_back(v);
	printf("Done.\n");
	return true;
}
Geometry* GeometryMgr::createGeometry(GeometryDef def)
{
	VBOInfo* mVBO = mVBOs.back();
	Geometry* g = new Geometry(def);
	if (!def.dynamic)
	{
		if (mVBO->mCurrentIndex >= 4096)
		{
			mVBO = new VBOInfo();
			mVBOs.push_back(mVBO);
		}
		mVBO->mCurrentIndex += 4;
	}
	mGeometry.push_back(g);
	return g;
}

/*
Geometry* GeometryMgr::createGeometry(GeometryDef def)
{
	Geometry* g;
	if (def.dynamic)
	{
		DynamicVBO* mVBO = mDynamicVBOs.back();
		if (mVBO->mGeometry.size() >= 1024)
		{
			DynamicVBO* v = new DynamicVBO();
			mDynamicVBOs.push_back(v);
			mVBO = v;
		}
		g = new Geometry(def);
		mVBO->mCurrentIndex += 4;
	} 
	else 
	{
		StaticVBO* mVBO = mStaticVBOs.back();
		if (mVBO->mGeometry.size() >= 1024)
		{
			StaticVBO* v = new StaticVBO();
			mStaticVBOs.push_back(v);
			mVBO = v;
		}
		g = new Geometry(def);
		mVBO->mCurrentIndex += 4;
	}

	return g;
}*/

void GeometryMgr::render()
{
	//OLD WAY:
	//iterate through each vbo, bind
	//iterate through each geometry to be rendered, bind.
	//iterate through each node, updating dirties, loadMatrix,
	//draw

	//NEW WAY:
	//GeoemtryToRender no longer exists.
	//Geometry no longer need a vector of parents.
	//Nodes: on geo ADD, add node to list. on geo REMOVE, remove node from list. We add and remove by Z. and store the iterator.in Node
	//on a Z change, we re-insert at the new position.
	//this function: we iterate through all the nodes to be drawn, updating dirties.
	//bind vbo, bind texture, loadMatrix, draw from geo index.

	//std::vector<Node*> vec;
	//vec.resize(m
	//std::copy(Node::mRenderList.begin(), Node::mRenderList.end(), vec.begin());

	uint32 oldVBO = 0, newVBO = 0;

	Geometry* g;
	Frame* f;
	Node* n;
	for (std::list<Node*>::iterator it = Node::mRenderList.begin(); it != Node::mRenderList.end(); it++)
	{
		n = (*it);
		g = n->mGeometryState.mGeometry;
		f = n->mGeometryState.mFrame;
		newVBO = g->mVertexVBO;
		if (g->mDynamic)
		{
			newVBO = n->mGeometryState.mFrame->mVertexVBO;
			if (!n->mGeometryState.anim.paused && float(SDL_GetTicks() - n->mGeometryState.anim.frame_start_tick) > n->mGeometryState.anim.inv_fps)
			{
				if (n->mGeometryState.anim.current_frame < n->mGeometryState.anim.end_frame)
					n->mGeometryState.anim.current_frame++;
				else if (n->mGeometryState.anim.repeat)
					n->mGeometryState.anim.current_frame = n->mGeometryState.anim.start_frame;
				else
					n->mGeometryState.anim.paused = true;

				n->mGeometryState.anim.frame_start_tick = SDL_GetTicks();

				n->mGeometryState.mFrame = n->mGeometryState.mGeometry->mTexture->getFrame(n->mGeometryState.anim.current_frame);
			}
			
		}

		if (oldVBO != newVBO)
		{
			oldVBO = newVBO;
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, g->mVertexVBO);
			glVertexPointer(2,GL_FLOAT,0,(char*)NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, g->mTexCoordVBO);
			glTexCoordPointer(2,GL_FLOAT,0,(char*)NULL);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		}

		glBindTexture(GL_TEXTURE_2D, g->mTexture->mID);

		if ((n->mFlags & Node::NODE_DIRTY) == Node::NODE_DIRTY)
		{
			while ((n->mParent->mFlags & Node::NODE_DIRTY) == Node::NODE_DIRTY)
			{
				n = n->mParent;
				n->mFlags &= ~Node::NODE_DIRTY;
			}
			n->update();
			n = (*it);
		}

		glLoadMatrixf(n->mMatrix);
		glColor4f(1.0f,1.0f,1.0f,n->mAlpha);
		if (!g->mDynamic)
		{
			glTranslatef(g->mFrame->mXOffset,g->mFrame->mYOffset,0);
			glDrawArrays(GL_QUADS,g->mIndex,4);
		}
		else
		{
			glTranslatef(n->mGeometryState.mFrame->mXOffset,n->mGeometryState.mFrame->mYOffset,0);
			glDrawArrays(GL_QUADS,n->mGeometryState.mFrame->mIndex,4);
		}
		
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
/*
void GeometryMgr::render()
{
	for (std::vector<IncrementalVBO*>::iterator it = mVBOs.begin(); it != mVBOs.end(); it++)
	{
		IncrementalVBO* v = (*it);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, v->mVertexVBO);
		glVertexPointer(2,GL_FLOAT,0,(char*)NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, v->mTexCoordVBO);
		glTexCoordPointer(2,GL_FLOAT,0,(char*)NULL);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		for (std::list<Geometry*>::iterator it = v->mGeometryToRender.begin(); it != v->mGeometryToRender.end(); it++)
		{
			Geometry* g = (*it);
			glBindTexture(GL_TEXTURE_2D, g->mTexture->mID);
			
			for (std::vector<Node*>::iterator nodeIt = g->mParents.begin(); nodeIt != g->mParents.end(); nodeIt++)
			{
				Node* n = (*nodeIt);
				if ((n->mFlags & Node::NODE_DIRTY) == Node::NODE_DIRTY)
				{
					while ((n->mParent->mFlags & Node::NODE_DIRTY) == Node::NODE_DIRTY)
					{
						n = n->mParent;
						n->mFlags &= ~Node::NODE_DIRTY;
					}
					n->update();
				}

				glLoadMatrixf((*nodeIt)->mMatrix);
				//glTranslatef(0,0,-(*nodeIt)->mZOrder);

				glDrawArrays(GL_QUADS,g->mIndex,4);
			}
			
		}

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}
*/
GeometryMgr::~GeometryMgr()
{
	for (std::vector<VBOInfo*>::iterator it = mVBOs.begin(); it != mVBOs.end(); it++)
		delete (*it);

	for (std::vector<Geometry*>::iterator git = mGeometry.begin(); git != mGeometry.end(); git++)
		delete (*git);

}

//vbos save geometry to render into a static vector
//we read from that and update any nodes that need updating. we save the attached nodes into a vector by z order.
//we then iterate through that vector and render the geometry at each node.