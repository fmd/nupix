#pragma once

namespace newPix
{
	class Position
		{
		public:
			__declspec(dllexport) Position(float _x = 0.0f, float _y = 0.0f, float _r = 0.0f):
				x(_x),
				y(_y),
				r(_r)
			{}
			__declspec(dllexport) ~Position()
			{}

			float	x,
					y,
					r;
		};

		enum TransformSpace
		{
			TS_LOCAL = 0,
			TS_WORLD = 1,
			TS_SELF	 = 2,
			//TS_SELF is only used in translate(). It translates with the Y axis parallel to its own rotation.
		};
}