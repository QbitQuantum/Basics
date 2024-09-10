BOOL CWndGuideSystem::LoadGuide( LPCTSTR lpszFileName )
{
	CScript script;
	if( script.Load( lpszFileName ) == FALSE )
		return FALSE;

	if(m_mapGuide.size() || m_vecEventGuide.size()) return FALSE;

	GUIDE_STRUCT guidestruct;

	script.tok = 0;
	
	while( script.tok != FINISHED )
	{
		guidestruct.init();
		guidestruct.m_nEventMsg = script.GetNumber();

		script.GetToken(); // {
		if( *script.token  == '{' )
		{
			script.GetToken(); // BEGINNER
			guidestruct.m_bBeginner = script.GetNumber();
			script.GetToken(); // SHOWLEVEL
			guidestruct.m_nShowLevel = script.GetNumber();
			script.GetToken(); // FLAG
			guidestruct.m_bFlag      = script.GetNumber();
			script.GetToken(); // KEY
			guidestruct.m_nkey = script.GetNumber();
			guidestruct.m_str = "";
			script.GetToken();
			guidestruct.m_str	= script.Token;
			script.GetToken();
			if( strcmpi( script.token, "SEQUENCE" ) == 0 )
			{
				guidestruct.m_nSequence = script.GetNumber();
				script.GetToken();
			}
			if( strcmpi( script.token, "LEVEL" ) == 0 )
			{
				guidestruct.m_nLevel = script.GetNumber();
				script.GetToken();
			}
			if( strcmpi( script.token, "CONDITION" ) == 0 )
			{
				guidestruct.m_nVicCondition = script.GetNumber();
				script.GetToken();
			}
			if( strcmpi( script.token, "INPUTCHAR" ) == 0 )
			{
				guidestruct.m_nInput = script.GetNumber();
				script.GetToken();
			}
			if( strcmpi( script.token, "INPUTSTR" ) == 0 )
			{
				script.GetToken();
				guidestruct.m_strInput = script.Token;
				script.GetToken();	// }
				while(*script.token  != '}')
				{
					guidestruct.m_strInput.Format("%s%s", guidestruct.m_strInput, script.token);
					script.GetToken();	// }
				}
			}
			if(guidestruct.m_nSequence != 0)
				m_mapGuide.insert(mgValType(guidestruct.m_nSequence, guidestruct));
			else
				m_vecEventGuide.push_back(guidestruct);
		}
		else
			script.GetToken();
	}
	
	m_bIsLoad = TRUE;
	
	return TRUE;
}