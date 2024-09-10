void CDialogMsg::AddMessage( CObj* pObj, LPCTSTR lpszMessage, DWORD RGB, int nKind, DWORD dwPStyle )
{
	if( pObj->GetType() == OT_MOVER )
	{
		CScanner scanner;
		scanner.SetProg( (LPVOID)lpszMessage );
		scanner.GetToken();

		// 이모티콘 명령
/*		
		if( scanner.Token == "/" )
		{			
			scanner.GetToken();

			CString strstr = scanner.token;
			for( int j=0; j < MAX_EMOTICON_NUM; j++ )
			{
				CString strstr2 = m_EmiticonCmd[ j ].m_szCommand;

				if( strstr == strstr2 )
				{
					AddEmoticonUser( pObj, m_EmiticonCmd[ j ].m_dwIndex );
					return;
				}
			}
		}
*/
		if( scanner.Token == "/" )
		{			
			CString strstr = lpszMessage;
			scanner.GetToken();
			for( int j=0; j < MAX_EMOTICON_NUM; j++ )
			{
				CString strstr2 = "/";
				strstr2+=m_EmiticonCmd[ j ].m_szCommand;
				if( strstr.GetLength() > 0 && strstr == strstr2 )
				{
					AddEmoticonUser( pObj, m_EmiticonCmd[ j ].m_dwIndex );
					return;
				}
			}
		}		
		else
		if( scanner.Token == "!" )
		{
			int nEmoticonIdx = scanner.GetNumber();
			AddEmoticon( pObj, nEmoticonIdx );
			return;
		}
		
		for( int i = 0; i < m_textArray.GetSize(); i++ )
		{
			LPCUSTOMTEXT lpCustomText = (LPCUSTOMTEXT) m_textArray.GetAt( i );
			if( lpCustomText->m_pObj == pObj )
			{
				safe_delete( lpCustomText );
				m_textArray.RemoveAt( i );
				break;
			}
		}
	}
	LPCUSTOMTEXT lpCustomText = new CUSTOMTEXT;
	lpCustomText->m_dwRGB = RGB;
	lpCustomText->m_pFont = CWndBase::m_Theme.m_pFontText; //ect ? m_pFontEffect : m_pFont;
	lpCustomText->m_pObj = pObj;
	lpCustomText->m_timer.Set( 5000 );
	lpCustomText->m_bInfinite	= FALSE;//( pObj->GetType() == OT_MOVER && ( (CMover*)pObj )->m_vtInfo.IsVendorOpen() );
	lpCustomText->m_pTexture = NULL;
	lpCustomText->m_nKind = nKind;

	// Mover라면 대사 출력 시간 동안 퀘스트 이모티콘을 감춘다.
	if( pObj->GetType() == OT_MOVER )
		((CMover*)pObj)->m_bShowQuestEmoticon = FALSE;

	if( lpCustomText->m_bInfinite )
	{
		DWORD dwColor = 0;
		dwColor = 0xff008000;
		lpCustomText->m_string.SetParsingString( lpszMessage, dwColor, 0x00000000, 0, dwPStyle );
	}
	else
		lpCustomText->m_string.SetParsingString( lpszMessage, 0xff000000, 0x00000000, 0, dwPStyle );

	int nMaxHeight = lpCustomText->m_pFont->GetMaxHeight();
	CSize size = lpCustomText->m_pFont->GetTextExtent( lpszMessage );
	int cx, cy;
	// 기본 사이즈 계산 
	if( size.cx >= 160 )
	{
		cx = 160;
		cy = 160; // 이 수치는 의미가 없음. Reset 이후에 줄수로 재 계산 됨
		
		lpCustomText->m_string.Init( lpCustomText->m_pFont, &CRect( 0, 0, cx - 16, cy - 16) );
	}
	else
	{
		cx = size.cx + 16; 
		cx = ( ( cx / 16 ) * 16 ) + ( ( cx % 16 ) ? 16 : 0 );
		cy = size.cy;// 이 수치는 의미가 없음. Reset 이후에 줄수로 재 계산 됨 
		lpCustomText->m_string.Init( lpCustomText->m_pFont, &CRect( 0, 0, cx - 16, cy - 16) );
	}


	cy = lpCustomText->m_string.GetLineCount() * nMaxHeight + 16; // 라인 줄수로 세로 길이를 구함 
	cy = ( ( cy / 16 ) * 16 ) + ( ( cy % 16 ) ? 16 : 0 );

	lpCustomText->m_rect = CRect( 0, 0, cx, cy );
	m_textArray.Add( lpCustomText );
}