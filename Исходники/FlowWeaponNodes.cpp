	void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo )
	{
		/*if (event == eFE_Activate && IsPortActive(pActInfo,0))
		{
		IScriptSystem * pSS = gEnv->pScriptSystem;
		SmartScriptTable table;
		pSS->GetGlobalValue("Weapon", table);
		Script::CallMethod( table, "StartFire");
		}
		else */
		if (event == eFE_Initialize)
		{
			pActInfo->pGraph->SetRegularlyUpdated( pActInfo->myID, true );
		}
		else if (event == eFE_Update)
		{
			IEntity * pEntity = pActInfo->pEntity;
			if (pEntity)
			{
				Vec3 dir = GetPortVec3(pActInfo, 0) - pEntity->GetWorldTM().GetTranslation();

				dir.normalize();

				Vec3 up(0,0,1);
				Vec3 right(dir^up);

				if (right.len2() < 0.01f)
				{
					right = dir.GetOrthogonal();
				}

				Matrix34 tm(pEntity->GetWorldTM());

				tm.SetColumn(1, dir);
				tm.SetColumn(0, right.normalize());
				tm.SetColumn(2, right^dir);

				pEntity->SetWorldTM(tm);
			}
		}
	}