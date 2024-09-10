BOOL TMonsterAIGroup::LoadData(LPSTR lpszFileName)
{
	TMonsterAIGroup::s_bDataLoad = FALSE;

	if ( !lpszFileName || !strcmp(lpszFileName, ""))
	{
		MsgBox("[Monster AI Group] - File load error : File Name Error");
		return FALSE;
	}

	try
	{
		SMDToken Token;
		SMDFile = fopen(lpszFileName, "r");	//ok

		if ( SMDFile == NULL )
		{
			MsgBox("[Monster AI Group] - Can't Open %s ", lpszFileName);
			return FALSE;
		}

		int iType = -1;

		while ( true )
		{
			Token = GetToken();

			if ( Token == END )
				break;

			iType = TokenNumber;

			while ( true )
			{
				if ( iType == 0 )
				{
					int iGroupNumber = -1;
					int iGuid = -1;
					int iClass = -1;
					int iRank = -1;
					int iStartAI = 0;
					int iAI01 = 0;
					int iAI02 = 0;
					int iAI03 = 0;
					int iCreateType = -1;
					int iMapNumber = -1;
					int iStartX = -1;
					int iStartY = -1;
					int iStartDir = -1;
					int iRegenType = -1;

					Token = GetToken();

					if ( !strcmp("end", TokenString))
						break;

					iGroupNumber = TokenNumber;

					Token = GetToken();
					iGuid = TokenNumber;

					Token = GetToken();
					iClass = TokenNumber;

					Token = GetToken();
					iRank = TokenNumber;

					Token = GetToken();
					iStartAI = TokenNumber;

					Token = GetToken();
					iAI01 = TokenNumber;

					Token = GetToken();
					iAI02 = TokenNumber;

					Token = GetToken();
					iAI03 = TokenNumber;

					Token = GetToken();
					iCreateType = TokenNumber;

					Token = GetToken();
					iMapNumber = TokenNumber;

					Token = GetToken();
					iStartX = TokenNumber;

					Token = GetToken();
					iStartY = TokenNumber;

					Token = GetToken();
					iStartDir = TokenNumber;

					Token = GetToken();
					iRegenType = TokenNumber;

					if ( iGroupNumber > MAX_MONSTER_AI_GROUP )
					{
						MsgBox("[Monster AI Group] Exceed Max GroupNumber %d",
							iGroupNumber);
						continue;
					}

					if ( iGuid > MAX_MONSTER_AI_GROUP_MEMBER)
					{
						MsgBox("[Monster AI Group] Exceed Max GroupMember %d, %d ",
							iGroupNumber, iGuid);
						continue;
					}

					TMonsterAIGroup::s_MonsterAIGroupMemberArray[iGroupNumber][iGuid].m_iGroupNumber = iGroupNumber;
					TMonsterAIGroup::s_MonsterAIGroupMemberArray[iGroupNumber][iGuid].m_iGuid = iGuid;
					TMonsterAIGroup::s_MonsterAIGroupMemberArray[iGroupNumber][iGuid].m_iClass = iClass;
					TMonsterAIGroup::s_MonsterAIGroupMemberArray[iGroupNumber][iGuid].m_iRank = iRank;
					TMonsterAIGroup::s_MonsterAIGroupMemberArray[iGroupNumber][iGuid].m_iStartAI = iStartAI;
					TMonsterAIGroup::s_MonsterAIGroupMemberArray[iGroupNumber][iGuid].m_iAI01 = iAI01;
					TMonsterAIGroup::s_MonsterAIGroupMemberArray[iGroupNumber][iGuid].m_iAI02 = iAI02;
					TMonsterAIGroup::s_MonsterAIGroupMemberArray[iGroupNumber][iGuid].m_iAI03 = iAI03;
					TMonsterAIGroup::s_MonsterAIGroupMemberArray[iGroupNumber][iGuid].m_iCreateType = iCreateType;
					TMonsterAIGroup::s_MonsterAIGroupMemberArray[iGroupNumber][iGuid].m_iMapNumber = iMapNumber;
					TMonsterAIGroup::s_MonsterAIGroupMemberArray[iGroupNumber][iGuid].m_iStartX = iStartX;
					TMonsterAIGroup::s_MonsterAIGroupMemberArray[iGroupNumber][iGuid].m_iStartY = iStartY;
					TMonsterAIGroup::s_MonsterAIGroupMemberArray[iGroupNumber][iGuid].m_iStartDir = iStartDir;
					TMonsterAIGroup::s_MonsterAIGroupMemberArray[iGroupNumber][iGuid].m_iRegenType = iRegenType;
					
					TMonsterAIGroup::s_iMonsterAIGroupMemberCount[iGroupNumber]++;
				}
			}
		}	// while ( true )

		fclose(SMDFile);

		LogAddC(2, "[Monster AI Group ] - %s file is Loaded", lpszFileName);

		TMonsterAIGroup::s_bDataLoad = TRUE;
	}
	catch ( DWORD )
	{
		MsgBox("[Monster AI Group] - Loading Exception Error (%s) File. ", lpszFileName);
	}

	return FALSE;
}