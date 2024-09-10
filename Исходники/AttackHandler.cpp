void CUser::Attack(Packet & pkt)
{
	Packet result;
	int16 sid = -1, tid = -1, damage, delaytime, distance;	
	uint8 bType, bResult;	
	
	CUser* pTUser = NULL;

	pkt >> bType >> bResult >> tid >> delaytime >> distance;

//	delaytime = delaytime / 100.0f;
//	distance = distance / 10.0f;

	if (isBlinking()
		|| isDead())
		return;

	_ITEM_TABLE *pTable = GetItemPrototype(RIGHTHAND);
	if (pTable == NULL) 
		return;
	
	// If you're holding a weapon, do a client-based (ugh, do not trust!) delay check.
	if (pTable 
		&& (delaytime < pTable->m_sDelay
			|| distance > pTable->m_sRange))
		return;	
	// Empty handed.
	else if (delaytime < 100)
		return;			

	// We're attacking a player...
	if (tid < NPC_BAND)
	{
		pTUser = g_pMain->GetUserPtr(tid);
 
		if (pTUser == NULL || pTUser->isDead() || pTUser->isBlinking()
				|| (pTUser->GetNation() == GetNation() && GetZoneID() != 48 /* TO-DO: implement better checks */)
				|| !isAttackZone()) 
			bResult = 0;
		else 
		{
			damage = GetDamage(pTUser, NULL);
			if (GetZoneID() == ZONE_SNOW_BATTLE && g_pMain->m_byBattleOpen == SNOW_BATTLE)
				damage = 0;		

			if (damage <= 0)
				bResult = 0;
			else 
			{
				// TO-DO: Move all this redundant code into appropriate event-based methods so that all the other cases don't have to copypasta (and forget stuff).
				pTUser->HpChange(-damage, this);
				if (pTUser->isDead())
					bResult = 2;

				ItemWoreOut(ATTACK, damage);
				pTUser->ItemWoreOut(DEFENCE, damage);
				SendTargetHP(0, tid, -damage);
			}
		}
	}
	// We're attacking an NPC...
	else if (tid >= NPC_BAND)
	{
		// AI hasn't loaded yet
		if (g_pMain->m_bPointCheckFlag == FALSE)	
			return;	

		CNpc *pNpc = g_pMain->m_arNpcArray.GetData(tid);		
		if (pNpc != NULL && pNpc->isAlive() 
			&& (pNpc->GetNation() == 0 || pNpc->GetNation() == GetNation()))
		{
			result.SetOpcode(AG_ATTACK_REQ);
			result	<< bType << bResult
					<< GetSocketID() << tid
					<< uint16(m_sTotalHit * m_bAttackAmount / 100)
					<< uint16(m_sTotalAc + m_sACAmount)
					<< m_sTotalHitrate /* this is actually a float. screwed up naming... */
					<< m_sTotalEvasionrate /* also a float */
					<< m_sItemAc
					<< m_bMagicTypeLeftHand << m_bMagicTypeRightHand
					<< m_sMagicAmountLeftHand << m_sMagicAmountRightHand;
			g_pMain->Send_AIServer(&result);	
			return;
		}
	}

	result.SetOpcode(WIZ_ATTACK);
	result << bType << bResult << GetSocketID() << tid;
	SendToRegion(&result);

	if (tid < NPC_BAND
		&& bResult == 2 // 2 means a player died.
		&& pTUser) 
	{
		pTUser->Send(&result);
		TRACE("*** User Attack Dead, id=%s, result=%d, type=%d, HP=%d\n", pTUser->m_pUserData->m_id, bResult, pTUser->m_bResHpType, pTUser->m_pUserData->m_sHp);
	}
}