#include "variables.h"
#include "iniwriter.h"
#include "inireader.h"

void CfgSystem::LoadCfg()
{
	static char path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		sprintf(szCmd, "\\insodod\\config.ini");

		folder = std::string(path) + "\\insodod\\";
		file = std::string(path) + szCmd;
	}
	CreateDirectoryA(folder.c_str(), NULL);

	CIniReader reader(file.c_str());

	gCvars.SMOOTHYAW = reader.ReadFloat("SMOOTHYAW");
	gCvars.SMOOTHPITCH = reader.ReadFloat("SMOOTHPITCH");
	gCvars.ENABLEAIM = reader.ReadFloat("ENABLEAIM");
	gCvars.AIMONFIRE = reader.ReadFloat("AIMONFIRE");
	gCvars.HITBOX = reader.ReadFloat("HITBOX");
	gCvars.AIMFOV = reader.ReadFloat("AIMFOV");
	gCvars.NORECOIL = reader.ReadFloat("NORECOIL");
	gCvars.NOSPREAD = reader.ReadFloat("NOSPREAD");
	gCvars.AUTOFIRE = reader.ReadFloat("AUTOFIRE");
	gCvars.SILENTAIM = reader.ReadFloat("SILENTAIM");
	gCvars.ESPBOX = reader.ReadFloat("ESPBOX");
	gCvars.ESPTEAM = reader.ReadFloat("ESPTEAM");
	gCvars.ESPHEALTH = reader.ReadFloat("ESPHEALTH");
	gCvars.CHAMS = reader.ReadFloat("CHAMS");
	gCvars.CHAMSXQZ = reader.ReadFloat("CHAMSXQZ");
	gCvars.CHAMSTEAM = reader.ReadFloat("CHAMSTEAM");
	gCvars.flRadarPos_x = reader.ReadFloat("flRadarPos_x");
	gCvars.flRadarPos_y = reader.ReadFloat("flRadarPos_y");
	gCvars.radar = reader.ReadFloat("radar");
	gCvars.watermark = reader.ReadFloat("watermark");
	gCvars.velocity = reader.ReadFloat("velocity");
	gCvars.triggerkey = reader.ReadFloat("triggerkey");
	gCvars.trigenable = reader.ReadFloat("trigenable");
	gCvars.trighead = reader.ReadFloat("trighead");
	gCvars.triggerbody = reader.ReadFloat("triggerbody");
	gCvars.trigerdelay = reader.ReadFloat("trigerdelay");
	gCvars.TRIGLIMB = reader.ReadFloat("TRIGLIMB");
	gCvars.LAGKEY = reader.ReadFloat("LAGKEY");
	gCvars.LAGFAST = reader.ReadFloat("LAGFAST");
	gCvars.AUTOPISTOL = reader.ReadFloat("AUTOPISTOL");
	gCvars.airstuck = reader.ReadFloat("airstuck");
	gCvars.airstuckkey = reader.ReadFloat("airstuckkey");
	gCvars.espcolorone = reader.ReadFloat("espcolorone");
	gCvars.espcolortwo = reader.ReadFloat("espcolortwo");
	gCvars.espcolorthird = reader.ReadFloat("espcolorthird");
	gCvars.viewmodel = reader.ReadFloat("viewmodel");
	gCvars.viewfov = reader.ReadFloat("viewfov");
}


void CfgSystem::SaveCFG()
{
	static char path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		sprintf(szCmd, "\\insodod\\config.ini");

		folder = std::string(path) + "\\insodod\\";
		file = std::string(path) + szCmd;
	}
	CreateDirectoryA(folder.c_str(), NULL);

	CIniWriter writer(file.c_str());

	writer.WriteFloat("SMOOTHYAW", gCvars.SMOOTHYAW);
	writer.WriteFloat("SMOOTHPITCH", gCvars.SMOOTHPITCH);
	writer.WriteFloat("ENABLEAIM", gCvars.ENABLEAIM);
	writer.WriteFloat("AIMONFIRE", gCvars.AIMONFIRE);
	writer.WriteFloat("HITBOX", gCvars.HITBOX);
	writer.WriteFloat("AIMFOV", gCvars.AIMFOV);
	writer.WriteFloat("NORECOIL", gCvars.NORECOIL);
	writer.WriteFloat("NOSPREAD", gCvars.NOSPREAD);
	writer.WriteFloat("AUTOFIRE", gCvars.AUTOFIRE);
	writer.WriteFloat("SILENTAIM", gCvars.SILENTAIM);
	writer.WriteFloat("ESPBOX", gCvars.ESPBOX);
	writer.WriteFloat("ESPTEAM", gCvars.ESPTEAM);
	writer.WriteFloat("ESPHEALTH", gCvars.ESPHEALTH);
	writer.WriteFloat("CHAMS", gCvars.CHAMS);
	writer.WriteFloat("CHAMSXQZ", gCvars.CHAMSXQZ);
	writer.WriteFloat("CHAMSTEAM", gCvars.CHAMSTEAM);
	writer.WriteFloat("flRadarPos_x", gCvars.flRadarPos_x);
	writer.WriteFloat("flRadarPos_y", gCvars.flRadarPos_y);
	writer.WriteFloat("radar", gCvars.radar);
	writer.WriteFloat("watermark", gCvars.watermark);
	writer.WriteFloat("velocity", gCvars.velocity);
	writer.WriteFloat("triggerkey", gCvars.triggerkey);
	writer.WriteFloat("trigenable", gCvars.trigenable);
	writer.WriteFloat("trighead", gCvars.trighead);
	writer.WriteFloat("triggerbody", gCvars.triggerbody);
	writer.WriteFloat("TRIGLIMB", gCvars.TRIGLIMB);
	writer.WriteFloat("LAGKEY", gCvars.LAGKEY);
	writer.WriteFloat("LAGFAST", gCvars.LAGFAST);
	writer.WriteFloat("AUTOPISTOL", gCvars.AUTOPISTOL);
	writer.WriteFloat("airstuck", gCvars.airstuck);
	writer.WriteFloat("airstuckkey", gCvars.airstuckkey);
	writer.WriteFloat("espcolorone", gCvars.espcolorone);
	writer.WriteFloat("espcolortwo", gCvars.espcolortwo);
	writer.WriteFloat("espcolorthird", gCvars.espcolorthird);
	writer.WriteFloat("viewmodel", gCvars.viewmodel);
	writer.WriteFloat("viewfov", gCvars.viewfov);
}

CGlobalVariables gCvars;

