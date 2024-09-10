void CFlowSetupModelPostRender::ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo )
{
	switch (event)
	{
	case eFE_Initialize:
		break;
	case eFE_Activate:
		if (IsPortActive(pActInfo, IN_SHUTDOWN))
		{
			CMenuRender3DModelMgr::Release(true);

			ITexture *tex = NULL;
			//unbind tex from MC
			if(gEnv->pConsole->GetCVar("r_UsePersistentRTForModelHUD")->GetIVal() > 0)		
				tex  = gEnv->pRenderer->EF_LoadTexture("$ModelHUD");
			else
				tex  = gEnv->pRenderer->EF_LoadTexture("$BackBuffer");

			IUIElement* pElement = pFlashUI->GetUIElement(sUIElement.c_str());
			IUIElement* pUIElement = pElement ? pElement->GetInstance(0) : NULL;
			if(pUIElement)
				pUIElement->UnloadTexFromMc(sMovieClipName.c_str(), tex);

			return;
		}
		
		if (IsPortActive(pActInfo, IN_START))
		{
			INDENT_LOG_DURING_SCOPE();

			// Setup scene settings
			CMenuRender3DModelMgr::SSceneSettings sceneSettings;
			sceneSettings.fovScale = 0.85f;
			sceneSettings.fadeInSpeed = 0.01f;
			sceneSettings.flashEdgeFadeScale = 0.0f;
			sceneSettings.ambientLight = Vec4(GetPortVec3(pActInfo, IN_AMBIENTLIGHTCOLOR), GetPortFloat(pActInfo, IN_AMBIENTLIGHTSTRENGTH));
			sceneSettings.lights.resize(3);
			sceneSettings.lights[0].pos.Set(-25.f, -10.f, 30.f);
			sceneSettings.lights[0].color = GetPortVec3(pActInfo, IN_LIGHTCOLOR1);
			sceneSettings.lights[0].specular = 4.f;
			sceneSettings.lights[0].radius = 400.f;
			sceneSettings.lights[1].pos.Set(25.f, -4.f, 30.f);
			sceneSettings.lights[1].color = GetPortVec3(pActInfo, IN_LIGHTCOLOR2);
			sceneSettings.lights[1].specular = 10.f;
			sceneSettings.lights[1].radius = 400.f;
			sceneSettings.lights[2].pos.Set(60.f, 40.f, 10.f);
			sceneSettings.lights[2].color = GetPortVec3(pActInfo, IN_LIGHTCOLOR3);
			sceneSettings.lights[2].specular = 10.f;
			sceneSettings.lights[2].radius = 400.f;

			//Create scene
			CMenuRender3DModelMgr *renderModels = new CMenuRender3DModelMgr();
			renderModels->SetSceneSettings(sceneSettings);

			ITexture *tex = NULL;
			//Fetch texture and send to movieclip
			if(gEnv->pConsole->GetCVar("r_UsePersistentRTForModelHUD")->GetIVal() > 0)		
				tex  = gEnv->pRenderer->EF_LoadTexture("$ModelHUD");
			else
				tex  = gEnv->pRenderer->EF_LoadTexture("$BackBuffer");

			string sStr = GetPortString(pActInfo, IN_MC);
			string::size_type sPos = sStr.find( ':' );
			sUIElement = sStr.substr( 0, sPos );
			sMovieClipName = sStr.substr( sPos + 1 );

			IUIElement* pElement = pFlashUI->GetUIElement(sUIElement.c_str());
			IUIElement* pUIElement = pElement ? pElement->GetInstance(0) : NULL;
			if(pUIElement)
				pUIElement->LoadTexIntoMc(sMovieClipName.c_str(), tex);
			else
				CryWarning(VALIDATOR_MODULE_FLOWGRAPH, VALIDATOR_WARNING, "CFlowAdd3DModelToHUD: Movieclip not found");

			//check debug info
			float debugscale = GetPortFloat(pActInfo, IN_DEBUGSCALE);
			ICVar* cv_debugRender = gEnv->pConsole->GetCVar("g_post3DRendererDebug");
			if(debugscale > 0.0f)
			{
				if(cv_debugRender)
				{
					cv_debugRender->Set(2);
					CMenuRender3DModelMgr::GetInstance()->SetDebugScale(debugscale);
				}
			}
			else
			{
				cv_debugRender->Set(0);
			}
			
		}
		break;
	}
}