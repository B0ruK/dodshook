

class INetChannel
{
private:
	__forceinline float GetLatency(int flow)
	{
		return getvfunc< float(__thiscall*)(decltype(this), int) >(this, 9)(this, flow);
	}
};

class CEngineClient
{
public:
	void GetScreenSize(int& width, int& height)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int&, int&);
		return getvfunc<OriginalFn>(this, 5)(this, width, height);
	}

	int GetLocalPlayer(VOID)
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 12)(this);
	}

	void GetViewAngles(Vector& vAngles)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, Vector&);
		return getvfunc< OriginalFn >(this, 19)(this, vAngles);
	}

	void SetViewAngles(Vector& vAngles)
	{
		typedef void(__thiscall* oSetViewAngles)(PVOID, Vector&);
		return getvfunc< oSetViewAngles >(this, 20)(this, vAngles);
	}

	int GetMaxClients()
	{
		typedef bool(__thiscall* oGetMaxClients)(PVOID);
		return getvfunc< oGetMaxClients >(this, 21)(this);
	}

	bool IsInGame()
	{
		typedef bool(__thiscall* oLocal)(PVOID);
		return getvfunc< oLocal >(this, 26)(this);
	}

	const matrix3x4& WorldToScreen()
	{
		typedef const matrix3x4& (__thiscall* oWorldToScreenMatrix)(PVOID);
		return getvfunc< oWorldToScreenMatrix >(this, 36)(this);
	}

	INetChannel* GetNetChannelInfo(void)
	{
		typedef INetChannel* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 72)(this);
	}
};

class CEntityList
{
public:
	CBaseEntity* GetClientEntity(int entnum)
	{
		typedef CBaseEntity* (__thiscall* OriginalFn)(PVOID, int);
		return getvfunc<OriginalFn>(this, 3)(this, entnum);
	}
	CBaseEntity *GetClientEntityFromHandle(HANDLE hEnt)
	{
		typedef CBaseEntity* (__thiscall* OriginalFn)(PVOID, HANDLE);
		return getvfunc<OriginalFn>(this, 4)(this, hEnt);
	}
};

class HLCLient
{
public:
	ClientClass* GetAllClasses(VOID)
	{
		typedef ClientClass* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 8)(this);
	}
};
