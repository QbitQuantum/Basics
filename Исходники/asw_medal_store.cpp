bool C_ASW_Medal_Store::SaveMedalStore()
{
	if ( !m_bLoaded )
		return false;

	KeyValues *kv = new KeyValues( "CLIENTDAT" );
	
	// output missions/campaigns/kills
	kv->SetInt("MC", m_iMissionsCompleted);
	kv->SetInt("CC", m_iCampaignsCompleted);
	kv->SetInt("AK", m_iAliensKilled);

	kv->SetInt("OMC", m_iOfflineMissionsCompleted);
	kv->SetInt("OCC", m_iOfflineCampaignsCompleted);
	kv->SetInt("OAK", m_iOfflineAliensKilled);

	kv->SetInt( "LPL", m_iXP );
	kv->SetInt( "LPP", m_iPromotion );
	
	KeyValues *pSubSection = new KeyValues("NEWEQUIP");
	char buffer[64];
	if (pSubSection)
	{
		for (int i=0;i<m_NewEquipment.Count();i++)
		{			
			pSubSection->SetInt( "EQUIP", m_NewEquipment[i]);
		}
		kv->AddSubKey(pSubSection);
	}	

	// output player medals
	pSubSection = new KeyValues("LP");
	if (pSubSection)
	{
		for (int i=0;i<m_PlayerMedals.Count();i++)
		{			
			Q_snprintf(buffer, sizeof(buffer), "M%d", i);
			pSubSection->SetInt(buffer, m_PlayerMedals[i]);
		}
		kv->AddSubKey(pSubSection);
	}	

	for (int k=0;k<ASW_NUM_MARINE_PROFILES;k++)
	{
		Q_snprintf(buffer, sizeof(buffer), "LA%d", k);
		pSubSection = new KeyValues(buffer);
		if (pSubSection)
		{			
			for (int i=0;i<m_MarineMedals[k].Count();i++)
			{
				Q_snprintf(buffer, sizeof(buffer), "M%d", i);
				pSubSection->SetInt(buffer, m_MarineMedals[k][i]);				
			}
			kv->AddSubKey(pSubSection);
		}		
	}

	// offline medal store
	pSubSection = new KeyValues("FP");
	if (pSubSection)
	{
		for (int i=0;i<m_OfflinePlayerMedals.Count();i++)
		{			
			Q_snprintf(buffer, sizeof(buffer), "M%d", i);
			pSubSection->SetInt(buffer, m_OfflinePlayerMedals[i]);
		}
		kv->AddSubKey(pSubSection);
	}	

	for (int k=0;k<ASW_NUM_MARINE_PROFILES;k++)
	{
		Q_snprintf(buffer, sizeof(buffer), "FA%d", k);
		pSubSection = new KeyValues(buffer);
		if (pSubSection)
		{			
			for (int i=0;i<m_OfflineMarineMedals[k].Count();i++)
			{
				Q_snprintf(buffer, sizeof(buffer), "M%d", i);
				pSubSection->SetInt(buffer, m_OfflineMarineMedals[k][i]);				
			}
			kv->AddSubKey(pSubSection);
		}		
	}

	CUtlBuffer buf; //( 0, 0, CUtlBuffer::TEXT_BUFFER );
	kv->RecursiveSaveToFile( buf, 0 );

	// pad buffer with zeroes to make a multiple of 8
	int nExtra = buf.TellPut() % 8;
	while ( nExtra != 0 && nExtra < 8 )
	{
		buf.PutChar( 0 );
		nExtra++;
	}
	UTIL_EncodeICE( (unsigned char*) buf.Base(), buf.TellPut(), g_ucMedalStoreEncryptionKey );

	ISteamUser *pSteamUser = steamapicontext ? steamapicontext->SteamUser() : NULL;
	if ( !pSteamUser )
		return false;

	char szMedalFile[ 256 ];
	Q_snprintf( szMedalFile, sizeof( szMedalFile ), "cfg/clientc_%I64u.dat", pSteamUser->GetSteamID().ConvertToUint64() );
	int len = Q_strlen( szMedalFile );
	for ( int i = 0; i < len; i++ )
	{
		if ( szMedalFile[ i ] == ':' )
			szMedalFile[i] = '_';
	}

	bool bResult = filesystem->WriteFile( szMedalFile, "MOD", buf );
	if ( bResult )
	{
	#if defined(NO_STEAM)
		AssertMsg( false, "SteamCloud not available." );
	#else
		ISteamRemoteStorage *pRemoteStorage = SteamClient() ? ( ISteamRemoteStorage * )SteamClient()->GetISteamGenericInterface(
			SteamAPI_GetHSteamUser(), SteamAPI_GetHSteamPipe(), STEAMREMOTESTORAGE_INTERFACE_VERSION ) : NULL;

		if ( asw_steam_cloud.GetBool() && pRemoteStorage )
		{
			WriteFileToRemoteStorage( pRemoteStorage, "PersistentMarines.dat", szMedalFile );
		}
	#endif
	}

	return bResult;
}