#pragma once

#define MATMUL(a, b, c) 	c[0] = a[0]*b[0]+a[1]*b[3]; \
							c[1] = a[0]*b[1]+a[1]*b[4]; \
							c[2] = a[0]*b[2]+a[1]*b[5]+a[2]; \
							c[3] = a[3]*b[0]+a[4]*b[3]; \
							c[4] = a[3]*b[1]+a[4]*b[4]; \
							c[5] = a[3]*b[2]+a[4]*b[5]+a[5];



#define CORDMUL(c, m, r) 	r[0] = c[0]*m[0]+c[1]*m[1]+m[2]; \
							r[1] = c[0]*m[3]+c[1]*m[4]+m[5];

#define M_PI 3.14159265358979323846
#define _180_OVER_PI 18.237813055620798859898303377751
#define PI_OVER_180 0.01745329251994329576923690768489


namespace newPix
{
	inline void regulateR(float& r)
	{
		if (r < 360 && r >= 0)
			return;
		else if (r >= 360)
		{
			while (r >= 360)
				r -= 360;
			return;
		}
		else if (r < -360)
		{
			while (r < -360)
				r += 360;
		}
		r += 360;
	}

	inline float getAngleFromVector(float x, float y)
	{
		float ret = 0;

		if (y < 0)
			ret += 180;

		if (x != 0 && y != 0)
			ret += atan(x/y)*float(180.0f/M_PI);
		else if (y == 0)
		{
			if (x < 0)
				ret -= 90;
			else if (x > 0)
				ret += 90;
		}

		regulateR(ret);

		return ret;
	}
}