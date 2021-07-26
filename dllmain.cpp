

#include "include.h"
#include "drawmodel.h"
#include "overrideview.h"
#include "createmove.h"
#include "panel.h"

vmt_hook* clientmode;
vmt_hook* panels;
vmt_hook* drawmodels;
vmt_hook* engine;

void InitializeStuff()
{	
	static bool once = false;

	if (!once)
	{
		InitialiseInterfaces();
		g_Netvarmanager.Init();

		clientmode = new vmt_hook(pClientmode);
		OverrideView_original = clientmode->hook<OverrideView>(16, hkOverrideView);
		original_get_fov = clientmode->hook<get_fov_t>(32, hkGetViewModelFOV);

		panels = new vmt_hook(pPanel);
		painttraverse_original = panels->hook<paint_traverse_t>(41, hkPaintTraverse);

		drawmodels = new vmt_hook(pModelRender);
		draw_model_original = drawmodels->hook<DrawModelExecuteFn>(19, hkDrawModelExecute);

		engine = new vmt_hook(pEngine);
		org_SetViewAngles = engine->hook<SetViewAngleFn>(20, hooked_SetViewAngles);

		Draw::InitFonts();

		once = true;
	}
}

int __stdcall DllMain(void*, int r, void*)
{
	if (r == 1)
	{
		InitializeStuff();
	}

	return 1;
}
