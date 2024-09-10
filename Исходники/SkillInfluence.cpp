void CSkillInfluence::Serialize( CAr & ar )
{
	int j, nMax = 0;
	DWORD	dwOdd;

	if( ar.IsStoring() )	// Saving
	{
		for( j = 0; j < MAX_SKILLINFLUENCE; j++ )		// 데이타 있는것만 개수 셈.
			if( m_aSkillInfluence[j].wID > 0 )
				nMax ++;

		ar << nMax;
		for( j = 0; j < MAX_SKILLINFLUENCE ; ++j )
		{
			if( m_aSkillInfluence[j].wID > 0 )
			{
				ar << m_aSkillInfluence[j].wType;
				ar << m_aSkillInfluence[j].wID;

#if __VER >= 11 // __SYS_COLLECTING
				if( m_aSkillInfluence[j].wType == BUFF_ITEM2 )
				{
					time_t t	= (time_t)m_aSkillInfluence[j].dwLevel - time_null();
					ar << t;
				}
				else
					ar << m_aSkillInfluence[j].dwLevel;
#else	// __SYS_COLLECTING
				ar << m_aSkillInfluence[j].dwLevel;
#endif	// __SYS_COLLECTING

#ifdef __WORLDSERVER			
				if( m_aSkillInfluence[j].tmCount )
				{
					if( m_aSkillInfluence[j].tmTime )
						dwOdd = m_aSkillInfluence[j].tmCount - (timeGetTime() - m_aSkillInfluence[j].tmTime);	// 남은시간 계산.
					else
						dwOdd = m_aSkillInfluence[j].tmCount;
				}
				else
					dwOdd = 0;
				if( (int)dwOdd < 0 )		dwOdd = 0;
				ar << dwOdd;		// 남은 시간을 저장.
#else // World
				ar << m_aSkillInfluence[j].tmCount;
#endif // not World
			}
		}
	} else
	// Loading
	{

		memset( m_aSkillInfluence, 0, sizeof(m_aSkillInfluence) );
#if __VER < 8 //__CSC_VER8_3
		m_pEmptyNode = NULL;
#endif //__CSC_VER8_3
		ar >> nMax;
		for( j = 0 ; j < nMax; ++j )		// 있는만큼만 부른다.
		{
			ar >> m_aSkillInfluence[j].wType;
			ar >> m_aSkillInfluence[j].wID;
#if __VER >= 11 // __SYS_COLLECTING
			if( m_aSkillInfluence[j].wType == BUFF_ITEM2 )
			{
				time_t t;
				ar >> t;
				m_aSkillInfluence[j].dwLevel	= time_null() + t;
			}
			else
				ar >> m_aSkillInfluence[j].dwLevel;
#else	// __SYS_COLLECTING
			ar >> m_aSkillInfluence[j].dwLevel;
#endif	// __SYS_COLLECTING
			ar >> dwOdd;
#ifdef __WORLDSERVER				
			BOOL bCharged = FALSE;
			if( m_aSkillInfluence[j].wType == BUFF_ITEM
#if __VER >= 11 // __SYS_COLLECTING
				|| m_aSkillInfluence[j].wType == BUFF_ITEM2
#endif	// __SYS_COLLECTING
				)
			{
				ItemProp *pItemProp = prj.GetItemProp( m_aSkillInfluence[j].wID );
				if( pItemProp )
				{
					if( pItemProp->bCharged ) // 상용화 아이템은 종료가 안되게 수정
						bCharged = TRUE;
				}
			}
#if __VER >= 9	// __PET_0410
			else if( m_aSkillInfluence[j].wType == BUFF_PET )
				bCharged	= TRUE;
#endif	// __PET_0410
#ifdef __DST_GIFTBOX
			else if( m_aSkillInfluence[j].wType == BUFF_EQUIP )
				bCharged	= TRUE;
#endif // __DST_GIFTBOX

			if( bCharged == FALSE && m_pMover && dwOdd >= MIN(61) )
			{
				Error( "SkillInflu::>Load : %s %d", m_pMover->GetName(), dwOdd );
				dwOdd = MIN(60);
			}
#endif //__WORLDSERVER
			m_aSkillInfluence[j].tmCount = dwOdd;			// 로딩했을때 남은시간을 로딩해서 세기 시작.
		} // for