BOOL CItemSystemFor380::Load380ItemOptionInfo(LPSTR filename)
{
	enum SMDToken Token;
	if (fopen_s(&SMDFile,filename, "r") != 0 )
	{
		return FALSE;
	}

	this->_InitOption();


	while ( true )
	{
		Token = (SMDToken)GetToken();

		if ( Token == END )
			break;

		if ( Token == NUMBER )
		{
			int Index = (int)TokenNumber;

			while ( true )
			{
				Token = (SMDToken)GetToken();
				int _type = (int)TokenNumber;

				if ( Token == NAME )
				{
					if ( !strcmp("end", TokenString))
					{
						break;
					}
				}

				Token = (SMDToken)GetToken();
				int _index = (int)TokenNumber;

				ITEMOPTION_FOR380ITEM * p = &this->m_itemOption[ITEMGET(_type, _index)];
				p->IsLoad = TRUE;
				p->m_Type = _type;
				p->m_Index = _index;

				Token = (SMDToken)GetToken();
				p->m_Option1 = (BYTE)TokenNumber;

				Token = (SMDToken)GetToken();
				p->m_Value1 = (WORD)TokenNumber;

				Token = (SMDToken)GetToken();
				p->m_Option2 = (BYTE)TokenNumber;

				Token = (SMDToken)GetToken();
				p->m_Value2 = (WORD)TokenNumber;

				Token = (SMDToken)GetToken();
				int iTime = (int)TokenNumber;
			}
		}
	}
	fclose(SMDFile);
	return TRUE;
}