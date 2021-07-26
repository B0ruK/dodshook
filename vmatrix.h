#pragma once


struct matrix3x4
{
	const float *operator[](int i) const
	{
		return m[i];
	}

	float m[3][4];
};
