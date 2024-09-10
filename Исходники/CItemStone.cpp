bool CItemStone::r_LoadVal( CScript & s ) // Load an item Script
{
	ADDTOCALLSTACK("CItemStone::r_LoadVal");
	EXC_TRY("LoadVal");

	switch ( FindTableSorted( s.GetKey(), sm_szLoadKeys, COUNTOF( sm_szLoadKeys )-1 ))
	{
		case STC_ABBREV: // "ABBREV"
			m_sAbbrev = s.GetArgStr();
			return true;
		case STC_ALIGN: // "ALIGN"
			SetAlignType(static_cast<STONEALIGN_TYPE>(s.GetArgVal()));
			return true;
		case STC_MasterUid:
			{
				if ( s.HasArgs() )
				{
					CGrayUID pNewMasterUid = (DWORD) s.GetArgVal();
					CChar * pChar = pNewMasterUid.CharFind();
					if ( !pChar )
					{
						DEBUG_ERR(( "MASTERUID called on non char 0%lx uid.\n", (DWORD)pNewMasterUid ));
						return( false );
					}

					CStoneMember * pNewMaster = GetMember( pChar );
					if ( !pNewMaster )
					{
						DEBUG_ERR(( "MASTERUID called on char 0%lx (%s) that is not a valid member of stone with 0x%lx uid.\n", (DWORD)pNewMasterUid, pChar->GetName(), (DWORD)GetUID() ));
						return( false );
					}

					CStoneMember * pMaster = GetMasterMember();
					if ( pMaster )
					{
						if ( pMaster->GetLinkUID() == pNewMasterUid )
							return( true );

						pMaster->SetPriv(STONEPRIV_MEMBER);
						//pMaster->SetLoyalTo(pChar);
					}

					//pNewMaster->SetLoyalTo(pChar);
					pNewMaster->SetPriv(STONEPRIV_MASTER);
				}
				else
				{
					DEBUG_ERR(( "MASTERUID called without arguments.\n" ));
					return( false );
				}
			}
			return( true );
		case STC_MEMBER: // "MEMBER"
			{
			TCHAR *Arg_ppCmd[8];		// Maximum parameters in one line
			size_t Arg_Qty = Str_ParseCmds( s.GetArgStr(), Arg_ppCmd, COUNTOF( Arg_ppCmd ), "," );
			if (Arg_Qty < 1) // must at least provide the member uid
				return false;

			new CStoneMember(
				this,
				ahextoi(Arg_ppCmd[0]),													// Member's UID
				Arg_Qty > 2 ? static_cast<STONEPRIV_TYPE>(ATOI(Arg_ppCmd[2])) : STONEPRIV_CANDIDATE,	// Members priv level (use as a type)
				Arg_Qty > 1 ? Arg_ppCmd[1] : "",										// Title
				ahextoi(Arg_ppCmd[3]),													// Member is loyal to this
				Arg_Qty > 4 ? (ATOI( Arg_ppCmd[4] ) != 0) : 0,							// Paperdoll stone abbreviation (also if they declared war)
				Arg_Qty > 5 ? (ATOI( Arg_ppCmd[5] ) != 0) : 0,							// If we declared war
				Arg_Qty > 6 ? ATOI( Arg_ppCmd[6] ) : 0);								// AccountGold
			}
			return true;
		case STC_WEBPAGE: // "WEBPAGE"
			m_sWebPageURL = s.GetArgStr();
			return true;
	}

	if ( s.IsKeyHead( sm_szLoadKeys[STC_CHARTER], 7 ))
	{
		unsigned int i = ATOI(s.GetKey() + 7);
		if ( i >= COUNTOF(m_sCharter))
			return( false );
		m_sCharter[i] = s.GetArgStr();
		return( true );
	}
	
	return CItem::r_LoadVal(s);
	EXC_CATCH;

	EXC_DEBUG_START;
	EXC_ADD_SCRIPT;
	EXC_DEBUG_END;
	return false;
}