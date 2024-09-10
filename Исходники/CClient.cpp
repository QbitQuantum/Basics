bool CClient::r_Verb(CScript &s, CTextConsole *pSrc) // Execute command from script
{
	ADDTOCALLSTACK("CClient::r_Verb");
	EXC_TRY("Verb");
	// NOTE: This can be called directly from a RES_WEBPAGE script.
	//  So do not assume we are a game client !
	// NOTE: Mostly called from CChar::r_Verb
	// NOTE: Little security here so watch out for dangerous scripts !

	ASSERT(pSrc);
	LPCTSTR pszKey = s.GetKey();

	// Old ver
	if ( s.IsKeyHead("SET", 3) && !g_Cfg.m_Functions.ContainsKey(pszKey) )
	{
		PLEVEL_TYPE ilevel = g_Cfg.GetPrivCommandLevel("SET");
		if ( ilevel > GetPrivLevel() )
			return false;

		ASSERT(m_pChar);
		addTargetVerb(pszKey + 3, s.GetArgRaw());
		return true;
	}

	if ( (toupper(pszKey[0]) == 'X') && !g_Cfg.m_Functions.ContainsKey(pszKey) )
	{
		PLEVEL_TYPE ilevel = g_Cfg.GetPrivCommandLevel("SET");
		if ( ilevel > GetPrivLevel() )
			return false;

		// Target this command verb on some other object.
		ASSERT(m_pChar);
		addTargetVerb(pszKey + 1, s.GetArgRaw());
		return true;
	}

	int index = FindTableSorted(s.GetKey(), sm_szVerbKeys, COUNTOF(sm_szVerbKeys) - 1);
	switch ( index )
	{
		case CV_ADD:
		{
			if ( s.HasArgs() )
			{
				TCHAR *ppArgs[2];
				size_t iArgQty = Str_ParseCmds(s.GetArgStr(), ppArgs, COUNTOF(ppArgs));

				if ( !IsValidGameObjDef(static_cast<LPCTSTR>(ppArgs[0])) )
				{
					g_Log.EventWarn("Invalid ADD argument '%s'\n", ppArgs[0]);
					SysMessageDefault(DEFMSG_CMD_INVALID);
					return true;
				}

				RESOURCE_ID rid = g_Cfg.ResourceGetID(RES_QTY, const_cast<LPCTSTR &>(ppArgs[0]));
				m_tmAdd.m_id = rid.GetResIndex();
				m_tmAdd.m_amount = (iArgQty > 1) ? static_cast<WORD>(maximum(ATOI(ppArgs[1]), 1)) : 1;

				if ( (rid.GetResType() == RES_CHARDEF) || (rid.GetResType() == RES_SPAWN) )
				{
					m_Targ_PrvUID.InitUID();
					return addTargetChars(CLIMODE_TARG_ADDCHAR, static_cast<CREID_TYPE>(m_tmAdd.m_id), false);
				}
				else
					return addTargetItems(CLIMODE_TARG_ADDITEM, static_cast<ITEMID_TYPE>(m_tmAdd.m_id));
				break;
			}

			if ( IsValidDef("d_add") )
				Dialog_Setup(CLIMODE_DIALOG, g_Cfg.ResourceGetIDType(RES_DIALOG, "d_add"), 0, m_pChar);
			else
				Menu_Setup(g_Cfg.ResourceGetIDType(RES_MENU, "MENU_ADDITEM"));
			break;
		}
		case CV_ADDBUFF:
		{
			TCHAR *ppArgs[11];
			Str_ParseCmds(s.GetArgStr(), ppArgs, COUNTOF(ppArgs));

			int iArgs[4];
			for ( int i = 0; i < 4; ++i )
			{
				if ( !IsStrNumeric(ppArgs[i]) )
				{
					DEBUG_ERR(("Invalid AddBuff argument number %u\n", i + 1));
					return true;
				}
				iArgs[i] = Exp_GetVal(ppArgs[i]);
			}
			if ( (iArgs[0] < 0) || (iArgs[0] > USHRT_MAX) )
			{
				DEBUG_ERR(("Invalid AddBuff icon ID\n"));
				break;
			}

			LPCTSTR pszArgs[7];
			size_t iArgQty = 0;
			for ( int i = 0; i < 7; ++i )
			{
				pszArgs[i] = ppArgs[i + 4];
				if ( pszArgs[i] != NULL )
					++iArgQty;
			}

			addBuff(static_cast<BUFF_ICONS>(iArgs[0]), static_cast<DWORD>(iArgs[1]), static_cast<DWORD>(iArgs[2]), static_cast<WORD>(iArgs[3]), pszArgs, iArgQty);
			break;
		}
		case CV_REMOVEBUFF:
		{
			BUFF_ICONS IconId = static_cast<BUFF_ICONS>(s.GetArgVal());
			if ( (IconId < 0) || (IconId > USHRT_MAX) )
			{
				DEBUG_ERR(("Invalid RemoveBuff icon ID\n"));
				break;
			}
			removeBuff(IconId);
			break;
		}
		case CV_ADDCLILOC:
		{
			// Add cliloc in @ClientTooltip trigger
			TCHAR *ppArgs[256];
			size_t iArgQty = Str_ParseCmds(s.GetArgRaw(), ppArgs, COUNTOF(ppArgs), ",");
			DWORD dwClilocId = static_cast<DWORD>(Exp_GetLLVal(ppArgs[0]));

			CGString sVal;
			for ( size_t i = 1; i < iArgQty; ++i )
			{
				if ( sVal.GetLength() )
					sVal += "\t";
				sVal += !strcmp(ppArgs[i], "NULL") ? " " : ppArgs[i];
			}

			if ( g_Cfg.m_wDebugFlags & DEBUGF_SCRIPTS )
				g_Log.EventDebug("SCRIPT: addcliloc(%lu,'%s')\n", dwClilocId, static_cast<LPCTSTR>(sVal));
			m_TooltipData.Add(new CClientTooltip(dwClilocId, sVal));
			break;
		}
		case CV_ADDCONTEXTENTRY:
		{
			TCHAR *ppArgs[20];
			if ( Str_ParseCmds(s.GetArgRaw(), ppArgs, COUNTOF(ppArgs), ",") > 4 )
			{
				DEBUG_ERR(("Bad AddContextEntry usage: Function takes maximum of 4 arguments!\n"));
				return true;
			}
			if ( !m_pPopupPacket )
			{
				DEBUG_ERR(("Bad AddContextEntry usage: Not used under a @ContextMenuRequest/@itemContextMenuRequest trigger!\n"));
				return true;
			}

			for ( int i = 0; i < 4; ++i )
			{
				if ( (i > 1) && IsStrEmpty(ppArgs[i]) )
					continue;

				if ( !IsStrNumeric(ppArgs[i]) )
				{
					DEBUG_ERR(("Bad AddContextEntry usage: Argument %d must be a number!\n", i + 1));
					return true;
				}
			}

			int iTextEntry = Exp_GetVal(ppArgs[0]);
			if ( iTextEntry < 100 )
			{
				DEBUG_ERR(("Bad AddContextEntry usage: TextEntry < 100 is reserved for server usage!\n"));
				return true;
			}
			m_pPopupPacket->addOption(static_cast<WORD>(iTextEntry), static_cast<DWORD>(Exp_GetLLVal(ppArgs[1])), static_cast<WORD>(Exp_GetLLVal(ppArgs[2])), static_cast<WORD>(Exp_GetLLVal(ppArgs[3])));
			break;
		}
		case CV_ARROWQUEST:
		{
			INT64 piVal[3];
			Str_ParseCmds(s.GetArgRaw(), piVal, COUNTOF(piVal));
			addArrowQuest(static_cast<WORD>(piVal[0]), static_cast<WORD>(piVal[1]), static_cast<DWORD>(piVal[2]));
			break;
		}
		case CV_BADSPAWN:
		{
			// Loop the world searching for bad spawns
			bool fFound = false;
			CItem *pItem = NULL;
			CSector *pSector = NULL;
			CResourceDef *pSpawnDef = NULL;
			for ( int m = 0; (m < 256) && !fFound; ++m )
			{
				if ( !g_MapList.m_maps[m] )
					continue;

				for ( int s = 0; (s < g_MapList.GetSectorQty(m)) && !fFound; ++s )
				{
					pSector = g_World.GetSector(m, s);
					if ( !pSector )
						continue;

					for ( pItem = static_cast<CItem *>(pSector->m_Items_Timer.GetHead()); (pItem != NULL) && !fFound; pItem = pItem->GetNext() )
					{
						if ( pItem->IsType(IT_SPAWN_ITEM) || pItem->IsType(IT_SPAWN_CHAR) )
						{
							pSpawnDef = static_cast<CItemSpawn *>(pItem)->FixDef();
							if ( !pSpawnDef )
							{
								RESOURCE_ID_BASE rid = pItem->IsType(IT_SPAWN_ITEM) ? pItem->m_itSpawnItem.m_ItemID : pItem->m_itSpawnChar.m_CharID;
								CPointMap pt = pItem->GetTopPoint();
								m_pChar->Spell_Teleport(pt, true, false);
								m_pChar->m_Act_Targ = pItem->GetUID();
								SysMessagef("Bad spawn (0%lx, id=%s). Set as ACT", static_cast<DWORD>(pItem->GetUID()), g_Cfg.ResourceGetName(rid));
								fFound = true;
							}
						}
					}
				}
			}
			if ( !fFound )
				SysMessage(g_Cfg.GetDefaultMsg(DEFMSG_NO_BAD_SPAWNS));
			break;
		}
		case CV_BANKSELF:
		{
			addBankOpen(m_pChar, LAYER_BANKBOX);
			break;
		}
		case CV_CAST:
		{
			SPELL_TYPE spell = static_cast<SPELL_TYPE>(g_Cfg.ResourceGetIndexType(RES_SPELL, s.GetArgStr()));
			const CSpellDef *pSpellDef = g_Cfg.GetSpellDef(spell);
			if ( !pSpellDef )
				return true;

			CObjBase *pObjSrc = dynamic_cast<CObjBase *>(pSrc);
			if ( IsSetMagicFlags(MAGICF_PRECAST) && !pSpellDef->IsSpellType(SPELLFLAG_NOPRECAST) )
			{
				int iSkill;
				if ( !pSpellDef->GetPrimarySkill(&iSkill, NULL) )
					return true;

				m_tmSkillMagery.m_Spell = spell;	// m_atMagery.m_Spell
				m_pChar->m_atMagery.m_Spell = spell;
				if ( pObjSrc )
				{
					m_Targ_UID = pObjSrc->GetUID();	// default target.
					m_Targ_PrvUID = pObjSrc->GetUID();
				}
				else
				{
					m_Targ_UID.ClearUID();
					m_Targ_PrvUID.ClearUID();
				}
				m_pChar->Skill_Start(static_cast<SKILL_TYPE>(iSkill));
				break;
			}
			else
				Cmd_Skill_Magery(spell, pObjSrc);
			break;
		}
		case CV_CHANGEFACE:		// open 'face selection' dialog (enhanced clients only)
		{
			addGumpDialog(CLIMODE_DIALOG, NULL, 0, NULL, 0, 0, 0, m_pChar, CLIMODE_DIALOG_FACESELECTION);
			break;
		}
		case CV_CHARLIST:		// usually just a gm command
		{
			if ( !PacketChangeCharacter::CanSendTo(m_NetState) )
				break;
			new PacketChangeCharacter(this);
			CharDisconnect();	// since there is no undoing this in the client.
			SetTargMode(CLIMODE_SETUP_CHARLIST);
			break;
		}
		case CV_CTAGLIST:
		{
			if ( !strcmpi(s.GetArgStr(), "log") )
				pSrc = &g_Serv;
			m_TagDefs.DumpKeys(pSrc, "CTAG.");
			break;
		}
		case CV_CLEARCTAGS:
		{
			if ( s.HasArgs() )
			{
				LPCTSTR pszArgs = s.GetArgStr();
				SKIP_SEPARATORS(pszArgs);
				m_TagDefs.ClearKeys(pszArgs);
			}
			else
				m_TagDefs.ClearKeys();
			break;
		}
		case CV_CLOSEPAPERDOLL:
		{
			const CChar *pChar = s.HasArgs() ? static_cast<CGrayUID>(s.GetArgVal()).CharFind() : m_pChar;
			if ( pChar )
				closeUIWindow(pChar, 0x1);
			break;
		}
		case CV_CLOSEPROFILE:
		{
			const CChar *pChar = s.HasArgs() ? static_cast<CGrayUID>(s.GetArgVal()).CharFind() : m_pChar;
			if ( pChar )
				closeUIWindow(pChar, 0x8);
			break;
		}
		case CV_CLOSESTATUS:
		{
			const CChar *pChar = s.HasArgs() ? static_cast<CGrayUID>(s.GetArgVal()).CharFind() : m_pChar;
			if ( pChar )
				closeUIWindow(pChar, 0x2);
			break;
		}
		case CV_CODEXOFWISDOM:
		{
			INT64 piArgs[2];
			size_t iArgQty = Str_ParseCmds(s.GetArgStr(), piArgs, COUNTOF(piArgs));
			if ( iArgQty < 1 )
			{
				SysMessage("Usage: CODEXOFWISDOM TopicID [ForceOpen]");
				break;
			}

			addCodexOfWisdom(static_cast<DWORD>(piArgs[0]), static_cast<bool>(piArgs[1]));
			break;
		}
		case CV_DYE:
		{
			const CObjBase *pObj = s.HasArgs() ? static_cast<CGrayUID>(s.GetArgVal()).ObjFind() : NULL;
			if ( pObj )
				addDyeOption(pObj);
			break;
		}
		case CV_EVERBTARG:
		{
			m_Prompt_Text = s.GetArgStr();
			addPromptConsole(CLIMODE_PROMPT_TARG_VERB, m_Targ_Text.IsEmpty() ? "Enter the verb" : "Enter the text", m_Targ_UID);
			break;
		}
		case CV_EXTRACT:
		{
			// sort of like EXPORT but for statics.
			// Opposite of the "UNEXTRACT" command
			TCHAR *ppArgs[2];
			size_t iArgQty = Str_ParseCmds(s.GetArgStr(), ppArgs, COUNTOF(ppArgs));
			if ( iArgQty < 2 )
			{
				SysMessage(g_Cfg.GetDefaultMsg(DEFMSG_EXTRACT_USAGE));
				break;
			}

			m_Targ_Text = ppArgs[0];				// point at the options (if any)
			m_tmTile.m_ptFirst.InitPoint();			// clear this first
			m_tmTile.m_Code = CV_EXTRACT;			// set extract code
			m_tmTile.m_id = Exp_GetVal(ppArgs[1]);	// extract id
			addTarget(CLIMODE_TARG_TILE, g_Cfg.GetDefaultMsg(DEFMSG_SELECT_EXTRACT_AREA), true);
			break;
		}
		case CV_UNEXTRACT:
		{
			// Create item from script.
			// Opposite of the "EXTRACT" command
			TCHAR *ppArgs[2];
			size_t iArgQty = Str_ParseCmds(s.GetArgStr(), ppArgs, COUNTOF(ppArgs));
			if ( iArgQty < 2 )
			{
				SysMessage(g_Cfg.GetDefaultMsg(DEFMSG_UNEXTRACT_USAGE));
				break;
			}

			m_Targ_Text = ppArgs[0];				// point at the options (if any)
			m_tmTile.m_ptFirst.InitPoint();			// clear this first
			m_tmTile.m_Code = CV_UNEXTRACT;			// set extract code
			m_tmTile.m_id = Exp_GetVal(ppArgs[1]);	// extract id
			addTarget(CLIMODE_TARG_UNEXTRACT, g_Cfg.GetDefaultMsg(DEFMSG_SELECT_MULTI_POS), true);
			break;
		}
		case CV_GMPAGE:
		{
			m_Targ_Text = s.GetArgStr();
			if ( !m_Targ_Text.IsEmpty() && !strnicmp(m_Targ_Text, "ADD ", 4) )
			{
				Cmd_GM_Page(m_Targ_Text + 4);
				break;
			}
			addPromptConsole(CLIMODE_PROMPT_GM_PAGE_TEXT, g_Cfg.GetDefaultMsg(DEFMSG_GMPAGE_PROMPT));
			break;
		}
		case CV_GOTARG:		// go to my (preselected) target.
		{
			ASSERT(m_pChar);
			CObjBase *pObj = m_Targ_UID.ObjFind();
			if ( pObj )
			{
				CPointMap pt = pObj->GetTopLevelObj()->GetTopPoint();
				m_pChar->m_dirFace = m_pChar->GetDir(pObj, m_pChar->m_dirFace);
				m_pChar->Spell_Teleport(pt, true, false);
			}
			break;
		}
		case CV_INFO:
		{
			// We could also get ground tile info.
			addTarget(CLIMODE_TARG_OBJ_INFO, g_Cfg.GetDefaultMsg(DEFMSG_SELECT_ITEM_INFO), true, false);
			break;
		}
		case CV_INFORMATION:
		{
			SysMessage(g_Serv.GetStatusString(0x22));
			SysMessage(g_Serv.GetStatusString(0x24));
			break;
		}
		case CV_LAST:	// fake previous target
		{
			if ( GetTargMode() >= CLIMODE_MOUSE_TYPE )
			{
				ASSERT(m_pChar);
				CObjBase *pObj = m_pChar->m_Act_Targ.ObjFind();
				if ( pObj )
				{
					Event_Target(GetTargMode(), pObj->GetUID(), pObj->GetTopPoint());
					addTargetCancel();
				}
				break;
			}
			return false;
		}
		case CV_LINK:	// link doors
		{
			m_Targ_UID.InitUID();
			addTarget(CLIMODE_TARG_LINK, g_Cfg.GetDefaultMsg(DEFMSG_SELECT_LINK_ITEM));
			break;
		}
		case CV_MAPWAYPOINT:
		{
			INT64 piVal[2];
			size_t iArgQty = Str_ParseCmds(s.GetArgRaw(), piVal, COUNTOF(piVal));
			if ( iArgQty < 2 )
			{
				SysMessage("Usage: MAPWAYPOINT uid type");
				break;
			}
			CObjBase *pObj = static_cast<CGrayUID>(piVal[0]).ObjFind();
			addMapWaypoint(pObj, static_cast<MAPWAYPOINT_TYPE>(piVal[1]));
			break;
		}
		case CV_MENU:
		{
			Menu_Setup(g_Cfg.ResourceGetIDType(RES_MENU, s.GetArgStr()));
			break;
		}
		case CV_MIDILIST:
		{
			INT64 piMidi[64];
			size_t iArgQty = Str_ParseCmds(s.GetArgStr(), piMidi, COUNTOF(piMidi));
			if ( iArgQty > 0 )
				addMusic(static_cast<MIDI_TYPE>(piMidi[Calc_GetRandVal(iArgQty)]));
			break;
		}
		case CV_NUDGE:
		{
			if ( !s.HasArgs() )
			{
				SysMessage("Usage: NUDGE dx dy dz");
				break;
			}
			m_Targ_Text = s.GetArgRaw();
			m_tmTile.m_ptFirst.InitPoint();		// clear this first
			m_tmTile.m_Code = CV_NUDGE;
			addTarget(CLIMODE_TARG_TILE, g_Cfg.GetDefaultMsg(DEFMSG_SELECT_NUDGE_AREA), true);
			break;
		}
		case CV_NUKE:
		{
			m_Targ_Text = s.GetArgRaw();
			m_tmTile.m_ptFirst.InitPoint();		// clear this first
			m_tmTile.m_Code = CV_NUKE;			// set nuke code
			addTarget(CLIMODE_TARG_TILE, g_Cfg.GetDefaultMsg(DEFMSG_SELECT_NUKE_AREA), true);
			break;
		}
		case CV_NUKECHAR:
		{
			m_Targ_Text = s.GetArgRaw();
			m_tmTile.m_ptFirst.InitPoint();		// clear this first
			m_tmTile.m_Code = CV_NUKECHAR;		// set nuke code
			addTarget(CLIMODE_TARG_TILE, g_Cfg.GetDefaultMsg(DEFMSG_SELECT_NUKE_CHAR_AREA), true);
			break;
		}
		case CV_OPENPAPERDOLL:
		{
			const CChar *pChar = s.HasArgs() ? static_cast<CGrayUID>(s.GetArgVal()).CharFind() : m_pChar;
			if ( pChar )
				addCharPaperdoll(pChar);
			break;
		}
		case CV_OPENTRADEWINDOW:
		{
			TCHAR *ppArgs[2];
			Str_ParseCmds(s.GetArgStr(), ppArgs, COUNTOF(ppArgs));

			CChar *pChar = ppArgs[0] ? static_cast<CGrayUID>(Exp_GetLLVal(ppArgs[0])).CharFind() : NULL;
			if ( pChar )
			{
				CItem *pItem = ppArgs[1] ? static_cast<CGrayUID>(Exp_GetLLVal(ppArgs[1])).ItemFind() : NULL;
				Cmd_SecureTrade(pChar, pItem);
			}
			break;
		}
		case CV_PAGE:
			Cmd_GM_PageCmd(s.GetArgStr());
			break;
		case CV_REPAIR:
			addTarget(CLIMODE_TARG_REPAIR, g_Cfg.GetDefaultMsg(DEFMSG_SELECT_ITEM_REPAIR));
			break;
		case CV_FLUSH:
#ifndef _MTNETWORK
			g_NetworkOut.flush(this);
#else
			g_NetworkManager.flush(m_NetState);
#endif
			break;
		case CV_RESEND:
			addReSync();
			break;
		case CV_SAVE:
			g_World.Save(s.GetArgVal() != 0);
			break;
		case CV_SCROLL:
			// put a scroll up.
			addScrollResource(s.GetArgStr(), SCROLL_TYPE_UPDATES);
			break;
		case CV_SENDPACKET:
			SendPacket(s.GetArgStr());
			break;
		case CV_SELF:		// fake self target
			if ( GetTargMode() >= CLIMODE_MOUSE_TYPE )
			{
				ASSERT(m_pChar);
				Event_Target(GetTargMode(), m_pChar->GetUID(), m_pChar->GetTopPoint());
				addTargetCancel();
				break;
			}
			return false;
		case CV_SHOWSKILLS:
			addSkillWindow(static_cast<SKILL_TYPE>(g_Cfg.m_iMaxSkill));		// reload the real skills
			break;
		case CV_SKILLMENU:
			Cmd_Skill_Menu(g_Cfg.ResourceGetIDType(RES_SKILLMENU, s.GetArgStr()));
			break;
		case CV_SKILLSELECT:
			Event_Skill_Use(g_Cfg.FindSkillKey(s.GetArgStr()));
			break;
		case CV_SUMMON:
		{
			ASSERT(m_pChar);
			const CSpellDef *pSpellDef = g_Cfg.GetSpellDef(SPELL_Summon);
			if ( !pSpellDef )
				return false;

			m_pChar->m_Act_Targ = m_pChar->GetUID();
			m_pChar->m_Act_TargPrv = m_pChar->GetUID();

			if ( pSpellDef->IsSpellType(SPELLFLAG_TARG_OBJ|SPELLFLAG_TARG_XYZ) )
			{
				m_tmSkillMagery.m_Spell = SPELL_Summon;
				m_tmSkillMagery.m_SummonID = static_cast<CREID_TYPE>(g_Cfg.ResourceGetIndexType(RES_CHARDEF, s.GetArgStr()));

				LPCTSTR pszPrompt = g_Cfg.GetDefaultMsg(DEFMSG_SELECT_MAGIC_TARGET);
				if ( !pSpellDef->m_sTargetPrompt.IsEmpty() )
					pszPrompt = pSpellDef->m_sTargetPrompt;

				int iSpellTimeout = static_cast<int>(GetDefNum("SPELLTIMEOUT"));
				if ( !iSpellTimeout )
					iSpellTimeout = g_Cfg.m_iSpellTimeout * TICK_PER_SEC;

				addTarget(CLIMODE_TARG_SKILL_MAGERY, pszPrompt, pSpellDef->IsSpellType(SPELLFLAG_TARG_XYZ), pSpellDef->IsSpellType(SPELLFLAG_HARM), iSpellTimeout);
				break;
			}
			else
			{
				m_pChar->m_atMagery.m_Spell = SPELL_Summon;
				m_pChar->m_atMagery.m_SummonID = static_cast<CREID_TYPE>(g_Cfg.ResourceGetIndexType(RES_CHARDEF, s.GetArgStr()));

				if ( IsSetMagicFlags(MAGICF_PRECAST) && !pSpellDef->IsSpellType(SPELLFLAG_NOPRECAST) )
				{
					m_pChar->Spell_CastDone();
					break;
				}
				else
				{
					int iSkill;
					if ( !pSpellDef->GetPrimarySkill(&iSkill, NULL) )
						return false;

					m_pChar->Skill_Start(static_cast<SKILL_TYPE>(iSkill));
				}
			}
			break;
		}
		case CV_SMSG:
		case CV_SYSMESSAGE:
			SysMessage(s.GetArgStr());
			break;
		case CV_SYSMESSAGEF:	// there is still an issue with numbers not resolving properly when %i,%d,or other numeric format code is in use
		{
			TCHAR *ppArgs[4];
			size_t iArgQty = Str_ParseCmds(s.GetArgRaw(), ppArgs, COUNTOF(ppArgs));
			if ( iArgQty < 2 )
			{
				g_Log.EventError("SysMessagef with less than 1 args for the given text\n");
				return false;
			}
			if ( iArgQty > 4 )
			{
				g_Log.EventError("Too many arguments given to SysMessagef (max = text + 3\n");
				return false;
			}
			if ( *ppArgs[0] == '"' )	// skip quotes
				++ppArgs[0];
			for ( TCHAR *pEnd = ppArgs[0] + strlen(ppArgs[0]) - 1; pEnd >= ppArgs[0]; --pEnd )
			{
				if ( *pEnd == '"' )		// skip quotes
				{
					*pEnd = '\0';
					break;
				}
			}
			SysMessagef(ppArgs[0], ppArgs[1], ppArgs[2] ? ppArgs[2] : 0, ppArgs[3] ? ppArgs[3] : 0);
			break;
		}
		case CV_SMSGU:
		case CV_SYSMESSAGEUA:
		{
			TCHAR *ppArgs[5];
			size_t iArgQty = Str_ParseCmds(s.GetArgRaw(), ppArgs, COUNTOF(ppArgs));
			if ( iArgQty > 4 )
			{
				// Font and mode are actually ignored here, but they never made a difference anyway.. I'd like to keep the syntax similar to SAYUA
				NCHAR szBuffer[MAX_TALK_BUFFER];
				CvtSystemToNUNICODE(szBuffer, COUNTOF(szBuffer), ppArgs[4], -1);

				addBarkUNICODE(szBuffer, NULL, static_cast<HUE_TYPE>(Exp_GetLLVal(ppArgs[0])), TALKMODE_SYSTEM, FONT_NORMAL, ppArgs[3]);
			}
			break;
		}
		case CV_SMSGL:
		case CV_SYSMESSAGELOC:
		{
			TCHAR *ppArgs[256];
			size_t iArgQty = Str_ParseCmds(s.GetArgRaw(), ppArgs, COUNTOF(ppArgs), ",");
			if ( iArgQty > 1 )
			{
				HUE_TYPE hue = HUE_TEXT_DEF;
				if ( ATOI(ppArgs[0]) > 0 )
					hue = static_cast<HUE_TYPE>(Exp_GetLLVal(ppArgs[0]));

				DWORD dwClilocId = static_cast<DWORD>(Exp_GetLLVal(ppArgs[1]));

				CGString sVal;
				for ( size_t i = 2; i < iArgQty; ++i )
				{
					if ( sVal.GetLength() )
						sVal += "\t";
					sVal += !strcmp(ppArgs[i], "NULL") ? " " : ppArgs[i];
				}

				addBarkLocalized(dwClilocId, NULL, hue, TALKMODE_SYSTEM, FONT_NORMAL, sVal.GetPtr());
			}
			break;
		}
		case CV_SMSGLEX:
		case CV_SYSMESSAGELOCEX:
		{
			TCHAR *ppArgs[256];
			size_t iArgQty = Str_ParseCmds(s.GetArgRaw(), ppArgs, COUNTOF(ppArgs), ",");
			if ( iArgQty > 2 )
			{
				HUE_TYPE hue = HUE_TEXT_DEF;
				AFFIX_TYPE affix = AFFIX_APPEND;
				if ( ATOI(ppArgs[0]) > 0 )
					hue = static_cast<HUE_TYPE>(Exp_GetLLVal(ppArgs[0]));

				DWORD dwClilocId = static_cast<DWORD>(Exp_GetLLVal(ppArgs[1]));

				if ( ppArgs[2] )
					affix = static_cast<AFFIX_TYPE>(Exp_GetLLVal(ppArgs[2]));

				CGString sVal;
				for ( size_t i = 4; i < iArgQty; ++i )
				{
					if ( sVal.GetLength() )
						sVal += "\t";
					sVal += !strcmp(ppArgs[i], "NULL") ? " " : ppArgs[i];
				}

				addBarkLocalizedEx(dwClilocId, NULL, hue, TALKMODE_SYSTEM, FONT_NORMAL, affix, ppArgs[3], sVal.GetPtr());
			}
			break;
		}
		case CV_TELE:
			Cmd_Skill_Magery(SPELL_Teleport, dynamic_cast<CObjBase *>(pSrc));
			break;
		case CV_TILE:
			if ( !s.HasArgs() )
			{
				SysMessage("Usage: TILE z-height item1 item2 itemX");
				break;
			}
			m_Targ_Text = s.GetArgStr();	// point at the options
			m_tmTile.m_ptFirst.InitPoint();	// clear this first
			m_tmTile.m_Code = CV_TILE;
			addTarget(CLIMODE_TARG_TILE, "Pick 1st corner:", true);
			break;
		case CV_VERSION:
			SysMessage(g_szServerDescription);
			break;
		case CV_WEBLINK:
			addWebLaunch(s.GetArgStr());
			break;
		default:
			if ( r_LoadVal(s) )
			{
				CGString sVal;
				if ( r_WriteVal(s.GetKey(), sVal, pSrc) )
					return true;
			}
			return CScriptObj::r_Verb(s, pSrc);		// used in the case of web pages to access server level things
	}
	return true;
	EXC_CATCH;

	EXC_DEBUG_START;
	EXC_ADD_SCRIPTSRC;
	EXC_DEBUG_END;
	return false;
}