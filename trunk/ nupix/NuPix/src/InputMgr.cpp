#include "InputMgr.h"

using namespace newPix;

InputMgr::InputMgr()
{

}

InputMgr::~InputMgr()
{
	printf("  -InputMgr... ");

	if (mInputInfo)
		delete mInputInfo;

	printf("Done.\n");
}

bool InputMgr::initialise()
{
	printf("  -InputMgr... ");
	mInputInfo = new InputInfo();
	printf("Done.\n");
	return true;
}

void InputMgr::keyPressed(SDLKey key)
{
	mInputInfo->mKeyState[key] = InputInfo::INPUT_PRESSED;
	mKeyBuffer.push_back(key);
}

void InputMgr::keyReleased(SDLKey key)
{
	mInputInfo->mKeyState[key] = InputInfo::INPUT_RELEASED;
	mKeyBuffer.push_back(key);
}

void InputMgr::mousePressed(uint16 id)
{
	mInputInfo->mMouseState[id] = InputInfo::INPUT_PRESSED;
	mMouseBuffer.push_back(id);
}

void InputMgr::mouseReleased(uint16 id)
{
	mInputInfo->mMouseState[id] = InputInfo::INPUT_RELEASED;
	mMouseBuffer.push_back(id);
}

void InputMgr::mouseMoved(SDL_MouseMotionEvent evt)
{
	mInputInfo->mX = evt.x;
	mInputInfo->mY = evt.y;
	mInputInfo->mXRel = evt.xrel;
	mInputInfo->mYRel = evt.yrel;
}

void InputMgr::processBuffers()
{
	std::vector<uint16>::iterator it = mKeyBuffer.begin();
	while (it != mKeyBuffer.end())
	{
		uint16 key = (*it);
		if (mInputInfo->mKeyState[key] == InputInfo::INPUT_PRESSED)
			mInputInfo->mKeyState[key] = InputInfo::INPUT_DOWN;

		if (mInputInfo->mKeyState[key] == InputInfo::INPUT_RELEASED)
			mInputInfo->mKeyState[key] = InputInfo::INPUT_UP;

		it++;
	}

	it = mMouseBuffer.begin();
	while (it != mMouseBuffer.end())
	{
		uint16 id = (*it);
		if (mInputInfo->mMouseState[id] == InputInfo::INPUT_PRESSED)
			mInputInfo->mMouseState[id] = InputInfo::INPUT_DOWN;

		if (mInputInfo->mMouseState[id] == InputInfo::INPUT_RELEASED)
			mInputInfo->mMouseState[id] = InputInfo::INPUT_UP;

		it++;
	}

	mKeyBuffer.clear();
	mMouseBuffer.clear();
	mInputInfo->mXRel = 0;
	mInputInfo->mYRel = 0;
}

InputInfo* InputMgr::getInputInfo()
{
	return mInputInfo;
}