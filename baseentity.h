
#include "netvars.h"

enum mFlags
{
	FL_ONGROUND = (1 << 0),
	IN_ATTACK = (1 << 0),
	IN_ATTACK2 = (1 << 11),
	IN_DUCK = (1 << 2),
	IN_JUMP = (1 << 1),
	IN_USE = (1 << 5),
	IN_FORWARD = (1 << 3),
	IN_BACK = (1 << 4),
	IN_MOVELEFT = (1 << 9),
	IN_MOVERIGHT = (1 << 10),
};

enum TeamIndexes
{
	TEAM_TT = 2,
	TEAM_CT = 3
};

#define pRenderables 0x4
#define pNetworkables 0x8

struct CBaseEntity
{
	ClientClass* GetClientClass()
	{
		PVOID pNetworkable = (PVOID)(this + pNetworkables);
		typedef ClientClass* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pNetworkable, 2)(pNetworkable);
	}

	const Vector& GetAbsOrigin()
	{
		typedef const Vector& (__thiscall *GetAbsOrg_t)(PVOID);
		return getvfunc<GetAbsOrg_t>(this, 9)(this);
	}

	bool IsDormant()
	{
		PVOID pNetworkable = (PVOID)(this + pNetworkables);
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pNetworkable, 8)(pNetworkable);
	}

	DWORD* GetModel()
	{
		PVOID pRenderable = (PVOID)(this + pRenderables);
		typedef DWORD* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pRenderable, 9)(pRenderable);
	}

	bool SetupBones(void* mtx)
	{
		PVOID pRenderable = (PVOID)(this + pRenderables);
		typedef bool(__thiscall* OriginalFn)(PVOID, void*, int, long, float);
		return getvfunc<OriginalFn>(pRenderable, 16)(pRenderable, mtx, 128, 0x100, 0);
	}

	int GetIndex()
	{
		PVOID pNetworkable = (PVOID)(this + pNetworkables);
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pNetworkable, 9)(pNetworkable);
	}

	float m_flSimulationTime()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseEntity", "m_flSimulationTime");
		return *(float*)((uintptr_t)this + iOffset);
	}

	Vector GetVecOrigin()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseEntity", "m_vecOrigin");
		return *(Vector*)((uintptr_t)this + iOffset);
	}

	int GetHitboxSet()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseAnimating", "m_nHitboxSet");
		return *(int*)((DWORD)this + iOffset);
	}

	int GetHealth()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BasePlayer", "m_iHealth");
		return *(int*)((uintptr_t)this + iOffset);
	}

	unsigned char GetLifeState()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BasePlayer", "m_lifeState");
		return *(unsigned char*)((uintptr_t)this + iOffset);
	}

	int GetTeamNum()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseEntity", "m_iTeamNum");
		return *(int*)((uintptr_t)this + iOffset);
	}

	int GetFlags()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BasePlayer", "m_fFlags");
		return *(int*)((uintptr_t)this + iOffset);
	}

	Vector GetVecViewOffset()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BasePlayer", "m_vecViewOffset[0]");
		return *(Vector*)((uintptr_t)this + iOffset);
	}

	Vector GetEyePosition()
	{
		return GetVecOrigin() + GetVecViewOffset();
	}

	Vector GetVelocity()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BasePlayer", "m_vecVelocity[0]");
		return *(Vector*)((uintptr_t)this + iOffset);
	}

	HANDLE GetActiveWeaponHandle()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseCombatCharacter", "m_hActiveWeapon");
		return *(HANDLE*)((uintptr_t)this + iOffset);
	}

	int GetTickBase()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BasePlayer", "m_nTickBase");
		return *(int*)((uintptr_t)this + iOffset);
	}

	bool IsAlive()
	{
		return (GetLifeState() == 0 && GetHealth() > 0);
	}

	inline Vector GetBonePos(int boneIndex)
	{
		matrix3x4 BoneMatrix[128];

		if (!this->SetupBones(BoneMatrix))
			return this->GetVecOrigin();

		matrix3x4 hitbox = BoneMatrix[boneIndex];

		return Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
	}
};

struct CBaseCombatWeapon
{
	float GetNextPrimaryAttack()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
		return *(float*)((uintptr_t)this + iOffset);
	}

	bool HasAmmo()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseCombatWeapon", "m_iClip1");
		return ((*(PINT)((DWORD)this + iOffset)) > 0);
	}
};
