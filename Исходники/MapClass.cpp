void LoadMapSettings(LPSTR szFileName)
{
	if ( (SMDFile = fopen(szFileName, "r")) == NULL )	//ok
	{
		return;
	}

	SMDToken Token;
	int iType = 0;

	while ( true )
	{
		Token = GetToken();

		if (Token == END )
		{
			break;
		}

		iType = TokenNumber;

		while ( true )
		{
			Token = GetToken();

			if ( Token == END )
			{
				break;
			}

			if ( iType >= 0 && iType <= MAX_NUMBER_MAP-1)
			{
				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}
				
				int ExpSingleInc = 0;
				int ExpPartyInc = 0;
				int DropIncrease = 0;
				int DropExcIncrease = 0;

				ExpSingleInc = TokenNumber;
				
				Token = GetToken();
				ExpPartyInc = TokenNumber;

				Token = GetToken();
				DropIncrease =  TokenNumber;

				Token = GetToken();
				DropExcIncrease = TokenNumber;

				Token = GetToken();
				g_MAP_SETTINGS[iType].drop_zen_increase = TokenNumber;
			
				g_MAP_SETTINGS[iType].exp_increase = ExpSingleInc;
				g_MAP_SETTINGS[iType].exp_party_increase = ExpPartyInc;
				g_MAP_SETTINGS[iType].drop_increase = DropIncrease;
				g_MAP_SETTINGS[iType].drop_exc_increase = DropExcIncrease;
			}
		}
	}

	fclose(SMDFile);
}