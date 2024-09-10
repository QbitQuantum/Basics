//
// Constant.h를 읽어 #define name value들을 모두 메모리에 적재
// Load()를 연속적으로 읽는다면 m_nMaxDef부터 추가로 읽게 된다.
// ex)  Load( "constant1.h" );	0 ~ 300 인덱스
//      Load( "constant2.h" );	301 ~ 600 인덱스
XE::xRESULT CDefine::Load( LPCTSTR strFileName )
{
	CToken	Token;
	TCHAR szName[256];

	if( Token.LoadFile( strFileName, TXT_EUCKR ) == XE::xFAIL )
		return XE::xFAIL;
	while(1)
	{
		if( Token.GetToken() == NULL )	break;
		if( Token == _T("define") )
		{
			Token.GetToken();
			// ex) #define OBJECT_DAO	1
			if( Token.m_Token[0] != '_' )		// #define _HUHU같이 첫자가밑줄 붙은건 읽지 않음
			{
				_tcscpy_s( szName, Token.m_Token );
				int		nVal = Token.GetNumber();
				// 읽어 메모리로 올릴때는 주석을 읽지 않는다.  
				// Object.inc에 있는 NAME부분을 가지고 저장할때만 기록한다.
				if( XE::xFAIL == AddDefine( szName, nVal, Token.GetRemark() ) )			// define 추가
				{
					XERROR( "%s 읽던중 CDefine의 최대 버퍼%d를 넘었다", strFileName, MAX_DEFINE );
					break;
				}
			} else
				XLOG( "define %s skip", Token.m_Token );
		}
	}
	return XE::xSUCCESS;
}