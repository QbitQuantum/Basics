//005b4500	->
int CSetItemOption::LoadTypeInfo(LPSTR Buffer, int iSize)
{
	CWzMemScript WzMemScript;
	int i;
	int Token;

	WzMemScript.SetBuffer(Buffer, iSize);

	memset(this->m_SetItemTypeInfo , -1, sizeof(this->m_SetItemTypeInfo) );

	for ( i=0; i<MAX_ITEMS; i++)
	{
		this->m_SetItemTypeInfo[i].IsLoad =FALSE;
	}
	
	while ( true )
	{
		int number;
		
		Token=WzMemScript.GetToken();
		if (Token == 2)
		{
			break;
		}

		if (Token == 1)
		{
			number = WzMemScript.GetNumber();
			
			while ( true )
			{
				int number2;
				LPSETITEM_TYPEINFO pointer;

				Token = WzMemScript.GetToken();
				number2=WzMemScript.GetNumber();
				if ( ( Token== 0) && (strcmp("end", WzMemScript.GetString() )== 0))
				{
					break;
				}
				else
				{
					pointer = &this->m_SetItemTypeInfo[number*MAX_SUBTYPE_ITEMS+number2];

					Token=WzMemScript.GetToken();
					pointer->OptionIndex[0]=WzMemScript.GetNumber();
					Token=WzMemScript.GetToken();
					pointer->OptionIndex[1]=WzMemScript.GetNumber();
					Token=WzMemScript.GetToken();
					pointer->ChaosMixLevel[0]=WzMemScript.GetNumber();
					Token=WzMemScript.GetToken();
					pointer->ChaosMixLevel[1]=WzMemScript.GetNumber();

					pointer->IsLoad=TRUE;
				}
			}
		}
		
	}

	return 1;
}