bool CCharPlayer::r_LoadVal( CChar * pChar, CScript &s )
{
	ADDTOCALLSTACK("CCharPlayer::r_LoadVal");
	EXC_TRY("LoadVal");
	
	LPCTSTR pszKey = s.GetKey();

	if ( !strnicmp(pszKey, "GMPAGE", 6) )		//	GM pages
	{
		pszKey += 6;
		if ( *pszKey == '.' )						//	GMPAGE.*
		{
			SKIP_SEPARATORS(pszKey);
			size_t index = Exp_GetVal(pszKey);
			if ( index >= g_World.m_GMPages.GetCount() )
				return false;

			CGMPage* pPage = STATIC_CAST <CGMPage*> (g_World.m_GMPages.GetAt(index));
			if ( pPage == NULL )
				return false;

			SKIP_SEPARATORS(pszKey);
			if ( !strcmpi(pszKey, "HANDLE") )
			{
				CChar *ppChar = pChar;
				LPCTSTR pszArgs = s.GetArgStr(); //Moved here because of error with quoted strings!?!?
				if ( *pszArgs )
					ppChar = dynamic_cast<CChar*>(g_World.FindUID(s.GetArgVal()));

				if ( ppChar == NULL )
					return false;

				CClient *pClient = ppChar->GetClient();
				if ( pClient == NULL )
					return false;

				pPage->SetGMHandler(pClient);
			}
			else if ( !strcmpi(pszKey, "DELETE") )
			{
				delete pPage;
			}
			else if ( pPage->FindGMHandler() )
			{
				CClient* pClient = pChar->GetClient();
				if ( pClient != NULL && pClient->GetChar() != NULL )
					pClient->Cmd_GM_PageCmd(pszKey);
			}
			else
			{
				return false;
			}

			return true;
		}
		return false;
	}
	else if ( ( !strnicmp(pszKey, "GUILD", 5) ) || ( !strnicmp(pszKey, "TOWN", 4) ) )
	{
		bool bIsGuild = !strnicmp(pszKey, "GUILD", 5);
		pszKey += bIsGuild ? 5 : 4;
		if ( *pszKey == '.' )
		{
			pszKey += 1;
			CItemStone *pMyGuild = pChar->Guild_Find(bIsGuild ? MEMORY_GUILD : MEMORY_TOWN);
			if ( pMyGuild ) return pMyGuild->r_SetVal(pszKey, s.GetArgRaw());
		}
		return false;
	}

	switch ( FindTableHeadSorted( s.GetKey(), sm_szLoadKeys, COUNTOF( sm_szLoadKeys )-1 ))
	{
		case CPC_DEATHS:
			m_wDeaths = static_cast<WORD>(s.GetArgVal());
			return true;
		case CPC_DSPEECH:
			return( m_Speech.r_LoadVal( s, RES_SPEECH ));
		case CPC_KILLS:
			m_wMurders = static_cast<WORD>(s.GetArgVal());
			pChar->NotoSave_Update();
			return true;
		case CPC_KRTOOLBARSTATUS:
			m_bKrToolbarEnabled = ( s.GetArgVal() != 0 );
			if ( pChar->IsClient() )
				pChar->GetClient()->addKRToolbar( m_bKrToolbarEnabled );
			return true;
		case CPC_LASTUSED:
			m_timeLastUsed = CServTime::GetCurrentTime() - ( s.GetArgVal() * TICK_PER_SEC );
			return( true );
		case CPC_PFLAG:
			{
				m_pflag = s.GetArgVal();
			} return( true );
		case CPC_PROFILE:
			m_sProfile = Str_MakeFiltered( s.GetArgStr());
			return( true );
		case CPC_REFUSETRADES:
			pChar->SetDefNum(s.GetKey(), s.GetArgVal() > 0 ? 1 : 0, false);
			return( true );
		case CPC_SKILLCLASS:
			return SetSkillClass( pChar, g_Cfg.ResourceGetIDType( RES_SKILLCLASS, s.GetArgStr()));
		case CPC_SKILLLOCK:
			{
				SKILL_TYPE skill = Skill_GetLockType( s.GetKey());
				if ( skill <= SKILL_NONE )
					return false;
				int bState = s.GetArgVal();
				if ( bState < SKILLLOCK_UP || bState > SKILLLOCK_LOCK )
					return false;
				Skill_SetLock(skill, static_cast<SKILLLOCK_TYPE>(bState));
			} return true;
		case CPC_SPEEDMODE:
			{
				m_speedMode = static_cast<unsigned short>(s.GetArgVal());
				pChar->UpdateSpeedMode();
			} return true;
		case CPC_STATLOCK:
			{
				STAT_TYPE stat = Stat_GetLockType( s.GetKey());
				if (( stat <= STAT_NONE ) || ( stat >= STAT_BASE_QTY ))
					return false;
				int bState = s.GetArgVal();
				if ( bState < SKILLLOCK_UP || bState > SKILLLOCK_LOCK )
					return false;
				Stat_SetLock(stat, static_cast<SKILLLOCK_TYPE>(bState));
			} return true;

		default:
			// Just ignore any NPC type stuff.
			if ( FindTableSorted( s.GetKey(), CCharNPC::sm_szLoadKeys, COUNTOF( CCharNPC::sm_szLoadKeys )-1 ) >= 0 )
			{
				return( true );
			}
			return( false );
	}
	EXC_CATCH;

	EXC_DEBUG_START;
	EXC_ADD_SCRIPT;
	EXC_DEBUG_END;
	return false;
}