#include "include.h"

PVOID GetInterface(LPCWSTR szModule, PCCH szObject)
{
	if (const auto Module = GetModuleHandleW(szModule))
	{
		const auto dwCreateInterface = reinterpret_cast<DWORD>(GetProcAddress(Module, "CreateInterface"));
		const auto dwShortJmp = dwCreateInterface + 0x5;
		const auto dwJmp = (dwShortJmp + *reinterpret_cast<DWORD *>(dwShortJmp)) + 0x4;

		auto pList = **reinterpret_cast<InterfaceNode ***>(dwJmp + 0x6);

		while (pList)
		{
			if ((strstr(pList->szName, szObject) && (strlen(pList->szName) - strlen(szObject)) < 5))
				return pList->fnGet();

			pList = pList->pNext;
		}
	}

	return nullptr;
}

void InitialiseInterfaces()
{
	pInfoPlayer = (IPlayerInfoManager*)(GetInterface(L"server.dll", "PlayerInfoManager"));
	pClient = (HLCLient*)(GetInterface(L"client.dll", "VClient"));
	pEngine = (CEngineClient*)(GetInterface(L"engine.dll", "VEngineClient"));
	pEntList = (CEntityList*)(GetInterface(L"client.dll", "VClientEntityList"));
	pModel = (CModelInfo*)(GetInterface(L"engine.dll", "VModelInfoClient"));
	pModelRender = (IVModelRender*)(GetInterface(L"engine.dll", "VEngineModel"));
	pMaterialSystem = (IMaterialSystem*)(GetInterface(L"materialsystem.dll", "VMaterialSystem"));
	pPanel = (IPanel*)(GetInterface(L"vgui2.dll", "VGUI_Panel"));
	pSurface = (ISurface*)(GetInterface(L"vguimatsurface.dll", "VGUI_Surface"));
	pEngineTrace = (CEnginetrace*)(GetInterface(L"engine.dll", "EngineTraceClient"));
	pRenderView = (IVRenderView*)(GetInterface(L"engine.dll", "VEngineRenderView"));
	pGlobalVars = pInfoPlayer->GetGlobalVars();
	pClientmode = **(void***)((*(DWORD**)pClient)[10] + 0x5);
}


void* pClientmode;
IPlayerInfoManager* pInfoPlayer;
CGlobalVars* pGlobalVars;
IVRenderView* pRenderView;
CEngineClient* pEngine;
IPanel* pPanel;
CEntityList* pEntList;
ISurface* pSurface;
IMaterialSystem* pMaterialSystem;
IVModelRender* pModelRender;
CModelInfo* pModel;
HLCLient* pClient;
CEnginetrace* pEngineTrace;