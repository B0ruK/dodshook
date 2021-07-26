#pragma once

struct ModelRenderInfo
{
	char pad[48];
	int entity_index;
};

enum MaterialVarFlag
{
	NO_DRAW = (1 << 2),
	ZNEARER = (1 << 10),
	NOCULL = (1 << 13),
	NOFOG = (1 << 14),
	IGNOREZ = (1 << 15),
	HALFLAMBERT = (1 << 27),
};

class IMaterial
{
public:
	void SetMaterialVarFlag(MaterialVarFlag flag, bool on)
	{
		typedef void(__thiscall* SetMaterialVarFlagFn)(void*, MaterialVarFlag, bool);
		getvfunc<SetMaterialVarFlagFn>(this, 29)(this, flag, on);
	}
};

class IMaterialSystem
{
public:
	IMaterial *FindMaterial(char const* pMaterialName, const char *pTextureGroupName, bool complain = true, const char *pComplainPrefix = NULL)
	{
		typedef IMaterial*(__thiscall* OriginalFn)(PVOID, char const*, const char*, bool, const char*);
		return getvfunc<OriginalFn>(this, 71)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
	}
};

class IVModelRender
{
public:
	void ForcedMaterialOverride(IMaterial* mat)
	{
		typedef void(__thiscall *OriginalFn)(void*, IMaterial*, int);
		return getvfunc<OriginalFn>(this, 1)(this, mat, 0);
	}
};

class IVRenderView
{
public:
	void SetColorModulation(float const* colors)
	{
		typedef void(__thiscall* oDrawModelExecute)(PVOID, float const*);
		return getvfunc<oDrawModelExecute>(this, 6)(this, colors);
	}
};
