void SetStrNull( TCHAR* lpStr, int nNullLength )
{
	int nLength = strlen( lpStr );
	// 0을 넣을 포지션이 실제 스트링 길이보다 길면 실제 스트링 길이로 맞출 필요가 있음
	if( nNullLength > nLength )
		nNullLength = nLength;
	int i; for( i = 0; i < nNullLength; )
	{
#ifdef __CLIENT
		if( ::GetLanguage() == LANG_THA && g_codePage == 874 ) // 타이 
			i++;
		else if(::GetLanguage() == LANG_VTN && g_codePage == 1258)
			i++;
		else
#endif//__CLIENT
		if( IsDBCSLeadByte( lpStr[ i ] ) )
			i+=2;
		else
			i++;
	}
	// i가 nLength 보다 크다면 Word캐릭터일 것이고, 끝부분이 깨져서 오차가 생긴 것이다.
	if( i > nNullLength )
		lpStr[ i - 2 ] = 0;
	else
		lpStr[ i ] = 0;
}