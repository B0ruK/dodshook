#pragma once

#include <ShlObj.h>
#include <sstream>

namespace CfgSystem
{
	void LoadCfg();
	void SaveCFG();
}

class CGlobalVariables
{
public:
	float SMOOTHYAW;
	float SMOOTHPITCH;
	float ENABLEAIM;
	float AIMONFIRE;
	float HITBOX;
	float AIMFOV;
	float NORECOIL;
	float NOSPREAD;
	float AUTOFIRE;
	float SILENTAIM;
	float ESPBOX;
	float ESPTEAM;
	float ESPHEALTH;
	float CHAMS;
	float CHAMSXQZ;
	float CHAMSTEAM;
	float flRadarPos_x = 120;
	float flRadarPos_y = 120;
	float radar;
	float watermark;
	float velocity;
	float triggerkey;
	float trigenable;
	float trighead;
	float triggerbody;
	float trigerdelay;
	float TRIGLIMB;
	float LAGKEY;
	float LAGFAST;
	float AUTOPISTOL;
	float airstuck;
	float airstuckkey;
	float espcolorone = 254;
	float espcolortwo;
	float espcolorthird;
	float viewmodel;
	float viewfov;


	bool bMenu = false;
};

extern CGlobalVariables gCvars;
