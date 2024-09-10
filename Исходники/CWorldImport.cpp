bool CImportFile::ImportWSC( CScript & s, word wModeFlags )
{
	ADDTOCALLSTACK("CImportFile::ImportWSC");
	// This file is a WSC or UOX world script file.

	IMPFLAGS_TYPE mode = IMPFLAGS_NOTHING;
	CSString sName;
	CItem * pItem = NULL;
	CChar * pChar = NULL;

	while ( s.ReadTextLine(true))
	{
		if ( s.IsKeyHead( "SECTION WORLDITEM", 17 ))
		{
			CheckLast();
			mode = IMPFLAGS_ITEMS;
			continue;
		}
		else if ( s.IsKeyHead( "SECTION CHARACTER", 17 ))
		{
			CheckLast();
			mode = ( wModeFlags & IMPFLAGS_CHARS ) ? IMPFLAGS_CHARS : IMPFLAGS_NOTHING;
			continue;
		}
		else if ( s.GetKey()[0] == '{' )
		{
			CheckLast();
			continue;
		}
		else if ( s.GetKey()[0] == '}' )
		{
			CheckLast();
			mode = IMPFLAGS_NOTHING;
			continue;
		}
		else if ( mode == IMPFLAGS_NOTHING )
			continue;
		else if ( s.GetKey()[0] == '\\' )
			continue;

		// Parse the line.
		tchar* pKey = const_cast<tchar*>(strchr(s.GetKey(), ' '));
		lpctstr pArg = NULL;

		if (pKey != NULL)
		{
			*pKey++ = '\0';
			GETNONWHITESPACE(pKey);
			pArg = pKey;
		}
		else
		{
			pArg = "";
		}

		if ( s.IsKey("SERIAL" ))
		{
			if ( m_pCurSer != NULL )
				return false;

			dword dwSerial = ATOI( pArg );
			if ( dwSerial == UID_UNUSED )
			{
				DEBUG_ERR(( "Import:Bad serial number\n" ));
				break;
			}
			m_pCurSer = new CImportSer( dwSerial );
			m_ListSer.InsertHead( m_pCurSer );
			continue;
		}
		if ( s.IsKey("NAME" ))
		{
			sName = ( pArg[0] == '#' ) ? "" : pArg;
			if ( mode == IMPFLAGS_ITEMS )
				continue;
		}
		if ( m_pCurSer == NULL )
		{
			DEBUG_ERR(( "Import:No serial number\n" ));
			break;
		}

		if ( mode == IMPFLAGS_ITEMS )	// CItem.
		{
			if ( s.IsKey("ID" ))
			{
				if ( m_pCurObj != NULL )
					return false;
				pItem = CItem::CreateTemplate(static_cast<ITEMID_TYPE>(ATOI(pArg)));
				pItem->SetName( sName );
				m_pCurObj = pItem;
				m_pCurSer->m_pObj = pItem;
				continue;
			}

			if ( m_pCurObj == NULL )
			{
				DEBUG_ERR(( "Import:Bad Item Key '%s'\n", s.GetKey()));
				break;
			}
			else if ( s.IsKey("CONT" ))
			{
				m_pCurSer->m_dwContSer = ATOI(pArg);
			}
			else if ( s.IsKey("LAYER" ))
			{
				m_pCurSer->m_layer = static_cast<LAYER_TYPE>(ATOI(pArg));
				continue;
			}
			else if (pItem == NULL)
			{
				DEBUG_ERR(( "Import:Found '%s' before ID.\n", s.GetKey()));
				continue;
			}

			if ( s.IsKey("X" ))
			{
				CPointMap pt = pItem->GetUnkPoint();
				pt.m_x = (short)( ATOI(pArg) );
				pItem->SetUnkPoint(pt);
				continue;
			}
			else if ( s.IsKey("Y" ))
			{
				CPointMap pt = pItem->GetUnkPoint();
				pt.m_y = (short)( ATOI(pArg) );
				pItem->SetUnkPoint(pt);
				continue;
			}
			else if ( s.IsKey("Z" ))
			{
				CPointMap pt = pItem->GetUnkPoint();
				pt.m_z = (char)( ATOI(pArg) );
				pItem->SetUnkPoint(pt);
				continue;
			}
			else if ( s.IsKey("COLOR" ))
			{
				pItem->SetHue( static_cast<HUE_TYPE>( ATOI(pArg) ) );
				continue;
			}
			else if ( s.IsKey("AMOUNT" ))
			{
				pItem->SetAmount( (word)ATOI(pArg) );
				continue;
			}
			else if ( s.IsKey("MOREX" ))
			{
				pItem->m_itNormal.m_morep.m_x = (short)(ATOI(pArg));
				continue;
			}
			else if ( s.IsKey("MOREY" ))
			{
				pItem->m_itNormal.m_morep.m_y = (short)(ATOI(pArg));
				continue;
			}
			else if ( s.IsKey("MOREZ" ))
			{
				pItem->m_itNormal.m_morep.m_z = (char)( ATOI(pArg) );
				continue;
			}
			else if ( s.IsKey("MORE" ))
			{
				pItem->m_itNormal.m_more1 = ATOI(pArg);
				continue;
			}
			else if ( s.IsKey("MORE2" ))
			{
				pItem->m_itNormal.m_more2 = ATOI(pArg);
				continue;
			}
			else if ( s.IsKey("DYEABLE" ))
			{
				//if ( ATOI(pArg))
				//	pItem->m_pDef->m_Can |= CAN_I_DYE;
				continue;
			}
			else if ( s.IsKey("ATT" ))
			{
				// pItem->m_pDef->m_attackBase = ATOI(pArg);
			}
			else if ( s.IsKey("TYPE" ))
			{
				// ??? translate the type field.
				//int i = ATOI(pArg);
			}
		}

		if ( mode == IMPFLAGS_CHARS )
		{
			if ( s.IsKey("NAME" ))
			{
				if ( m_pCurObj != NULL )
					return false;
				pChar = CChar::CreateBasic( CREID_MAN );
				pChar->SetName( sName );
				m_pCurObj = pChar;
				m_pCurSer->m_pObj = pChar;
				continue;
			}
			if ( m_pCurObj == NULL )
			{
				DEBUG_ERR(( "Import:Bad Item Key '%s'\n", s.GetKey()));
				break;
			}
			else if (pChar == NULL)
			{
				DEBUG_ERR(( "Import:Found '%s' before NAME.\n", s.GetKey()));
				continue;
			}

			if ( s.IsKey("X" ))
			{
				CPointMap pt = pChar->GetUnkPoint();
				pt.m_x = (short)(ATOI(pArg));
				pChar->SetUnkPoint(pt);
				continue;
			}
			else if ( s.IsKey("Y" ))
			{
				CPointMap pt = pChar->GetUnkPoint();
				pt.m_y = (short)(ATOI(pArg));
				pChar->SetUnkPoint(pt);
				continue;
			}
			else if ( s.IsKey("Z" ))
			{
				CPointMap pt = pChar->GetUnkPoint();
				pt.m_z = (char)(ATOI(pArg));
				pChar->SetUnkPoint(pt);
				continue;
			}
			else if ( s.IsKey("BODY" ))
			{
				pChar->SetID(static_cast<CREID_TYPE>(ATOI(pArg)));
				continue;
			}
			else if ( s.IsKey("SKIN" ))
			{
				pChar->SetHue( static_cast<HUE_TYPE>( ATOI(pArg) ));
				continue;
			}
			else if ( s.IsKey("DIR" ))
			{
				pChar->m_dirFace = static_cast<DIR_TYPE>(ATOI(pArg));
				if ( pChar->m_dirFace < 0 || pChar->m_dirFace >= DIR_QTY )
					pChar->m_dirFace = DIR_SE;
				continue;
			}
			else if ( s.IsKey("XBODY" ))
			{
				pChar->m_prev_id = static_cast<CREID_TYPE>(ATOI(pArg));
				continue;
			}
			else if ( s.IsKey("XSKIN" ))
			{
				pChar->m_prev_Hue = static_cast<HUE_TYPE>( ATOI(pArg) );
				continue;
			}
			else if ( s.IsKey("FONT" ))
			{
				pChar->m_fonttype = static_cast<FONT_TYPE>(ATOI(pArg));
				continue;
			}
			else if ( s.IsKey("KARMA" ))
			{
				pChar->Stat_SetBase(STAT_KARMA, (short)(ATOI(pArg)));
				continue;
			}
			else if ( s.IsKey("FAME" ))
			{
				pChar->Stat_SetBase(STAT_FAME, (short)(ATOI(pArg)));
				continue;
			}
			else if ( s.IsKey("TITLE" ))
			{
				pChar->m_sTitle = pArg;
				continue;
			}
			else if ( s.IsKey("STRENGTH" ))
			{
				pChar->Stat_SetBase(STAT_STR, (short)(ATOI(pArg)));
			}
			else if ( s.IsKey("DEXTERITY" ))
			{
				pChar->Stat_SetBase(STAT_DEX, (short)(ATOI(pArg)));
			}
			else if ( s.IsKey("INTELLIGENCE" ))
			{
				pChar->Stat_SetBase(STAT_INT, (short)(ATOI(pArg)));
			}
			else if ( s.IsKey("HITPOINTS" ))
			{
				pChar->Stat_SetVal(STAT_STR,(short)(ATOI(pArg)));
			}
			else if ( s.IsKey("STAMINA" ))
			{
				pChar->Stat_SetVal(STAT_DEX,(short)(ATOI(pArg)));
			}
			else if ( s.IsKey( "MANA" ))
			{
				pChar->Stat_SetVal(STAT_INT,(short)(ATOI(pArg)));
			}
			else if ( s.IsKeyHead( "SKILL", 5 ))
			{
				SKILL_TYPE skill = static_cast<SKILL_TYPE>(ATOI( &(s.GetKey()[5])));
				if ( pChar->IsSkillBase(skill) && g_Cfg.m_SkillIndexDefs.IsValidIndex(skill) )
				{
					pChar->Skill_SetBase( skill, ATOI(pArg));
				}
			}
			else if ( s.IsKey("ACCOUNT" ))
			{
				// What if the account does not exist ?
				pChar->SetPlayerAccount( pArg );
			}
			else if ( s.IsKey("KILLS" ) && pChar->m_pPlayer )
			{
				pChar->m_pPlayer->m_wMurders = (word)(ATOI(pArg));
			}
			else if ( s.IsKey("NPCAITYPE" ))
			{
				// Convert to proper NPC type.
				int i = ATOI( pArg );
				switch ( i )
				{
				case 0x01:	pChar->SetNPCBrain( NPCBRAIN_HEALER ); break;
				case 0x02:	pChar->SetNPCBrain( NPCBRAIN_MONSTER ); break;
				case 0x04:
				case 0x40:	pChar->SetNPCBrain( NPCBRAIN_GUARD ); break;
				case 0x08:	pChar->SetNPCBrain( NPCBRAIN_BANKER ); break;
				default:	pChar->SetNPCBrain( pChar->GetNPCBrain( false )); break;
				}
			}
			continue;
		}
	}
	return true;
}