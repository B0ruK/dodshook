

class Aimbut
{
public:
	void Main(CUserCmd* pUserCmd, CBaseEntity* pLocal);

	bool GetHitboxpos(CBaseEntity* pLocal,CBaseEntity* Entitiy, Vector &vPos, int iHitBox);

	bool IsVisible(Vector& vecStart, Vector& vecEnd, CBaseEntity* pLocal, CBaseEntity* target);

	void triggerbot(CUserCmd *cmd, CBaseEntity* local);

	void Reset()
	{
		iTarget = -1;
		fBestTarget = 99999.9f;
		vTarget.Zero();
		vFinal.Zero();
	}

	bool HasTarget()
	{
		return (iTarget != -1);
	}

	matrix3x4 matrix[128];

	Vector vMax;
	Vector vMin;

	int iTarget;

	float fBestTarget;

	Vector vTarget;

	Vector vFinal;

	Vector vEyePos;
};

extern Aimbut g_aimbot;