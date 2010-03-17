#pragma once

class InputInfo
{
public:
	enum InputState
	{
		INPUT_PRESSED,
		INPUT_DOWN,
		INPUT_RELEASED,
		INPUT_UP,
	};
	
	InputInfo() :
		mX(0),
		mY(0),
		mZ(0),
		mXRel(0),
		mYRel(0),
		mZRel(0)
	{
		for (int i=0;i<350;i++)
			mKeyState[i] = INPUT_UP;

		for (int i=0;i<10;i++)
			mMouseState[i] = INPUT_UP;
	}

	~InputInfo()
	{

	}

	uint16	mX,
			mY,
			mZ;
	int		mXRel,
			mYRel,
			mZRel;

	InputState	mMouseState[10],
				mKeyState[350];

};