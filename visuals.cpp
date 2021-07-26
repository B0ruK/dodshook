#include "include.h"

CESP g_ESP;

#define COLORESP (gCvars.espcolorone), (gCvars.espcolortwo), (gCvars.espcolorthird), 255

void CESP::drawvelocity(int screenWidth, int screenHeight, CBaseEntity* local_player)
{
	Vector speed = local_player->GetVelocity();

	int intspeed = round(speed.Length2D());

	Draw::DrawStringA(Fonts::m_VelocityFont, true, screenWidth / 2, screenHeight - 100, COLORESP, "%0i", intspeed);
}

void CESP::DrawBox(const RECT& rect)
{
	pSurface->DrawSetColor(COLORESP);
	pSurface->DrawOutlinedRect(rect.left, rect.top, rect.right, rect.bottom);
	pSurface->DrawSetColor(0, 0, 0, 255);
	pSurface->DrawOutlinedRect(rect.left - 1, rect.top - 1, rect.right + 1, rect.bottom + 1);
	pSurface->DrawOutlinedRect(rect.left + 1, rect.top + 1, rect.right - 1, rect.bottom - 1);
}

void CESP::DrawHealth(const RECT& rect, CBaseEntity* player)
{
	int hp = player->GetHealth();

	if (hp > 100)
		hp = 100;

	float box_h = (float)fabs(rect.bottom - rect.top);

	float off = 6;

	auto height = (((box_h * hp) / 100));

	int x = rect.left - off;
	int y = rect.top;
	int w = 4;
	int h = box_h;

	pSurface->DrawSetColor(0, 0, 0, 255);
	pSurface->DrawFilledRect(x, y, x + w, y + h);
	pSurface->DrawSetColor(0, 255, 0, 255);
	pSurface->DrawFilledRect(x + 1, y + 1, x + w - 1, y + height - 2);
}

void CESP::drawradar(int screenwidght, int screenhight, CBaseEntity* local)
{
	int iMyTeam = local->GetTeamNum();

	for (int ax = 1; ax <= pEngine->GetMaxClients(); ax++)
	{
		CBaseEntity* entity = pEntList->GetClientEntity(ax);

		if (!entity)
			continue;

		if (entity == local)
			continue;

		if (!entity->GetModel())
			continue;

		if (entity->IsDormant())
			continue;

		if (!entity->IsAlive())
			continue;

		int iTeamNum = entity->GetTeamNum();

		if (iTeamNum == iMyTeam)
			continue;

		static Vector vClientViewAngles;

		pEngine->GetViewAngles(vClientViewAngles);

		DrawRadarPoint(entity->GetAbsOrigin(), local->GetAbsOrigin(), vClientViewAngles);
	}
}

void CESP::draw(CBaseEntity* local)
{
	int iMyTeam = local->GetTeamNum();

	for (int ax = 1; ax <= pEngine->GetMaxClients(); ax++)
	{
		CBaseEntity* entity = pEntList->GetClientEntity(ax);

		if (!entity)
			continue;

		if (entity == local)
			continue;

		if (!entity->GetModel())
			continue;

		if (entity->IsDormant())
			continue;

		if (!entity->IsAlive())
			continue;

		if (!entity->SetupBones(matrix))
			continue;

		DrawPlayer(entity,iMyTeam);
	}
}

void CESP::DrawPlayer(CBaseEntity * entity,int iMyTeam)
{
	Vector Origin3D = entity->GetAbsOrigin();
	Vector Origin;

	if (Origin3D.IsZero())
		return;

	if (!Draw::WorldToScreen(Origin3D, Origin))
		return;

	Vector Head3D = entity->GetBonePos(13);
	Head3D.z += 15.0f;
	Vector Head;

	if (Head3D.IsZero())
		return;

	if (!Draw::WorldToScreen(Head3D, Head))
		return;

	float h = fabs(Head.y - Origin.y);
	float w = h / 1.65f;

	RECT rect =
	{
		static_cast<long>(Origin.x - w * 0.5f),
		static_cast<long>(Head.y),
		static_cast<long>(w),
		static_cast<long>(Origin.y)
	};

	rect.right += static_cast<long>(rect.left);

	int iTeamNum = entity->GetTeamNum();

	int middle = ((rect.right - rect.left) / 2) + rect.left;

	int inthealf = entity->GetHealth();

	if (iTeamNum == iMyTeam && gCvars.ESPTEAM)
	{
		if (gCvars.ESPBOX)
		{
			DrawBox(rect);
		}

		if (gCvars.ESPHEALTH)
		{
			DrawHealth(rect, entity);
		}
	}

	if (iTeamNum != iMyTeam)
	{
		if (gCvars.ESPBOX)
		{
			DrawBox(rect);
		}

		if (gCvars.ESPHEALTH)
		{
			DrawHealth(rect, entity);
		}
	}
}

void CESP::DrawRadarBack(int screenwidght, int screenhight)
{
	int size = 100;

	if (g_Mouse.LeftClick(gCvars.flRadarPos_x - (size / 2) - 6, gCvars.flRadarPos_y - (size / 2) - 6, size * 2 + 12, size * 2 + 12))
	{
		gCvars.flRadarPos_x = g_Mouse.mouse_x;
		gCvars.flRadarPos_y = g_Mouse.mouse_y;
		gCvars.flRadarPos_x = gCvars.flRadarPos_x;
		gCvars.flRadarPos_y = gCvars.flRadarPos_y;
	}

	int centerx = gCvars.flRadarPos_x + (size / 2);
	int centery = gCvars.flRadarPos_y + (size / 2);

	Draw::FillRGBA(centerx - size - 6, centery - size - 20, 2 * size + 12, 2 * size + 26, 35, 35, 35, 255);
	Draw::OutlinedRectangle(centerx - size - 6, centery - size - 20, 2 * size + 12, 2 * size + 26, 0, 0, 0, 254);

	Draw::DrawStringA(Fonts::m_MenuFont,false, centerx - size, centery - size - 19, 255, 255, 255, 255,"Radar");
	Draw::FillRGBA(centerx - size, centery - size, 2 * size, 2 * size, 50, 50, 50, 255);

	Draw::OutlinedRectangle(centerx - size, centery - size, 2 * size, 2 * size,0,0,0,254);
	Draw::FillRGBA(centerx, centery - size, 1, 2 * size, 0, 0, 0, 120);
	Draw::FillRGBA(centerx - size, centery, 2 * size, 1, 0, 0, 0, 120);
}

void CESP::DrawRadarPoint(Vector vecOriginx, Vector vecOriginy, Vector vAngle)
{
	int size = 100;

	size -= 5;

	int centerx = gCvars.flRadarPos_x + (size / 2);
	int centery = gCvars.flRadarPos_y + (size / 2);

	float dx = vecOriginx.x - vecOriginy.x;
	float dy = vecOriginx.y - vecOriginy.y;

	float flAngle = vAngle.y;
	float yaw = (flAngle)* (PI / 180.0);

	float mainViewAngles_CosYaw = cos(yaw);
	float mainViewAngles_SinYaw = sin(yaw);

	float x = dy * (-mainViewAngles_CosYaw) + dx * mainViewAngles_SinYaw;
	float y = dx * (-mainViewAngles_CosYaw) - dy * mainViewAngles_SinYaw;

	float range = size * 30;

	if (fabs(x) > range || fabs(y) > range)
	{
		if (y > x)
		{
			if (y > -x) {
				x = range * x / y;
				y = range;
			}
			else {
				y = -range * y / x;
				x = -range;
			}
		}
		else {
			if (y > -x) {
				y = range * y / x;
				x = range;
			}
			else {
				x = -range * x / y;
				y = -range;
			}
		}
	}

	int ScreenX = centerx + int(x / range * float(size));

	int ScreenY = centery + int(y / range * float(size));

	size -= 10;

	int radar_menu_x = centerx;

	int radar_menu_y = centery;

	if (ScreenX < radar_menu_x - size)
	{
		ScreenX = radar_menu_x - size + 1;
	}
	else if (ScreenX > radar_menu_x + size)
	{
		ScreenX = radar_menu_x + size - 3;
	}

	if (ScreenY < radar_menu_y - size)
	{
		ScreenY = radar_menu_y - size + 2;
	}
	else if (ScreenY > radar_menu_y + size)
	{
		ScreenY = radar_menu_y + size - 4;
	}

	Draw::FillRGBA(ScreenX - 1, ScreenY - 1, 4, 4, 255,255,255,255);
}