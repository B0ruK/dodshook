
#include "md5hash.h"

inline void GaYnormalize(float &flAngle)
{
	while (flAngle > 180.f)
		flAngle -= 360.f;

	while (flAngle < -180.f)
		flAngle += 360.f;
}

inline void NormalizeAngles(Vector &vecAngles)
{
	for (int iAxis = 0; iAxis < 3; iAxis++)
		GaYnormalize(vecAngles[iAxis]);
}

inline static void CAngleVectors(const Vector &vecAngles, Vector *vecForward, Vector *vecRight, Vector *vecUp)
{
	float flSinPitch, flSinYaw, flSinRoll, flCosPitch, flCosYaw, flCosRoll;

	Math::sinCos(DEG2RAD(vecAngles.x), &flSinPitch, &flCosPitch);
	Math::sinCos(DEG2RAD(vecAngles.y), &flSinYaw, &flCosYaw);
	Math::sinCos(DEG2RAD(vecAngles.z), &flSinRoll, &flCosRoll);

	if (vecForward)
	{
		vecForward->x = flCosPitch * flCosYaw;
		vecForward->y = flCosPitch * flSinYaw;
		vecForward->z = -flSinPitch;
		vecForward->Normalize();
	}

	if (vecRight)
	{
		vecRight->x = -1.f * flSinRoll * flSinPitch * flCosYaw + -1.f * flCosRoll * -flSinYaw;
		vecRight->y = -1.f * flSinRoll * flSinPitch * flSinYaw + -1.f * flCosRoll * flCosYaw;
		vecRight->z = -1.f * flSinRoll * flCosPitch;
		vecRight->Normalize();
	}

	if (vecUp)
	{
		vecUp->x = flCosRoll * flSinPitch * flCosYaw + -flSinRoll * -flSinYaw;
		vecUp->y = flCosRoll * flSinPitch * flSinYaw + -flSinRoll * flCosYaw;
		vecUp->z = flCosRoll * flCosPitch;
		vecUp->Normalize();
	}
}


inline static void VectorAngles(const Vector &vecDirection, Vector &vecAngles)
{
	if (vecDirection.x == 0 && vecDirection.y == 0)
	{
		if (vecDirection.z > 0.f)
			vecAngles.x = 270.f;
		else
			vecAngles.x = 90.f;

		vecAngles.y = 0.f;
	}
	else
	{
		vecAngles.x = RAD2DEG(atan2(-vecDirection.z, sqrtf(vecDirection.x * vecDirection.x + vecDirection.y * vecDirection.y)));
		vecAngles.y = RAD2DEG(atan2(vecDirection.y, vecDirection.x));

		if (vecAngles.x < 0.f)
			vecAngles.x += 360.f;

		if (vecAngles.y < 0.f)
			vecAngles.y += 360.f;
	}

	vecAngles.z = 0.f;
	NormalizeAngles(vecAngles);
}

inline void NoSpread(CUserCmd* cmd, CBaseCombatWeapon* w, Vector &ref)
{
	CBaseEntity *local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());

	if (!local)
		return;

	cmd->random_seed = MD5_PseudoRandom(cmd->command_number) & 255;

	Vector shake = Vector();

	float(__thiscall* GetBulletSpread)(void*, float) = getvfunc<float(__thiscall*)(void*, float)>(w, 373);
	float f = GetBulletSpread(w, local->GetVelocity().Length2D());

	shake.x = f;
	shake.y = f;

	if (cmd->random_seed == 39)
		cmd->random_seed += 2;

	Math::RandomSeed(cmd->random_seed);

	float x = Math::RandomFloat(-0.5f, 0.5f) + Math::RandomFloat(-0.5f, 0.5f);
	float y = Math::RandomFloat(-0.5f, 0.5f) + Math::RandomFloat(-0.5f, 0.5f);

	Vector forward, right, up;

	NormalizeAngles(cmd->viewangles);
	CAngleVectors(cmd->viewangles, &forward, &right, &up);

	Vector new_va = forward + (right * shake.x * x * -1.0f) + (up * shake.y * y * -1.0f);
	new_va.NormalizeInPlace();

	VectorAngles(new_va, ref);
	NormalizeAngles(ref);
}