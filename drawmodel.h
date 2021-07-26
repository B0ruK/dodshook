
void OverridematerialXQZ(IMaterial* mat, float r, float g, float b)
{
	mat->SetMaterialVarFlag(IGNOREZ, true);

	float Color[3] = { r / 255, g / 255, b / 255 };

	pRenderView->SetColorModulation(Color);
	pModelRender->ForcedMaterialOverride(mat);
}

void Overridematerial(IMaterial* mat, float r, float g, float b)
{
	mat->SetMaterialVarFlag(IGNOREZ, false);

	float Color[3] = { r / 255, g / 255, b / 255 };

	pRenderView->SetColorModulation(Color);
	pModelRender->ForcedMaterialOverride(mat);
}


typedef void(__thiscall *DrawModelExecuteFn)(IVModelRender*, void*, const ModelRenderInfo&, void*);
DrawModelExecuteFn draw_model_original = nullptr;

void __stdcall hkDrawModelExecute(void* state, const ModelRenderInfo &pInfo, void *bonetoworld)
{
	static IMaterial* material = pMaterialSystem->FindMaterial("debug/debugambientcube", "Model textures");

	if (pInfo.entity_index && material)
	{
		CBaseEntity* pEntity = (CBaseEntity*)pEntList->GetClientEntity(pInfo.entity_index);
		CBaseEntity *pLocal = pEntList->GetClientEntity(pEngine->GetLocalPlayer());

		if (gCvars.bMenu)
		{
			material->SetMaterialVarFlag(ZNEARER, true);
			material->SetMaterialVarFlag(NOCULL, true);
			material->SetMaterialVarFlag(NOFOG, true);
			material->SetMaterialVarFlag(HALFLAMBERT, true);
		}

		if (pEntity && pLocal && material)
		{
			if (pEntity->GetTeamNum() == TEAM_TT || pEntity->GetTeamNum() == TEAM_CT)
			{
				if ((gCvars.CHAMSTEAM || pEntity->GetTeamNum() != pLocal->GetTeamNum()) && gCvars.CHAMS)
				{
					if (pEntity->IsAlive())
					{
						if (gCvars.CHAMSXQZ)
						{
							OverridematerialXQZ(material, gCvars.espcolortwo, gCvars.espcolorthird, gCvars.espcolorone);
							draw_model_original(pModelRender, state, pInfo, bonetoworld);
						}
						Overridematerial(material, gCvars.espcolorone, gCvars.espcolortwo, gCvars.espcolorthird);
					}
				}
			}
		}
	}

	draw_model_original(pModelRender, state, pInfo,bonetoworld);
	pModelRender->ForcedMaterialOverride(nullptr);
}

