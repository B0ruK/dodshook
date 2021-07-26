#pragma once


typedef float(__thiscall* get_fov_t)(void*);
get_fov_t original_get_fov;

float __fastcall hkGetViewModelFOV(void* ecx, void* edx)
{
	CBaseEntity *pLocal = pEntList->GetClientEntity(pEngine->GetLocalPlayer());

	if (pLocal && pEngine->IsInGame() && gCvars.viewmodel > 67)
	{
		return gCvars.viewmodel;
	}
	else
	{
		return original_get_fov(ecx);
	}
}

using OverrideView = void(__thiscall*)(void* _this, CViewSetup*);
OverrideView OverrideView_original = nullptr;

void __fastcall hkOverrideView(void* _this, void* _edx, CViewSetup* setup)
{
	CBaseEntity *pLocal = pEntList->GetClientEntity(pEngine->GetLocalPlayer());

	if (pLocal && pEngine->IsInGame())
	{
		if (gCvars.viewfov > 0)
		{
			setup->m_fov += gCvars.viewfov;
		}
	}


	OverrideView_original(_this, setup);
}