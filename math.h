#pragma once

#include "vmatrix.h"

#define PI 3.14159265358979323846f
#define M_RADPI		57.295779513082
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )
#define square( x ) ( x * x )
#define FastSqrt(x)	(sqrt)(x)

namespace Math
{
	float sseSqrt(float x);

	int RandomIntRange(int min, int max);

	void vectorAngles(Vector forward, Vector &angles);

	float DotProduct(const float *v1, const float *v2);

	VOID VectorTransform(const Vector in1, const matrix3x4& in2, Vector& out);

	FORCEINLINE void VectorSubtract(const Vector& a, const Vector& b, Vector& c);

	float GetFov(Vector vLocalOrigin, Vector vPosition, Vector vForward);

	inline void NormalizeAngle(float & flAngle);

	void CalcAngle(Vector &vSource, Vector &vDestination, Vector &qAngle);

	void angleVectors(Vector angles, Vector &f);

	float AngleNormalize(float angle);

	Vector NormalizeAngle(Vector angles);

	void ClampAngles(Vector& angle);

	void RandomSeed(int iSeed);

	void sinCos(float radians, PFLOAT sine, PFLOAT cosine);

	void angleVectors(Vector angles, Vector & f, Vector & r, Vector & u);

	float RandomFloat(float fMin, float fMax);

	FORCEINLINE void VectorAdd(const Vector& a, const Vector& b, Vector& c)
	{
		c.x = a.x + b.x;
		c.y = a.y + b.y;
		c.z = a.z + b.z;
	}
}

