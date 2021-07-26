#include "include.h"


float Math::DotProduct(const float *v1, const float *v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

auto Math::RandomFloat(float min, float max) -> float
{
	static auto oRandomFloat = reinterpret_cast<float(*)(float, float)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomFloat"));
	return oRandomFloat(min, max);
}

void Math::RandomSeed(int iSeed)
{
	static auto oRandomSeed = reinterpret_cast<void(*)(std::uint32_t)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed"));
	oRandomSeed(iSeed);
}

void Math::sinCos(float radians, PFLOAT sine, PFLOAT cosine)
{
	__asm
	{
		fld dword ptr[radians]
		fsincos
		mov edx, dword ptr[cosine]
		mov eax, dword ptr[sine]
		fstp dword ptr[edx]
		fstp dword ptr[eax]
	}
}

void Math::angleVectors(Vector angles, Vector &f, Vector &r, Vector &u)
{
	float sp, sy, sr, cp, cy, cr;

	sinCos(DEG2RAD(angles[0]), &sp, &cp);
	sinCos(DEG2RAD(angles[1]), &sy, &cy);
	sinCos(DEG2RAD(angles[2]), &sr, &cr);

	f[0] = cp * cy;
	f[1] = cp * sy;
	f[2] = -sp;

	r[0] = -1.0f * sr * sp * cy + -1.0f * cr * -sy;
	r[1] = -1.0f * sr * sp * sy + -1.0f * cr * cy;
	r[2] = -1.0f * sr * cp;

	u[0] = cr * sp * cy + -sr * -sy;
	u[1] = cr * sp * sy + -sr * cy;
	u[2] = cr * cp;
}

int Math::RandomIntRange(int min, int max)
{
	static bool first = true;

	if (first)
	{
		srand(GetTickCount());
		first = false;
	}

	return min + rand() % (max - min);
}

VOID Math::VectorTransform(const Vector in1, const matrix3x4& in2, Vector& out)
{
	float buf[3];
	buf[0] = in1.x;
	buf[1] = in1.y;
	buf[2] = in1.z;

	out[0] = DotProduct(buf, in2[0]) + in2[0][3];
	out[1] = DotProduct(buf, in2[1]) + in2[1][3];
	out[2] = DotProduct(buf, in2[2]) + in2[2][3];
}

FORCEINLINE void Math::VectorSubtract(const Vector& a, const Vector& b, Vector& c)
{
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

float Math::sseSqrt(float x)
{
	float root = 0.0f;

	__asm
	{
		sqrtss xmm0, x
		movss root, xmm0
	}

	return root;
}

void Math::vectorAngles(Vector forward, Vector &angles)
{
	if (forward[1] == 0.0f && forward[0] == 0.0f)
	{
		angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f;
		angles[1] = 0.0f;
	}
	else
	{
		float len2d = sseSqrt(square(forward[0]) + square(forward[1]));

		angles[0] = RAD2DEG(atan2f(-forward[2], len2d));
		angles[1] = RAD2DEG(atan2f(forward[1], forward[0]));

		if (angles[0] < 0.0f) angles[0] += 360.0f;
		if (angles[1] < 0.0f) angles[1] += 360.0f;
	}

	angles[2] = 0.0f;
}

float Math::GetFov(Vector vLocalOrigin, Vector vPosition, Vector vForward)
{
	Vector vLocal;

	Math::VectorSubtract(vPosition, vLocalOrigin, vLocal);

	vLocal.NormalizeInPlace();

	float fValue = vForward.Dot(vLocal);

	if (fValue < -1.0f)
		fValue = -1.0f;

	if (fValue > 1.0f)
		fValue = 1.0f;

	return RAD2DEG(acos(fValue));
}

inline void Math::NormalizeAngle(float &flAngle)
{
	while (flAngle > 180.f)
		flAngle -= 360.f;

	while (flAngle < -180.f)
		flAngle += 360.f;
}

void Math::ClampAngles(Vector& angle)
{
	if (angle.y > 180.0f)
		angle.y = 180.0f;
	else if (angle.y < -180.0f)
		angle.y = -180.0f;

	if (angle.x > 89.0f)
		angle.x = 89.0f;
	else if (angle.x < -89.0f)
		angle.x = -89.0f;

	angle.z = 0;
}

void Math::CalcAngle(Vector &vSource, Vector &vDestination, Vector &qAngle)
{
	Vector vDelta = vSource - vDestination;

	float fHyp = (vDelta.x * vDelta.x) + (vDelta.y * vDelta.y);

	float fRoot;

	__asm
	{
		sqrtss xmm0, fHyp
		movss fRoot, xmm0
	}

	qAngle.x = RAD2DEG(atan(vDelta.z / fRoot));
	qAngle.y = RAD2DEG(atan(vDelta.y / vDelta.x));

	if (vDelta.x >= 0.0f)
		qAngle.y += 180.0f;

	qAngle.x = AngleNormalize(qAngle.x);
	qAngle.y = AngleNormalize(qAngle.y);
}

void Math::angleVectors(Vector angles, Vector &f)
{
	float sp, sy, sr, cp, cy, cr;

	sinCos(DEG2RAD(angles[0]), &sp, &cp);
	sinCos(DEG2RAD(angles[1]), &sy, &cy);
	sinCos(DEG2RAD(angles[2]), &sr, &cr);

	f[0] = cp * cy;
	f[1] = cp * sy;
	f[2] = -sp;
}

float Math::AngleNormalize(float angle)
{
	while (angle < -180)    angle += 360;
	while (angle > 180)    angle -= 360;

	return angle;
}

Vector Math::NormalizeAngle(Vector angles)
{
	if (angles.x > 89)
	{
		angles.x = 89;
	}
	else if (-89 > angles.x)
	{
		angles.x = -89;
	}

	if (angles.y > 180)
	{
		angles.y -= 360;
	}
	else if (-180 > angles.y)
	{
		angles.y += 360;
	}

	angles.z = 0;

	return angles;
}