	EContextEstablishTaskResult OnStep(SContextEstablishState& state)
	{
		ILevel*			pLevel = CCryAction::GetCryAction()->GetILevelSystem()->GetCurrentLevel();
		if (!pLevel)
		{
			GameWarning("level is null");
			return eCETR_Failed;
		}
		const char * levelName = CCryAction::GetCryAction()->GetLevelName();
		if (!levelName)
		{
			GameWarning("levelName is null");
			return eCETR_Failed;
		}
		ILevelInfo* pLevelInfo = CCryAction::GetCryAction()->GetILevelSystem()->GetLevelInfo(levelName);
		if (!pLevelInfo)
		{
			GameWarning("levelInfo is null");
			return eCETR_Failed;
		}


		// delete any pending entities before reserving EntityIds in LoadEntities()
		gEnv->pEntitySystem->DeletePendingEntities();

		string missionXml = pLevelInfo->GetDefaultGameType()->xmlFile;
		string xmlFile = string(pLevelInfo->GetPath()) + "/" + missionXml;

		XmlNodeRef rootNode = GetISystem()->LoadXmlFromFile(xmlFile.c_str());

		if (rootNode)
		{
			const char *script = rootNode->getAttr("Script");

			if (script && script[0])
				gEnv->pScriptSystem->ExecuteFile(script, true, true);

			XmlNodeRef objectsNode = rootNode->findChild("Objects");

			if (objectsNode)
				gEnv->pEntitySystem->LoadEntities(objectsNode, false);
		}
		else
			return eCETR_Failed;

		SEntityEvent loadingCompleteEvent(ENTITY_EVENT_LEVEL_LOADED);
		gEnv->pEntitySystem->SendEventToAll( loadingCompleteEvent );

		return eCETR_Ok;
	}