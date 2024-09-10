BOOL	CTitleManager::LoadTitle(LPCTSTR lpszFileName)
{
	HonorData	TempData;
	CScript		script;


	if( script.Load( lpszFileName ) == FALSE )
		return FALSE;

	script.tok = 0;

	TempData.Init();
	TempData.nID		= script.GetNumber(); // ID

	while(script.tok != FINISHED)
	{
		
		TempData.nLGrouping = script.GetNumber();	// 대분류
		TempData.nSGrouping = script.GetNumber();	// 소분류
		TempData.nNeed		= script.GetNumber();	// 획득 조건
		script.GetToken();
		TempData.strTitle	= script.Token;	// 타이틀 이름
		switch(TempData.nLGrouping)
		{
			case HI_HUNT_MONSTER:
				if(m_mapMonster.size() < MONSTER_TITLE_MAX)
				{
					m_mapMonster.insert(map<int, HonorData>::value_type(TempData.nSGrouping, TempData));
					m_mapAll.insert(map<int, HonorData>::value_type(TempData.nID, TempData));
				}
				else
				{
					Error("Too many title about monster!");
					return FALSE;
				}
				break;

			case HI_USE_ITEM:
				if(m_mapItem.size() < MONSTER_TITLE_MAX)
				{
					m_mapItem.insert(map<int, HonorData>::value_type(TempData.nSGrouping, TempData));
					m_mapAll.insert(map<int, HonorData>::value_type(TempData.nID, TempData));
				}
				else
				{
					Error("Too many title about item!");
					return FALSE;
				}
				break;

			default:
				m_mapEtc.insert(map<int, HonorData>::value_type(TempData.nSGrouping, TempData));
				m_mapAll.insert(map<int, HonorData>::value_type(TempData.nID, TempData));
				break;
		};
		m_nCurrentTitleCount++;
		TempData.Init();
		TempData.nID		= script.GetNumber(); // ID
	}
	
	return TRUE;
}