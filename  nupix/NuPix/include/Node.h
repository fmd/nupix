#pragma once

#include "stdafx.h" 
#include "Geometry.h"

namespace newPix
{
	struct AnimationState
	{
		AnimationState():
			paused(true)
		{}

		AnimationState(uint16 _start_frame, uint16 _end_frame, float _inv_fps, bool _repeat):
			frame_start_tick(0),
			current_frame(_start_frame),
			start_frame(_start_frame),
			end_frame(_end_frame),
			inv_fps(_inv_fps),
			repeat(_repeat),
			paused(false)
		{}

		uint32 frame_start_tick;
		uint16	current_frame,
				start_frame,
				end_frame;
		float	inv_fps;

		bool	repeat,
				paused;
	};
	struct GeometryState
	{
		GeometryState():
			mGeometry(NULL),
			mFrame(0),
			anim(AnimationState())
		{}
		Geometry* mGeometry;
		Frame* mFrame;
		AnimationState anim;
	};

	class Node
	{
	public:
		enum
		{
			NODE_DIRTY = 1,
			NODE_VISIBLE = 2,
		};

		__declspec(dllexport) Node();
		__declspec(dllexport) void update();

		__declspec(dllexport) void attachNode(Node* n);
		__declspec(dllexport) void attachGeometry(Geometry* g);
		__declspec(dllexport) void detachGeometry();
		__declspec(dllexport) void setZOrder(uint32 z);

		__declspec(dllexport) void bringToFront();
		__declspec(dllexport) void sendToBack();

		__declspec(dllexport) void gotoAndStop(const char* c);
		__declspec(dllexport) void gotoAndStop(uint16 n);
		__declspec(dllexport) void playAnimation(const char* c, bool repeat = false);

		__declspec(dllexport) void destroy();
		__declspec(dllexport) void destroyAllChildren();

		__declspec(dllexport) Node* createChildNode(const Position& pos);

		__declspec(dllexport) void rotate(float r);
		__declspec(dllexport) void translate(float x, float y);
		__declspec(dllexport) ~Node();

		static void destroyAll();
		void propagateDirt();

		uint8 mFlags;
		Node* mParent;
		
		GeometryState mGeometryState;

		float mMatrix[16];
		float mAlpha;
		Position mPosition;

		std::list<Node*>::iterator mRenderIt;
		static std::list<Node*> mRenderList;
	private:
		Node(Node* parent, const Position& pos);
		void kill(); //the buffer between destroy and delete.

		std::vector<Node*> mNodes;
		std::list<Node*>::iterator mDestroyIt;
		static std::list<Node*> mDestroyList;
	};
}