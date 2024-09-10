BOOL CWndTutorial::LoadTutorial(LPCTSTR lpszFileName)
{
	
	CScript			s;
	int				nIndex = 0;
	CString			strKeyword;
	TUTORIAL_STRING temp;

	if( s.Load( lpszFileName ) == FALSE )
		return FALSE;
	s.tok = 0;
	m_mapTutorial.clear();

	// {
	//	제목(문자열)
	//	내용(문자열)
	// }
	while( s.tok != FINISHED )
	{
		s.GetToken();	// {
		s.GetToken();	//
		temp.strTitle		= s.token;
		s.GetToken();
		temp.strContents	= s.token;
		m_mapTutorial.insert(map<int, TUTORIAL_STRING>::value_type(nIndex, temp));
		s.GetToken();	// }

		// 완료한 레벨까지만 추가한다
		if(g_Option.m_nTutorialLv >= nIndex + 1)
		{
			CWndListBox* pWndListBox	= (CWndListBox*)GetDlgItem( WIDC_LIST1 );
			pWndListBox->AddString( temp.strTitle );
		}
		++nIndex;
	}
	return TRUE;

}