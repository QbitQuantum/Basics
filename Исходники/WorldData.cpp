void CWorld::loadMob()
{
	CTString fnTemp; 
	CTString strFullPath = _fnmApplicationPath.FileDir();
	CTString fnZoneFlag		= strFullPath + "data\\ZoneFlag.lod";

	static BOOL		bLoadMobData = TRUE;
	const BOOL		bWETestGame	= (_bWorldEditorApp && _bInTestGame);

	if ((bLoadMobData && !_bWorldEditorApp) || bWETestGame)
	{
		CTString	fnMobData;

		if( ( _pGameState && _pGameState->GetGameMode() != CGameState::GM_NONE ) || bWETestGame )
		{			
			CallProgressHook_t(0.0f);

			switch( g_iCountry )
			{
			case THAILAND:
				fnMobData.PrintF("data\\mobAll_th.lod");
				break;
			default:
				fnMobData.PrintF("data\\mobAll.lod");
				break;
			}

			fnTemp = strFullPath + fnMobData;

			if(CMobData::loadEx(fnTemp) == false)
			{
				MessageBox(NULL, "Npc file is not correct", "Error!", MB_OK);
				_pGameState->Running() = FALSE;
				_pGameState->QuitScreen() = FALSE;
			}

			if(CMobData::LoadZoneData(fnZoneFlag) == false)
			{
				MessageBox(NULL, "zoneFlag file is not correct", "Error!", MB_OK);
				_pGameState->Running() = FALSE;
				_pGameState->QuitScreen() = FALSE;
			}

			fnTemp = strFullPath + "data\\npc_channel.bin";
			CMobData::LoadChannelData(fnTemp);

			CallProgressHook_t(1.0f);
			LoadStringNPCName();

			bLoadMobData = FALSE;
		}
	}
}