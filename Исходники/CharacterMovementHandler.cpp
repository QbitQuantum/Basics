void CUser::ZoneChange(uint16 sNewZone, float x, float z)
{
	C3DMap * pMap = g_pMain->GetZoneByID(sNewZone);
	if (pMap == nullptr) 
		return;

	ZoneChangeError errorReason;
	if (!CanChangeZone(pMap, errorReason))
	{
		Packet result;

		switch (errorReason)
		{
		case ZoneChangeErrorWrongLevel:
			/* this will depend on the zone */
			break;

		case ZoneChangeErrorWarActive:
			result.Initialize(WIZ_WARP_LIST);
			result << uint8(2) << uint8(4);
			Send(&result);
			break;

		case ZoneChangeErrorNeedLoyalty:
			/* does this have an error? */
			break;
		}

		return;
	}

	m_bWarp = true;
	m_bZoneChangeFlag = true;

	UserInOut(INOUT_OUT);

	if (sNewZone == ZONE_SNOW_BATTLE)
		SetMaxHp(1);

	if (GetZoneID() != sNewZone)
	{
		SetZoneAbilityChange();

		// Reset the user's anger gauge when leaving the zone
		// Unknown if this is official behaviour, but it's logical.
		if (GetAngerGauge() > 0)
			UpdateAngerGauge(0);

		/* 
			Here we also send a clan packet with subopcode 0x16 (with a byte flag of 2) if war zone/Moradon
			or subopcode 0x17 (with nWarEnemyID) for all else
		*/
#if 0
		if (isInClan())
		{
			CKnights * pKnights = g_pMain->GetClanPtr(GetClanID());
			if (pKnights != nullptr
					&& pKnights->bKnightsWarStarted)
			{
				Packet clanPacket(WIZ_KNIGHTS_PROCESS);
				if (pMap->isWarZone() || byNewZone == ZONE_MORADON)
					clanPacket << uint8(0x17) << uint8(2);
				else 
					clanPacket << uint16(0x16) << uint16(0 /*nWarEnemyID*/);

				Send(&clanPacket);
			}
		}
#endif


		if (sNewZone == ZONE_SNOW_BATTLE)
			SetMaxHp();

		if (isInParty())
			PartyRemove(GetSocketID());

		ResetWindows();
	}

	m_bZone = (uint8) sNewZone; // this is 2 bytes to support the warp data loaded from SMDs. It should not go above a byte, however.
	SetPosition(x, 0.0f, z);
	m_pMap = pMap;

	if (g_pMain->m_nServerNo != pMap->m_nServerNo)
	{
		_ZONE_SERVERINFO *pInfo = g_pMain->m_ServerArray.GetData(pMap->m_nServerNo);
		if (pInfo == nullptr) 
			return;

		UserDataSaveToAgent();

		m_bLogout = 2;	// server change flag
		SendServerChange(pInfo->strServerIP, 2);
		return;
	}
	
	SetRegion(GetNewRegionX(), GetNewRegionZ());

	Packet result(WIZ_ZONE_CHANGE, uint8(ZoneChangeTeleport));
	result << uint16(GetZoneID()) << GetSPosX() << GetSPosZ() << GetSPosY() << g_pMain->m_byOldVictory;
	Send(&result);

	if (!m_bZoneChangeSameZone)
	{
		m_sWhoKilledMe = -1;
		m_iLostExp = 0;
		m_bRegeneType = 0;
		m_tLastRegeneTime = 0;
		m_sBind = -1;
		InitType3();
		InitType4();
		CMagicProcess::CheckExpiredType9Skills(this, true);
		SetUserAbility();
	}	

	result.Initialize(AG_ZONE_CHANGE);
	result << GetSocketID() << GetZoneID();
	Send_AIServer(&result);

	m_bZoneChangeSameZone = false;
	m_bZoneChangeFlag = false;
}