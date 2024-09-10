void MMatchClient::UpdateObjCache(MMatchObjCache* pCache)
{
	MMatchObjCache* pScanCache = FindObjCache(pCache->GetUID());
	if (pScanCache != NULL) return;

	MMatchObjCache* pNewCache = new MMatchObjCache;

	pNewCache->SetInfo(pCache->GetUID(), pCache->GetName(), pCache->GetClanName(), pCache->GetLevel(), 
					   pCache->GetUGrade(), pCache->GetPGrade()
					   , pCache->GetRank(), pCache->GetKillCount(), pCache->GetDeathCount(), pCache->GetDTGrade());
	pNewCache->SetCLID(pCache->GetCLID());
	pNewCache->SetEmblemChecksum(pCache->GetEmblemChecksum());
	pNewCache->AssignCostume(pCache->GetCostume());
	pNewCache->SetFlags(pCache->GetFlags());

	_ASSERT(m_ObjCacheMap.find(pNewCache->GetUID())==m_ObjCacheMap.end());
	m_ObjCacheMap.Insert(pNewCache->GetUID(), pNewCache);
}