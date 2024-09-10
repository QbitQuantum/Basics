/*
 *	추천검색어를 유지하는 리스트가 있다는 조건하에 코딩한 것입니다.
    추천검색어의 갯수를 구하고 그 갯수만큼 루틴을 돌아서서
	추천검색어를 나타낼 윈도우(CRcmmWordWnd)를 생성합니다.
	생성한 윈도우는 vector(m_vecRcmmWordList)에서 유지합니다. 
 */
void CDlg_Search::MakeRcmmWordList()
{
	// Lock을 사용하는 대신 m_hThread가 떠 있으면 m_listWords를 사용하지 않는다.
	if( m_hThread || m_listWords.size() == 0) return;

	CRect rcClient;
	GetClientRect(&rcClient);

#ifdef USE_CLIPRECOMMEND
	m_rgnClip.SetRectRgn(&rcClient);
#endif

	CString strRcmmWord;
	CRect rectWord;
#ifdef USE_CLIPRECOMMEND
	CRgn rgnTmp;
	rgnTmp.CreateRectRgn(0, 0, 0, 0);
#endif
	int nBeforeLeft = m_rectSrchRcmmWordTitle.left;//"추천검색어 : " 길이
	nBeforeLeft += m_rectSrchRcmmWordTitle.Width();
	nBeforeLeft += 5;
	rectWord = m_rectSrchRcmmWordTitle;
	rectWord.left = nBeforeLeft;

	list<CString>::iterator it;
	std::vector< SmartPtr<CRcmmWordWnd> >::iterator wit;

	int nIndex = 0;

	it = m_listWords.begin();
	wit = m_vecRcmmWordList.begin();
	for( ;
		wit != m_vecRcmmWordList.end() && it != m_listWords.end(); ++wit, ++it)
	{

		for( ; it != m_listWords.end(); ++it )
		{
			strRcmmWord = (*it);
//			TRACE(_T("kEYWORD : %s\r\n"), strRcmmWord);
			if(strRcmmWord == _T("")) continue;
					
			//추천 검색어를 나타낼 영역의 크기를 구한다. 
			GetMsgRect(strRcmmWord, rectWord);		
			int nWidth = rectWord.Width();
			int nHeight = rectWord.Height();
			rectWord.left = nBeforeLeft;
			rectWord.top = m_rectSrchRcmmWordTitle.top;
			rectWord.bottom = rectWord.top + nHeight; ///+ 12;
			rectWord.right = rectWord.left + nWidth;

			// 너무 긴 추천 검색어는 제거한다.
			if(rectWord.Width() > m_rectSrchRcmmWord.Width() / 2)
				continue;

			++nIndex;

			//추천검색어 중에서 마지막으로 나타내는 검색어의 right를 제한
	//		if( rectWord.left <= m_rectSrchRcmmWord.right && 
	//			rectWord.right > m_rectSrchRcmmWord.right )
	//			rectWord.right = m_rectSrchRcmmWord.right;

			(*wit)->MoveWindow(rectWord);
			(*wit)->SetRcmmWord(strRcmmWord);
			(*wit)->SetRealRect(rectWord);
			//영역 밖의 것은 Hide 한다. 
			if( rectWord.right > m_rectSrchRcmmWord.right || !m_bShowRecommend)
			{
				(*wit)->ShowWindow(SW_HIDE);

#ifdef USE_CLIPRECOMMEND
				rgnTmp.SetRectRgn(&rectWord);
				m_rgnClip.CombineRgn(&m_rgnClip, &rgnTmp, RGN_DIFF);
#endif
			}
			else if(m_bShowRecommend)
			{
				(*wit)->ShowWindow(SW_NORMAL);
				(*wit)->Invalidate();
	//			CRect rc;
	//			pWnd->GetWindowRect(&rc);
	//			ScreenToClient(&rc);
			}
			
		
			nBeforeLeft += nWidth;
			nBeforeLeft += 3;//간격 

			break;
		}

		if(nBeforeLeft >= m_rectSrchRcmmWord.right )
			break;
	}

	while(wit != m_vecRcmmWordList.end())
	{
		(*wit)->ShowWindow(SW_HIDE);
		++wit;
	}

	m_nValidRecomm = nIndex;

	Invalidate();

}