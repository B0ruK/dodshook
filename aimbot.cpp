#include "include.h"

Aimbut g_aimbot;

bool shoot;
static int custom_delay = 0;

bool Aimbut::IsVisible(Vector& vecStart, Vector& vecEnd, CBaseEntity* pLocal, CBaseEntity* target)
{
	if (!pLocal || !target)
		return false;

	raytrace rayfag;

	rayfag.Init(vecStart, vecEnd);

	traceclass tr;
	tracefitlers Skip = pLocal;

	pEngineTrace->TraceRay(rayfag,0x46004003, &Skip, &tr);

	if (tr.entity == target || tr.fraction == 1.f)
		return true;

	return false;
}

void Aimbut::triggerbot(CUserCmd *cmd, CBaseEntity* local)
{
	Vector ViewAngles = cmd->viewangles;

	Vector CrosshairForward;
	Math::angleVectors(ViewAngles,CrosshairForward);

	CrosshairForward *= 8192.0f;

	Vector TraceSource = local->GetEyePosition();
	Vector TraceDestination = TraceSource + CrosshairForward;

	raytrace raygay;

	raygay.Init(TraceSource, TraceDestination);

	traceclass Trace;
	tracefitlers Skip = local;

	pEngineTrace->TraceRay(raygay,0x46004003,&Skip, &Trace);

	if (!Trace.entity)
		return;

	if (!Trace.entity->IsAlive())
		return;

	if (Trace.entity->GetTeamNum() == TEAM_TT || Trace.entity->GetTeamNum() == TEAM_CT)
	{
		if (local->GetTeamNum() == Trace.entity->GetTeamNum())
			return;

		bool didHit = false;

		if ((gCvars.trighead && Trace.hitgroup == mhitgrp::Head)
			|| (gCvars.triggerbody && Trace.hitgroup == mhitgrp::Chest)
			|| (gCvars.triggerbody && Trace.hitgroup == mhitgrp::Stomach)
			|| (gCvars.TRIGLIMB && Trace.hitgroup == mhitgrp::LeftArm)
			|| (gCvars.TRIGLIMB && Trace.hitgroup == mhitgrp::RightArm)
			|| (gCvars.TRIGLIMB && Trace.hitgroup == mhitgrp::LeftLeg)
			|| (gCvars.TRIGLIMB && Trace.hitgroup == mhitgrp::RightLeg))
		{
			didHit = true;
		}

		if (gCvars.trigerdelay >= 1)
		{
			if (custom_delay >= gCvars.trigerdelay / 30)
			{
				if (didHit)
				{
					custom_delay = 0;
					shoot = true;
					cmd->buttons |= IN_ATTACK;
				}
			}
			else
			{
				custom_delay++;
			}
		}
	}
	else
		return;
}

bool Aimbut::GetHitboxpos(CBaseEntity* pLocal,CBaseEntity* Entitiy, Vector &vPos, int iHitBox)
{
	if (!pLocal || !Entitiy)
		return false;

	if (!Entitiy->SetupBones(matrix))
		return false;

	const DWORD *model = Entitiy->GetModel();

	if (!model)
		return false;

	studiohdr* hdr = pModel->GetStudiomodel(Entitiy->GetModel());

	if (!hdr)
		return false;

	mstudiohitboxset *set = hdr->pHitboxSet(Entitiy->GetHitboxSet());

	if (!set)
		return false;

	mstudiobbox *hitbox = set->pHitbox(iHitBox);

	if (!hitbox)
		return false;

	Math::VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
	Math::VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);

	if (vMin.IsZero() || vMax.IsZero())
		return false;

	vPos = (vMin + vMax) * 0.5;

	if(IsVisible(vEyePos,vPos,pLocal,Entitiy))
		return true;

	return false;
}

void Aimbut::Main(CUserCmd* pUserCmd, CBaseEntity* pLocal)
{
	int iMyTeam = pLocal->GetTeamNum();

	vEyePos = pLocal->GetEyePosition();

	static Vector vClientViewAngles;
	pEngine->GetViewAngles(vClientViewAngles);

	static Vector vAngle;
	Math::angleVectors(vClientViewAngles,vAngle);

	Reset();

	for (INT ax = 1; ax <= pEngine->GetMaxClients(); ax++)
	{
		CBaseEntity* entity = pEntList->GetClientEntity(ax);

		if (!entity)
			continue;

		if (entity == pLocal)
			continue;

		if (!entity->GetModel())
			continue;

		if (!entity->IsAlive())
			continue;

		if (entity->IsDormant())
			continue;

		if (entity->GetTeamNum() == iMyTeam)
			continue;

		if (!entity->SetupBones(matrix))
			continue;

		if (!GetHitboxpos(pLocal,entity, vTarget,gCvars.HITBOX))
			continue;

		float fCurrFOV = Math::GetFov(vEyePos,vTarget,vAngle);

		if(fCurrFOV > gCvars.AIMFOV)
			continue;

		fCurrFOV = (Vector(vTarget - vEyePos).Length());

		if(fBestTarget < fCurrFOV)
			continue;

		fBestTarget = fCurrFOV;

		vFinal = vTarget;

		iTarget = ax;
	}

	if(HasTarget())
	{
		Math::CalcAngle(vEyePos,vFinal,pUserCmd->viewangles);

		if (gCvars.SMOOTHPITCH > 0 && gCvars.SMOOTHYAW > 0)
		{
			vClientViewAngles.x = Math::AngleNormalize(vClientViewAngles.x);
			vClientViewAngles.y = Math::AngleNormalize(vClientViewAngles.y);

			Vector qDelta = pUserCmd->viewangles - vClientViewAngles;

			qDelta.x = Math::AngleNormalize(qDelta.x);
			qDelta.y = Math::AngleNormalize(qDelta.y);

			pUserCmd->viewangles.x = vClientViewAngles.x + qDelta.x / (float)gCvars.SMOOTHPITCH;
			pUserCmd->viewangles.y = vClientViewAngles.y + qDelta.y / (float)gCvars.SMOOTHYAW;

			pUserCmd->viewangles.x = Math::AngleNormalize(pUserCmd->viewangles.x);
			pUserCmd->viewangles.y = Math::AngleNormalize(pUserCmd->viewangles.y);
		}

		if (!gCvars.SILENTAIM)
		{
			pEngine->SetViewAngles(pUserCmd->viewangles);
		}

		if (gCvars.AUTOFIRE)
		{
			pUserCmd->buttons |= IN_ATTACK;
		}
	}
}
