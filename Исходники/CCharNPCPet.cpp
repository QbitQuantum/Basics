bool CChar::NPC_OnHearPetCmdTarg(int iCmd, CChar *pSrc, CObjBase *pObj, const CPointMap &pt, LPCTSTR pszArgs)
{
	ADDTOCALLSTACK("CChar::NPC_OnHearPetCmdTarg");
	// Pet commands that required a target.

	if ( m_fIgnoreNextPetCmd )
	{
		m_fIgnoreNextPetCmd = false;
		return false;
	}

	if ( !NPC_PetCheckAccess(iCmd, pSrc) )
		return true;

	bool bSuccess = false;
	CItem *pItemTarg = dynamic_cast<CItem *>(pObj);
	CChar *pCharTarg = dynamic_cast<CChar *>(pObj);

	switch ( iCmd )
	{
		case PC_ATTACK:
		case PC_KILL:
		{
			if ( !pCharTarg || (pCharTarg == this) || (pCharTarg == pSrc) )
				break;

			bSuccess = pCharTarg->OnAttackedBy(pSrc, true);
			if ( bSuccess )
				bSuccess = Fight_Attack(pCharTarg, true);
			break;
		}

		case PC_FOLLOW:
			if ( !pCharTarg || (pCharTarg == this) )
				break;
			m_Act_Targ = pCharTarg->GetUID();
			bSuccess = Skill_Start(NPCACT_FOLLOW_TARG);
			break;

		case PC_FRIEND:
		{
			if ( !pCharTarg || !pCharTarg->m_pPlayer || (pCharTarg == pSrc) )
			{
				Speak(g_Cfg.GetDefaultMsg(DEFMSG_NPC_PET_CONFUSED));
				break;
			}
			CItemMemory *pMemory = Memory_FindObjTypes(pCharTarg, MEMORY_FRIEND);
			if ( pMemory )
			{
				pSrc->SysMessage(g_Cfg.GetDefaultMsg(DEFMSG_NPC_PET_TARG_FRIEND_ALREADY));
				break;
			}
			pSrc->SysMessagef(g_Cfg.GetDefaultMsg(DEFMSG_NPC_PET_TARG_FRIEND_SUCCESS1), GetName(), pCharTarg->GetName());
			pCharTarg->SysMessagef(g_Cfg.GetDefaultMsg(DEFMSG_NPC_PET_TARG_FRIEND_SUCCESS2), pSrc->GetName(), GetName());
			Memory_AddObjTypes(pCharTarg, MEMORY_FRIEND);

			m_Act_Targ = pCharTarg->GetUID();
			bSuccess = Skill_Start(NPCACT_FOLLOW_TARG);
			break;
		}

		case PC_UNFRIEND:
		{
			if ( !pCharTarg || !pCharTarg->m_pPlayer )
			{
				Speak(g_Cfg.GetDefaultMsg(DEFMSG_NPC_PET_CONFUSED));
				break;
			}
			CItemMemory *pMemory = Memory_FindObjTypes(pCharTarg, MEMORY_FRIEND);
			if ( !pMemory )
			{
				pSrc->SysMessage(g_Cfg.GetDefaultMsg(DEFMSG_NPC_PET_TARG_UNFRIEND_NOTFRIEND));
				break;
			}
			pSrc->SysMessagef(g_Cfg.GetDefaultMsg(DEFMSG_NPC_PET_TARG_UNFRIEND_SUCCESS1), GetName(), pCharTarg->GetName());
			pCharTarg->SysMessagef(g_Cfg.GetDefaultMsg(DEFMSG_NPC_PET_TARG_UNFRIEND_SUCCESS2), pSrc->GetName(), GetName());
			pMemory->Delete();

			m_Act_Targ = pSrc->GetUID();
			bSuccess = Skill_Start(NPCACT_FOLLOW_TARG);
			break;
		}

		case PC_GO:
			if ( !pt.IsValidPoint() )
				break;
			m_Act_p = pt;
			bSuccess = Skill_Start(NPCACT_GOTO);
			break;

		case PC_GUARD:
			if ( !pCharTarg || (pCharTarg == this) )
				break;
			pCharTarg->SysMessagef(g_Cfg.GetDefaultMsg(DEFMSG_NPC_PET_TARG_GUARD_SUCCESS), GetName());
			m_Act_Targ = pCharTarg->GetUID();
			bSuccess = Skill_Start(NPCACT_GUARD_TARG);
			break;

		case PC_TRANSFER:
			if ( !pCharTarg || !pCharTarg->m_pClient )
				break;
			if ( IsSetOF(OF_PetSlots) )
			{
				if ( !pCharTarg->FollowersUpdate(this, static_cast<short>(maximum(1, GetDefNum("FOLLOWERSLOTS", true))), true) )
				{
					pSrc->SysMessageDefault(DEFMSG_PETSLOTS_TRY_TRANSFER);
					break;
				}
			}
			bSuccess = NPC_PetSetOwner(pCharTarg);
			break;

		case PC_PRICE:
			if ( !pItemTarg || !NPC_IsVendor() || !pSrc->m_pClient )
				break;
			if ( IsDigit(pszArgs[0]) )	// did they name a price
				return NPC_SetVendorPrice(pItemTarg, ATOI(pszArgs));
			if ( !NPC_SetVendorPrice(pItemTarg, -1) )	// test if it can be priced
				return false;
			pSrc->m_pClient->addPromptConsole(CLIMODE_PROMPT_VENDOR_PRICE, g_Cfg.GetDefaultMsg(DEFMSG_NPC_VENDOR_SETPRICE_2), pItemTarg->GetUID(), GetUID());
			return true;

		default:
			break;
	}

	// Make some sound to confirm we heard it
	NPC_PetConfirmCommand(bSuccess, pSrc);
	return bSuccess;
}