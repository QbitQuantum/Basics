void MMatchObjectCacheBuilder::AddObject(MMatchObject* pObj)
{
	MMatchObjCache* pCache = new MMatchObjCache;
	int nItemID=0;
	MMatchItemDesc* pItemDesc = NULL;

	MMatchCharInfo* pCharInfo = pObj->GetCharInfo();
//	_ASSERT(pCharInfo);
	if (pCharInfo == NULL)
	{
		delete pCache;
		return;
	}

	MMatchObjectDuelTournamentCharInfo* pDTCharInfo = pObj->GetDuelTournamentCharInfo();
	int nDTLastWeekGrade = pDTCharInfo ? pDTCharInfo->GetLastWeekGrade() : 0;

	pCache->SetInfo(pObj->GetUID(), pObj->GetName(), pCharInfo->m_ClanInfo.m_szClanName, 
					pCharInfo->m_nLevel, pObj->GetAccountInfo()->m_nUGrade, pObj->GetAccountInfo()->m_nPGrade
					, pCharInfo->m_nRank, pCharInfo->m_nTotalKillCount, pCharInfo->m_nTotalDeathCount, nDTLastWeekGrade );
	pCache->SetCLID(pObj->GetCharInfo()->m_ClanInfo.m_nClanID);

	MMatchClan* pClan = MMatchServer::GetInstance()->GetClanMap()->GetClan(pObj->GetCharInfo()->m_ClanInfo.m_nClanID);
	if (pClan)
		pCache->SetEmblemChecksum(pClan->GetEmblemChecksum());
	else
		pCache->SetEmblemChecksum(0);

	pCache->GetCostume()->nSex = pObj->GetCharInfo()->m_nSex;
	pCache->GetCostume()->nHair = pObj->GetCharInfo()->m_nHair;
	pCache->GetCostume()->nFace = pObj->GetCharInfo()->m_nFace;

	for (int i=0; i < MMCIP_END; i++)
	{
		if (!pObj->GetCharInfo()->m_EquipedItem.IsEmpty(MMatchCharItemParts(i)))
		{
			pCache->GetCostume()->nEquipedItemID[i] =
				pObj->GetCharInfo()->m_EquipedItem.GetItem(MMatchCharItemParts(i))->GetDescID();
		}
		else
		{
			pCache->GetCostume()->nEquipedItemID[i] = 0;
		}
	}

	pCache->SetFlags(pObj->GetPlayerFlags());

	m_ObjectCacheList.push_back(pCache);
}