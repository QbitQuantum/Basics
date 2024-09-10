bool CWebPageDef::r_Verb( CScript & s, CTextConsole * pSrc )	// some command on this object as a target
{
	ADDTOCALLSTACK("CWebPageDef::r_Verb");
	EXC_TRY("Verb");
	ASSERT(pSrc);
	sm_iListIndex = 0;
	TCHAR *pszTmp2 = Str_GetTemp();

	WV_TYPE iHeadKey = (WV_TYPE) FindTableSorted( s.GetKey(), sm_szVerbKeys, COUNTOF(sm_szVerbKeys)-1 );
	switch ( iHeadKey )
	{
		case WV_WEBPAGE:
		{
			// serv a web page to the pSrc
			CClient *pClient = dynamic_cast<CClient *>(pSrc);
			if ( !pClient )
				return false;
			return ServPage(pClient, s.GetArgStr(), NULL);
		}
	
		case WV_CLIENTLIST:
		{
			ClientIterator it;
			for ( CClient *pClient = it.next(); pClient != NULL; pClient = it.next() )
			{
				CChar *pChar = pClient->GetChar();
				if ( !pChar )
					continue;
				if ( pChar->IsStatFlag(STATF_Insubstantial) && (pClient->GetPrivLevel() > PLEVEL_Player) )
					continue;

				sm_iListIndex++;

				LPCTSTR pszArgs = s.GetArgStr();
				if ( pszArgs[0] == '\0' )
					pszArgs = "<tr><td>%NAME%</td><td>%REGION.NAME%</td></tr>\n";
				strcpy(pszTmp2, pszArgs);
				pChar->ParseText(Str_MakeFiltered(pszTmp2), &g_Serv, 1);
				pSrc->SysMessage(pszTmp2);
			}
			break;
		}
	
		case WV_GUILDLIST:
		case WV_TOWNLIST:
		{
			if ( !s.HasArgs() )
				return false;

			IT_TYPE	needtype = (iHeadKey == WV_GUILDLIST) ? IT_STONE_GUILD : IT_STONE_TOWN;

			for ( size_t i = 0; i < g_World.m_Stones.GetCount(); i++ )
			{
				CItemStone *pStone = g_World.m_Stones[i];
				if ( !pStone || !pStone->IsType(needtype) )
					continue;

				sm_iListIndex++;

				strcpy(pszTmp2, s.GetArgStr());
				pStone->ParseText(Str_MakeFiltered(pszTmp2), &g_Serv, 1);
				pSrc->SysMessage(pszTmp2);
			}
			break;
		}

		case WV_GMPAGELIST:
		{
			if ( !s.HasArgs() )
				return false;
			CGMPage *pPage = static_cast<CGMPage *>(g_World.m_GMPages.GetHead());
			for ( ; pPage != NULL; pPage = pPage->GetNext() )
			{
				sm_iListIndex++;
				strcpy(pszTmp2, s.GetArgStr());
				pPage->ParseText(Str_MakeFiltered(pszTmp2), &g_Serv, 1);
				pSrc->SysMessage(pszTmp2);
			}
			break;
		}
	
		default:
			return CResourceLink::r_Verb(s, pSrc);
	}
	return true;
	EXC_CATCH;

	EXC_DEBUG_START;
	EXC_ADD_SCRIPTSRC;
	EXC_DEBUG_END;
	return false;
}