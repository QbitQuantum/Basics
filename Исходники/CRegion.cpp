bool CRegionBase::r_Verb( CScript & s, CTextConsole * pSrc ) // Execute command from script
{
	ADDTOCALLSTACK("CRegionBase::r_Verb");
	EXC_TRY("Verb");
	LPCTSTR pszKey = s.GetKey();

	if ( !strnicmp(pszKey, "CLEARTAGS", 9) )
	{
		pszKey = s.GetArgStr();
		SKIP_SEPARATORS(pszKey);
		m_TagDefs.ClearKeys(pszKey);
		return true;
	}	

	int index = FindTableSorted(pszKey, sm_szVerbKeys, COUNTOF(sm_szVerbKeys) - 1);
	if ( index < 0 )
	{
		index = FindTableSorted(s.GetKey(), CSector::sm_szVerbKeys, SEV_QTY);
		if ( index >= 0 )
			return SendSectorsVerb(s.GetKey(), s.GetArgRaw(), pSrc);
	}

	switch ( static_cast<RV_TYPE>(index) )
	{
		case RV_ALLCLIENTS:
		{
			ClientIterator it;
			for (CClient* pClient = it.next(); pClient != NULL; pClient = it.next())
			{
				CChar * pChar = pClient->GetChar();
				if ( !pChar || (pChar->m_pArea != this) )
					continue;

				CScript script( s.GetArgStr() );
				pChar->r_Verb(script, pSrc);
			}
			return true;
		}
		case RV_TAGLIST:
		{
			m_TagDefs.DumpKeys( pSrc, "TAG." );
			return true;
		}

		default:
			break;
	}

	return CScriptObj::r_Verb(s, pSrc);
	EXC_CATCH;

	EXC_DEBUG_START;
	g_Log.EventDebug("command '%s' args '%s' [%p]\n", s.GetKey(), s.GetArgRaw(), static_cast<void *>(pSrc));
	EXC_DEBUG_END;
	return false;
}