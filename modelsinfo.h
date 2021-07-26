#pragma once


struct mstudiobbox
{
	int         bone;
	int         group;
	Vector		bbmin;
	Vector		bbmax;
	int         szhitboxnameindex;
	int         unused[8];
};

struct mstudiohitboxset
{
	int                   sznameindex;
	inline char* const    pszName(void) const { return ((char*)this) + sznameindex; }
	int                   numhitboxes;
	int                   hitboxindex;
	inline mstudiobbox*   pHitbox(int i) const { return (mstudiobbox*)(((BYTE*)this) + hitboxindex) + i; };
};

struct studiohdr
{
	unsigned char     pad[0xAC];
	int               numhitboxsets;
	int               hitboxsetindex;

	mstudiohitboxset* pHitboxSet(int i) const
	{
		return (mstudiohitboxset*)(((BYTE*)this) + hitboxsetindex) + i;
	};
};

class CModelInfo
{
public:
	studiohdr* GetStudiomodel(const DWORD *mod)
	{
		typedef studiohdr* (__thiscall* GetStudiomodelFn)(void*, const DWORD*);
		return getvfunc< GetStudiomodelFn >(this, 28)(this, mod);
	}
};