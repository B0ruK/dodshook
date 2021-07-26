


class CESP
{
public:
	void draw(CBaseEntity* local);
	void drawradar(int screenwidght, int screenheight, CBaseEntity* local);
	void DrawRadarBack(int screenwidght, int screenheight);
	void DrawRadarPoint(Vector vecOriginx, Vector vecOriginy, Vector vAngle);
	void drawvelocity(int screenWidth, int screenHeight, CBaseEntity* local_player);
	void DrawBox(const RECT& rect);
	void DrawHealth(const RECT & rect, CBaseEntity * player);
	void DrawPlayer(CBaseEntity * pEntity,int iMyTeam);

	matrix3x4 matrix[128];
};

extern CESP g_ESP;

