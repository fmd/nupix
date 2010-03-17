#include "Node.h"
#include "NPCore.h"
#include "Texture.h"
#include "Geometry.h"

using namespace newPix;

std::list<Node*> Node::mRenderList;
std::list<Node*> Node::mDestroyList;

Node::Node():
	mAlpha(1.0f),
	mGeometryState(GeometryState())
{
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX,mMatrix);

	mParent = this;
	mPosition = Position(0,0,0);	
	//mFlags |= NODE_DIRTY;
	mDestroyList.push_back(this);
	mDestroyIt = (--mDestroyList.end());
}

Node::Node(Node* parent, const Position& pos):
	mAlpha(1.0f),
	mGeometryState(GeometryState())
{
	mParent = parent;
	mPosition = pos;	
	mFlags |= NODE_DIRTY;
	mDestroyList.push_back(this);
	mDestroyIt = (--mDestroyList.end());
}

void Node::propagateDirt()
{
	mFlags |= NODE_DIRTY;
	if (mNodes.size() > 0)
		for (std::vector<Node*>::iterator it = mNodes.begin(); it != mNodes.end(); it++)
			(*it)->propagateDirt();	
}

void Node::translate(float x, float y)
{
	mPosition.x += x;
	mPosition.y += y;
	propagateDirt();
}

void Node::rotate(float r)
{
	mPosition.r += r;
	regulateR(mPosition.r);
	propagateDirt();
}
void Node::destroyAllChildren()
{	
	for (std::vector<Node*>::iterator it = mNodes.begin(); it != mNodes.end(); it++)
		delete (*it);

	mNodes.clear();
}

void Node::destroy()
{
	if (mParent->mNodes.size() > 0)
		for (std::vector<Node*>::iterator it = mParent->mNodes.begin(); it != mParent->mNodes.end(); it++)
			if ((*it) == this)
			{
				mParent->mNodes.erase(it);
				break;
			}
	delete this;
}

void Node::kill()
{
	if (mNodes.size() > 0)
		for (std::vector<Node*>::iterator it = mNodes.begin(); it != mNodes.end(); it++)
			(*it)->kill();

	mDestroyList.erase(mDestroyIt);
	if (mGeometryState.mGeometry != NULL)
		mRenderList.erase(mRenderIt);
}

Node::~Node()
{

}

Node* Node::createChildNode(const Position& pos)
{
	Node* ret;
	ret = new Node(this, pos);
	mNodes.push_back(ret);

	return ret;
}

void Node::update()
{
	glLoadMatrixf(mParent->mMatrix);
	glTranslatef(mPosition.x, mPosition.y,0);
	glRotatef(mPosition.r,0,0,-1);
	glGetFloatv(GL_MODELVIEW_MATRIX,mMatrix);
	
	mFlags &= ~NODE_DIRTY; 

	std::vector<Node*>::iterator it;
	for (it = mNodes.begin(); it != mNodes.end(); it++)
		(*it)->update();
}

void Node::attachNode(Node* n)
{
	mNodes.push_back(n);
	n->mParent = this;
	n->mFlags |= NODE_DIRTY;
}

void Node::attachGeometry(Geometry* g)
{
	if (mGeometryState.mGeometry == NULL)
	{
		mRenderList.push_back(this);
		mRenderIt = (--mRenderList.end());
	}
	mGeometryState.mGeometry = g;
	mGeometryState.mFrame = g->mFrame;
}

void Node::detachGeometry()
{
	mGeometryState.mGeometry = NULL;
	mRenderList.erase(mRenderIt);
}

void Node::bringToFront()
{
	mRenderList.erase(mRenderIt);
	mRenderList.push_back(this);
	mRenderIt = (--mRenderList.end());
}

void Node::sendToBack()
{
	mRenderList.erase(mRenderIt);
	mRenderList.push_front(this);
	mRenderIt = (mRenderList.begin());
}

void Node::setZOrder(uint32 z)
{
	if (mGeometryState.mGeometry != NULL)
	{
		if (z <= 1)
		{
			mRenderList.erase(mRenderIt);
			mRenderList.push_back(this);
			mRenderIt = (--mRenderList.end());
		}
		else if (z > mRenderList.size())
		{	
			mRenderList.erase(mRenderIt);
			mRenderList.push_front(this);
			mRenderIt = (mRenderList.begin());
		}
		else
		{
			mRenderList.erase(mRenderIt);
			std::list<Node*>::iterator it = mRenderList.begin();
			std::advance(it, (z-1));
			mRenderList.insert(it, this);
		}
	}
}

void Node::destroyAll()
{
	for (std::list<Node*>::iterator it = mDestroyList.begin(); it != mDestroyList.end(); it++)
	{
		delete (*it);
	}

	mDestroyList.clear();
	mRenderList.clear();
}

void Node::playAnimation(const char* c, bool repeat)
{
	Animation a = mGeometryState.mGeometry->mTexture->mAnimations[std::string(c)];
	mGeometryState.anim.current_frame = a.start_frame;
	mGeometryState.anim.start_frame = a.start_frame;
	mGeometryState.anim.end_frame = a.end_frame;
	mGeometryState.anim.inv_fps = a.inv_fps;
	mGeometryState.anim.repeat = repeat;
	mGeometryState.anim.paused = false;
	mGeometryState.anim.frame_start_tick = SDL_GetTicks();

	mGeometryState.mFrame = mGeometryState.mGeometry->mTexture->getFrame(mGeometryState.anim.current_frame);
}


void Node::gotoAndStop(const char* c)
{
	if (mGeometryState.mGeometry != NULL && mGeometryState.mGeometry->mDynamic)
	{
		mGeometryState.mFrame = mGeometryState.mGeometry->mTexture->getFrame(c);
	}
}

void Node::gotoAndStop(uint16 n)
{
	if (mGeometryState.mGeometry != NULL && mGeometryState.mGeometry->mDynamic)
	{
		mGeometryState.mFrame = mGeometryState.mGeometry->mTexture->getFrame(n);
	}
}
