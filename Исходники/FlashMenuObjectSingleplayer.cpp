void CFlashMenuObject::UpdateSingleplayerDifficulties()
{
	if(!m_apFlashMenuScreens[MENUSCREEN_FRONTENDSTART])
		return;

	if(!m_pPlayerProfileManager)
		return;

	IPlayerProfile *pProfile = m_pPlayerProfileManager->GetCurrentProfile(m_pPlayerProfileManager->GetCurrentUser());
	if(!pProfile)
		return;

	string sGeneralPath = "Singleplayer.Difficulty";
	int iDifficulties = 8;
/*	for(int i=0; i<EDifficulty_END; ++i)
	{
		string sPath = sGeneralPath;
		char c[5];
		itoa(i, c, 10);
		sPath.append(c);
		sPath.append(".available");

		TFlowInputData data;
		pProfile->GetAttribute(sPath, data, false);
		bool bDone = false;
		data.GetValueWithConversion(bDone);
		if(bDone)
		{
			iDifficulties += i*2;
		}
	}
*/
	int iDifficultiesDone = 0;
	for(int i=0; i<EDifficulty_END; ++i)
	{
		string sPath = sGeneralPath;
		char c[5];
		itoa(i, c, 10);
		sPath.append(c);
		sPath.append(".done");

		TFlowInputData data;
		pProfile->GetAttribute(sPath, data, false);
		bool bDone = false;
		data.GetValueWithConversion(bDone);
		if(bDone)
		{
			iDifficultiesDone += std::max(i*2,1);
		}
	}

	TFlowInputData data;
	pProfile->GetAttribute("Singleplayer.LastSelectedDifficulty", data, false);
	int iDiff = 2;
	data.GetValueWithConversion(iDiff);

	if(iDiff<=0)
	{
		iDiff = 2;
	}

	m_apFlashMenuScreens[MENUSCREEN_FRONTENDSTART]->Invoke("Root.MainMenu.SinglePlayer.enableDifficulties", iDifficulties);
	m_apFlashMenuScreens[MENUSCREEN_FRONTENDSTART]->Invoke("Root.MainMenu.SinglePlayer.enableDifficultiesStats", iDifficultiesDone);
	m_apFlashMenuScreens[MENUSCREEN_FRONTENDSTART]->Invoke("Root.MainMenu.SinglePlayer.selectDifficulty", iDiff);
}