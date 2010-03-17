#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif

#include <newPix.h>

using namespace newPix;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	NPCore* core = NPCore::getPtr();

	VideoSettings v;
	v.screenW = 640;
	v.screenH = 480;
	v.fullscreen = false;
	core->initialise(v);
	InputInfo* info = core->getInputMgr()->getInputInfo();

	core->getTextureMgr()->addTexture("media/newguysheet.png","guy",GL_NEAREST,GL_NEAREST);
	FrameInfo f;
	f.x = 0;
	f.y = 0;
	f.w = 24;
	f.h = 72;
	f.tag = "stand";
	f.x_offset = 0;
	f.y_offset = 0;
	core->getTextureMgr()->getTexture("guy")->loadFrame(f);

	f.x = 24;
	f.y = 0;
	f.w = 24;
	f.h = 72;
	f.tag = "walk_start";
	f.x_offset = 0;
	f.y_offset = 0;
	core->getTextureMgr()->getTexture("guy")->loadFrame(f);

	for (int i = 2; i<8;i++)
	{
		f.x = i*24;
		f.y = 0;
		f.w = 24;
		f.h = 72;
		f.tag = "__bad";
		f.x_offset = 0;
		f.y_offset = 0;
		core->getTextureMgr()->getTexture("guy")->loadFrame(f);
	}

	f.x = 192;
	f.y = 0;
	f.w = 24;
	f.h = 72;
	f.tag = "walk_end";
	f.x_offset = 0;
	f.y_offset = 0;
	core->getTextureMgr()->getTexture("guy")->loadFrame(f);

	f.x = 0;
	f.y = 0;
	f.w = 2;
	f.h = 2;
	f.tag = "block";
	f.x_offset = 0;
	f.y_offset = 0;
	core->getTextureMgr()->getTexture("guy")->loadFrame(f);

	Animation a = Animation("walk",2,9,20);
	core->getTextureMgr()->getTexture("guy")->loadAnimation(a);

	f.x = 0;
	f.y = 72;
	f.w = 24;
	f.h = 72;
	f.tag = "left_walk_start";
	f.x_offset = 0;
	f.y_offset = 0;
	core->getTextureMgr()->getTexture("guy")->loadFrame(f);

	for (int i = 1; i<7;i++)
	{
		f.x = i*24;
		f.y = 72;
		f.w = 24;
		f.h = 72;
		f.tag = "__bad";
		f.x_offset = 0;
		f.y_offset = 0;
		core->getTextureMgr()->getTexture("guy")->loadFrame(f);
	}

	f.x = 168;
	f.y = 72;
	f.w = 24;
	f.h = 72;
	f.tag = "left_walk_end";
	f.x_offset = 0;
	f.y_offset = 0;
	core->getTextureMgr()->getTexture("guy")->loadFrame(f);

	a = Animation("left_walk",11,17,20);
	core->getTextureMgr()->getTexture("guy")->loadAnimation(a);

	GeometryDef def;
	def.dynamic = true;
	def.w = 240;
	def.h = 720;
	def.t = "guy";
	def.f = "stand";

	Geometry* g = core->getGeometryMgr()->createGeometry(def);
	Node* n = core->getRootNode()->createChildNode(Position(0,0,0));
	n->attachGeometry(g);
	n->playAnimation("walk",true);
	Node* n2 = n->createChildNode(Position(0,14,0));
	def.dynamic = false;
	def.w = 32;
	def.h = 32;
	def.f = "block";


	Geometry* g2 = core->getGeometryMgr()->createGeometry(def);
	n2->attachGeometry(g2);
	n2->sendToBack();
	bool quit = false;
	bool facingright = true;
	while (!quit)
	{
		if (info->mKeyState[K_ESCAPE] == InputInfo::INPUT_DOWN)
			quit = true;
		
		n2->translate(0,float(NPCore::getPtr()->getTimeSinceLastFrame())*0.04);
		n2->mAlpha -= float(NPCore::getPtr()->getTimeSinceLastFrame())*0.001;
		if (n2->mAlpha <= 0)
		{
			n2->mPosition.y = 14;
			n2->mAlpha = 1.0f;
			n2->sendToBack();
		}
		if (facingright)
		{
			n->translate(float(NPCore::getPtr()->getTimeSinceLastFrame())*0.04,0);
			if (n->mPosition.x > 320)
			{
				facingright = false;
				n->playAnimation("left_walk",true);
			}
		}
		else
		{
			n->translate(-float(NPCore::getPtr()->getTimeSinceLastFrame())*0.04,0);
			if (n->mPosition.x < -320)
			{
				facingright = true;
				n->playAnimation("walk",true);
			}
		}
		core->processOneFrame();
	}

	core->shutdown();
	return 0;
}