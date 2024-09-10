//로그 찍기
VOID cLogMgr::AddLog( char* strmsg, ... )
{

	char szBuff[4096];
	char szDate[128];		//날짜
	char szTime[128];		//시간

	_strdate_s( szDate, 128 );
	_strtime_s( szTime, 128 );
	vsprintf_s( szBuff, strmsg, (char*)(&strmsg+1) );

	//Console에 출력할 경우
	if( m_nTarget & LOG_CONSOLE )
	{
		printf( "(data[%s] time[%s] ) : %s\n", szDate, szTime, szBuff );
	}

	//FILE 에 출력 할경우
	if( m_nTarget & LOG_FILE )
	{
		LogFile( "(data[%s] time[%s] ) : %s\n", szDate, szTime, szBuff );
	}

	//LOG 윈도우에 출력할 경우 ( 디버그 모드에서만 지원
#ifdef _DEBUG

	if( m_nTarget & LOG_WINDOW )
	{
		//윈도우 리스트 박스에 로그 추가
		SendMessage( m_hWndListBox, LB_ADDSTRING, 0, (LPARAM)szBuff );

		//추가된 리스트 박스의 순번 얻기 (마지막을 선택하면 된다 )
		UINT32 n = SendMessage( m_hWndListBox, LB_GETCOUNT, 0, 0 ) - 1;

		//선택 커서 마지막으로
		SendMessage( m_hWndListBox, LB_SETCURSEL, (WPARAM)n, 0 );
	}

#endif //_DEBUG
}