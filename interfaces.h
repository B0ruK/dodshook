

extern void InitialiseInterfaces();

extern void* pClientmode;
extern IPlayerInfoManager* pInfoPlayer;
extern CGlobalVars* pGlobalVars;
extern CEngineClient* pEngine;
extern IPanel* pPanel;
extern CEntityList* pEntList;
extern ISurface* pSurface;
extern IMaterialSystem* pMaterialSystem;
extern IVModelRender* pModelRender;
extern CModelInfo* pModel;
extern HLCLient* pClient;
extern CEnginetrace* pEngineTrace;
extern IVRenderView* pRenderView;

struct InterfaceNode
{
	void* (*fnGet)();
	const char* szName;
	InterfaceNode* pNext;
};