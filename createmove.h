#pragma once

bool gaystuck = false;

void DoStuff(CUserCmd* pUserCmd,CBaseEntity* pLocal)
{
	if (pLocal && pLocal->IsAlive())
	{
		if (pLocal->GetTeamNum() == TEAM_TT || pLocal->GetTeamNum() == TEAM_CT)
		{
			if (gCvars.airstuck)
			{
				if (GetAsyncKeyState(gCvars.airstuckkey) & 1)
					gaystuck = !gaystuck;

				if (gaystuck)
				{
					pUserCmd->tick_count = 16777216;
				}
			}

			if (gCvars.LAGFAST > 0 && GetAsyncKeyState(gCvars.LAGKEY))
			{
				Sequence::RemoveConds(gCvars.LAGFAST);
			}

			CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)pEntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());

			if (pWeapon && pWeapon->HasAmmo())
			{
				Vector qOldAngle = pUserCmd->viewangles;

				if (gCvars.AUTOPISTOL && !gCvars.ENABLEAIM)
				{
					float fCurTime = pGlobalVars->interval_per_tick * (pLocal->GetTickBase() + 1);
					float fNextPrimary = pWeapon->GetNextPrimaryAttack();

					bool bCanFire = true;

					static bool bOldBullet;

					if ((fNextPrimary > fCurTime) || bOldBullet)
						bCanFire = false;

					if (!(fNextPrimary > fCurTime))
						bOldBullet = false;

					if ((pUserCmd->buttons & IN_ATTACK))
					{
						if (bCanFire)
							bOldBullet = true;
						else
						{
							pUserCmd->buttons &= ~IN_ATTACK;
						}
					}
				}

				if (gCvars.ENABLEAIM)
				{
					float fCurTime = pGlobalVars->interval_per_tick * (pLocal->GetTickBase() + 1);
					float fNextPrimary = pWeapon->GetNextPrimaryAttack();

					bool bCanFire = true;

					static bool bOldBullet;

					if ((fNextPrimary > fCurTime) || bOldBullet)
						bCanFire = false;

					if (!(fNextPrimary > fCurTime))
						bOldBullet = false;

					if (gCvars.AIMONFIRE)
					{
						if (GetAsyncKeyState(0x01))
						{
							g_aimbot.Main(pUserCmd, pLocal);
						}
					}
					else
					{
						if (gCvars.SMOOTHPITCH > 0 && gCvars.SMOOTHYAW > 0)
						{
							g_aimbot.Main(pUserCmd, pLocal);
						}
						else
						{
							if (bCanFire)
							{
								g_aimbot.Main(pUserCmd, pLocal);
							}
						}
					}
				}

				if (gCvars.NOSPREAD)
				{
					if (pUserCmd->buttons & IN_ATTACK)
					{
						NoSpread(pUserCmd, pWeapon, pUserCmd->viewangles);
					}
				}

				if (gCvars.trigenable)
				{
					if (GetAsyncKeyState(gCvars.triggerkey))
					{
						g_aimbot.triggerbot(pUserCmd, pLocal);
					}
				}
			}

			if (gCvars.ENABLEAIM)
			{
				Math::ClampAngles(pUserCmd->viewangles);
			}
		}
	}
}

template<typename T> inline T get_BP()
{
	__asm mov eax, ebp
}

template<typename T> inline T get_SI()
{
	__asm mov eax, esi
}


using SetViewAngleFn = void(__stdcall*)(Vector &);
SetViewAngleFn org_SetViewAngles = nullptr;

void __stdcall hooked_SetViewAngles(Vector &angles)
{
	CUserCmd* cmd = get_SI<CUserCmd*>();
	unsigned* sequence_number = (*get_BP<unsigned**>() + 2);

	CBaseEntity* pLocal = pEntList->GetClientEntity(pEngine->GetLocalPlayer());

	if (pLocal && gCvars.NORECOIL)
	{
		if (get_SI<CBaseEntity*>() == pLocal)
			return;
	}

	org_SetViewAngles(angles);

	if (cmd && cmd->command_number == *sequence_number)
	{
		DoStuff(cmd,pLocal);

		*sequence_number = cmd->command_number;
	}
}
