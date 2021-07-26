


class CUserCmd
{
public:
	virtual ~CUserCmd() {};
	int command_number;
	int tick_count;
	Vector viewangles;
	float forwardmove;
	float sidemove;
	float upmove;
	int	buttons;
	byte impulse;
	int weaponselect;
	int weaponsubtype;
	int random_seed;
};


