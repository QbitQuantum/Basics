void	KNpcTemplate::InitNpcBaseData(int nNpcTemplateId)
{
	if (nNpcTemplateId < 0 ) return;
	int nNpcTempRow = nNpcTemplateId + 2;

	g_NpcSetting.GetString(nNpcTempRow, "Name", "", Name, sizeof(Name));
	g_NpcSetting.GetInteger(nNpcTempRow, "Kind", 0, (int *)&m_Kind);
	g_NpcSetting.GetInteger(nNpcTempRow, "Camp", 0, &m_Camp);
	g_NpcSetting.GetInteger(nNpcTempRow, "Series", 0, &m_Series);
	
	g_NpcSetting.GetInteger(nNpcTempRow, "HeadImage",	0, &m_HeadImage);
	g_NpcSetting.GetInteger(nNpcTempRow, "ClientOnly",	0, &m_bClientOnly);
	g_NpcSetting.GetInteger(nNpcTempRow, "CorpseIdx",	0, &m_CorpseSettingIdx);
	
	g_NpcSetting.GetInteger(nNpcTempRow, "DeathFrame",	12, &m_DeathFrame);
	g_NpcSetting.GetInteger(nNpcTempRow, "WalkFrame",	15, &m_WalkFrame);
	g_NpcSetting.GetInteger(nNpcTempRow, "RunFrame",	15, &m_RunFrame);
	g_NpcSetting.GetInteger(nNpcTempRow, "HurtFrame",	10, &m_HurtFrame);
	g_NpcSetting.GetInteger(nNpcTempRow, "WalkSpeed",	5, &m_WalkSpeed);
	g_NpcSetting.GetInteger(nNpcTempRow, "AttackSpeed",	20, &m_AttackFrame);
	g_NpcSetting.GetInteger(nNpcTempRow, "CastSpeed",	20, &m_CastFrame);
	g_NpcSetting.GetInteger(nNpcTempRow, "RunSpeed",	10, &m_RunSpeed);
	g_NpcSetting.GetInteger(nNpcTempRow, "StandFrame",	15, &m_StandFrame);
	g_NpcSetting.GetInteger(nNpcTempRow, "StandFrame1", 15, &m_StandFrame1);
	g_NpcSetting.GetInteger(nNpcTempRow, "Stature",		0,  &m_nStature);

#ifdef _SERVER	
	g_NpcSetting.GetInteger(nNpcTempRow, "Treasure",		0, &m_Treasure);
	g_NpcSetting.GetInteger(nNpcTempRow, "AIMode",	0, &m_AiMode);
	g_NpcSetting.GetInteger(nNpcTempRow, "AIParam1",	0, &m_AiParam[0]);
	g_NpcSetting.GetInteger(nNpcTempRow, "AIParam2",	0, &m_AiParam[1]);
	g_NpcSetting.GetInteger(nNpcTempRow, "AIParam3",	0, &m_AiParam[2]);
	g_NpcSetting.GetInteger(nNpcTempRow, "AIParam4",	0, &m_AiParam[3]);
	g_NpcSetting.GetInteger(nNpcTempRow, "AIParam5",	0, &m_AiParam[4]);
	g_NpcSetting.GetInteger(nNpcTempRow, "AIParam6",	0, &m_AiParam[5]);
	g_NpcSetting.GetInteger(nNpcTempRow, "AIParam7",	0, &m_AiParam[6]);
	g_NpcSetting.GetInteger(nNpcTempRow, "AIParam8",	0, &m_AiParam[7]);
	g_NpcSetting.GetInteger(nNpcTempRow, "AIParam9",	0, &m_AiParam[8]);
	g_NpcSetting.GetInteger(nNpcTempRow, "AIParam10",	5, &m_AiParam[9]);

	g_NpcSetting.GetInteger(nNpcTempRow, "FireResistMax",	0, &m_FireResistMax);
	g_NpcSetting.GetInteger(nNpcTempRow, "ColdResistMax",	0, &m_ColdResistMax);
	g_NpcSetting.GetInteger(nNpcTempRow, "LightResistMax",	0, &m_LightResistMax);
	g_NpcSetting.GetInteger(nNpcTempRow, "PoisonResistMax",	0, &m_PoisonResistMax);
	g_NpcSetting.GetInteger(nNpcTempRow, "PhysicsResistMax",	0, &m_PhysicsResistMax);
	g_NpcSetting.GetInteger(nNpcTempRow, "ActiveRadius", 30, &m_ActiveRadius);
	g_NpcSetting.GetInteger(nNpcTempRow, "VisionRadius", 40, &m_VisionRadius);
	
	char szDropFile[200];
	g_NpcSetting.GetString(nNpcTempRow, "DropRateFile", "", szDropFile, sizeof(szDropFile));
	strlwr(szDropFile);
	strcpy(m_szDropRateFile, szDropFile);
	KItemDropRateNode DropNode;
	strcpy(DropNode.m_szFileName, szDropFile);
	
	if (g_ItemDropRateBinTree.Find(DropNode))
	{
		m_pItemDropRate = DropNode.m_pItemDropRate;
	}
	else
	{
		KItemDropRateNode newDropNode;
		strcpy(newDropNode.m_szFileName,szDropFile);
		newDropNode.m_pItemDropRate = g_GenItemDropRate(szDropFile);
		g_ItemDropRateBinTree.Insert(newDropNode);
		m_pItemDropRate = newDropNode.m_pItemDropRate;
	}
	
	int nAIMaxTime = 0;
	g_NpcSetting.GetInteger(nNpcTempRow, "AIMaxTime", 25, (int*)&nAIMaxTime);
	m_AIMAXTime = (BYTE)nAIMaxTime;
	
	g_NpcSetting.GetInteger(nNpcTempRow, "HitRecover", 0, &m_HitRecover);
	g_NpcSetting.GetInteger(nNpcTempRow, "ReviveFrame", 2400, &m_ReviveFrame);
	
	char szLevelScript[MAX_PATH];
	g_NpcSetting.GetString(nNpcTempRow, "LevelScript", "", szLevelScript, MAX_PATH);
	if (!szLevelScript[0])
		m_dwLevelSettingScript = 0;
	else
	{
#ifdef WIN32
		_strlwr(szLevelScript);
#else
		for (int nl = 0; szLevelScript[nl]; nl++)
			if (szLevelScript[nl] >= 'A' && szLevelScript[nl] <= 'Z')
				szLevelScript[nl] += 'a' - 'A';
#endif
		m_dwLevelSettingScript = g_FileName2Id(szLevelScript);
	}

#else
	g_NpcSetting.GetInteger(nNpcTempRow, "ArmorType", 0, &m_ArmorType);
	g_NpcSetting.GetInteger(nNpcTempRow, "HelmType", 0, &m_HelmType);
	g_NpcSetting.GetInteger(nNpcTempRow, "WeaponType", 0, &m_WeaponType);
	g_NpcSetting.GetInteger(nNpcTempRow, "HorseType", -1, &m_HorseType);
	g_NpcSetting.GetInteger(nNpcTempRow, "RideHorse",0, &m_bRideHorse);
	g_NpcSetting.GetString(nNpcTempRow, "ActionScript", "", ActionScript,sizeof(ActionScript));
	g_NpcSetting.GetString(nNpcTempRow, "LevelScript", "", m_szLevelSettingScript, 100);
#endif

	
}