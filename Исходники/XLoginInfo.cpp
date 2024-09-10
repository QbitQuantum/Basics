BOOL XLoginInfo::Load( LPCTSTR szFile )
{
	CToken token;
	m_strLoginFile = szFile;
    // 플랫폼에 관계없이 이 함수로 대동단결
	if( token.LoadFromDoc( szFile, XE::TXT_EUCKR ) == xFAIL )
	{
		XLOGXN("login.txt not found");
		return FALSE;
	}
	XLOGXN("load login.txt success!");
	if( token.GetToken() == NULL )
		return FALSE;
#ifdef _XLOGIN_UUID
	if( token == _T("__none") )
	{
		// login파일이 없으면 디폴트 uuid방식으로 로그인
		m_typeLogin = xLT_UUID;
		XLOGXN("uuid not found. create uuid now.");
		char cUUID[ 48 ];
		XPH::GetUUID( cUUID, 48 );
		m_strUUID = cUUID;
		XLOGXN("UUID:%s", C2SZ( cUUID ) );
		Save();
	} else
	if( token == _T("__uuid") )
	{
		if( token.GetToken() )
			m_strUUID = SZ2C(token.m_Token);
		else
			return FALSE;	// 파일이 깨진것 앱을 다시 설치해야함.
		m_typeLogin = xLT_UUID;
	} else
#endif
#ifdef _XLOGIN_FACEBOOK
	if( token == _T("__facebook") )
	{
		if( token.GetToken() )
			m_strFbUserId = SZ2C(token.m_Token);
		else
			return FALSE;
		//
		if( token.GetToken() )
			m_strFbUsername = token.m_Token;
		else
		{
			// 페북에 유저네임이 없을수도 있게 되어서 에러로 처리하지 않음.
//			m_strFbUserId.clear();
//			return FALSE;
		}
		m_typeLogin = xLT_FACEBOOK;
	} else
#endif
#ifdef _XUNIVERSAL
	if( token == _T("__idpw") )
	{
		//
		if( token.GetToken() )
			m_strID = SZ2C( token.m_Token );
		XLOGXN("login id:%s", token.m_Token);
		//
		if( token.GetToken() )
			m_strPassword = SZ2C( token.m_Token );
		else
		{
			m_strID.clear();
			return FALSE;
		}
		m_typeLogin = xLT_IDPW;
  #ifdef _DEV
		XLOGXN("login pw:%s", token.m_Token);
  #endif
	} else
#endif 
	{
		m_typeLogin = xLT_NONE;
		XBREAKF( 1, "unknown login identifier:%s", token.m_Token );
		return FALSE;
	}
// add facebook login mode
//////////////////////////////////////////////////////////////////////////
	m_bLoaded = TRUE;
	return TRUE;
}