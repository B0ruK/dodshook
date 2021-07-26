


class CGlobalVars
{
public:
	float realtime;
	int framecount;
	float absoluteframetime;
	float curtime;
	float frametime;
	int maxclients;
	int tickcount;
	float interval_per_tick;
	float interpolation_amount;
};

class IPlayerInfoManager
{
public:
	CGlobalVars* GetGlobalVars()
	{
		typedef CGlobalVars* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 1)(this);
	}
};