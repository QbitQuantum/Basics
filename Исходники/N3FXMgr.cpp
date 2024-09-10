void CN3FXMgr::TriggerBundle(int SourceID, int SourceJoint, int FXID, __Vector3 TargetPos, int idx, int MoveType, unsigned int iVer)
{
	__TABLE_FX* pFX = s_pTbl_FXSource->Find(FXID);
	if(!pFX) return; 

	char buff[MAX_PATH];
	sprintf(buff, pFX->szFN.c_str());
	_strlwr(buff);
	std::string strTmp = buff;

	stlMAP_BUNDLEORIGIN_IT itOrigin = m_OriginBundle.find(strTmp);

	if(itOrigin != m_OriginBundle.end())	//같은 효과가 있다..
	{
		LPFXBUNDLEORIGIN pSrc = itOrigin->second;		
		CN3FXBundleGame* pBundle = new CN3FXBundleGame;
				
		pBundle->SetPreBundlePos(SourceID, SourceJoint);
		pSrc->pBundle->Duplicate(pBundle);
		pBundle->m_iID = FXID;
		pBundle->m_iIdx = idx;
		pBundle->m_iMoveType = MoveType;
		pBundle->m_iSourceJoint = SourceJoint;

		pBundle->Trigger(SourceID, TargetPos, pFX->dwSoundID);		
		m_ListBundle.push_back(pBundle);
		pSrc->iNum++;
	}
	else	//같은 효과가 없다..
	{
		LPFXBUNDLEORIGIN pSrc = new FXBUNDLEORIGIN;
		pSrc->pBundle = new CN3FXBundleGame;
		pSrc->pBundle->LoadFromFile(pFX->szFN, iVer);

		CN3FXBundleGame* pBundle = new CN3FXBundleGame;

		pBundle->SetPreBundlePos(SourceID, SourceJoint);
		pSrc->pBundle->Duplicate(pBundle);	
		pBundle->m_iID = FXID;
		pBundle->m_iIdx = idx;
		pBundle->m_iMoveType = MoveType;
		pBundle->m_iSourceJoint = SourceJoint;

		pBundle->Trigger(SourceID, TargetPos, pFX->dwSoundID);
		m_ListBundle.push_back(pBundle);

		pSrc->iNum++;
		m_OriginBundle.insert(stlMAP_BUNDLEORIGIN_VALUE(strTmp, pSrc));
	}
}