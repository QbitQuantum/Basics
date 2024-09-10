//------------------------------------------------------------------------
bool CItem::SetGeometry(int slot, const ItemString &name, const Vec3 &poffset, const Ang3 &aoffset, float scale, bool forceReload)
{
	bool changedfp=false;

	switch(slot)
	{
	case eIGS_Arms:
	{
		if(!name || forceReload)
		{
			GetEntity()->FreeSlot(slot);
#ifndef ITEM_USE_SHAREDSTRING
			m_geometry[slot].resize(0);
#else
			m_geometry[slot].reset();
#endif
		}

		ResetCharacterAttachment(eIGS_FirstPerson, ITEM_ARMS_ATTACHMENT_NAME);

		ICharacterInstance *pCharacter=0;

		if(name && name[0])
		{
			if(name != m_geometry[slot])
				GetEntity()->LoadCharacter(slot, name);

			DrawSlot(eIGS_Arms, false);

			pCharacter = GetEntity()->GetCharacter(eIGS_Arms);
		}
		else if(m_pForcedArms)
		{
			pCharacter = m_pForcedArms;
		}
		else
		{
			int armsId=m_stats.hand==eIH_Right?0:1;
			pCharacter = GetOwnerActor()?GetOwnerActor()->GetFPArms(armsId):0;
		}

		if(pCharacter)
		{
			pCharacter->SetFlags(pCharacter->GetFlags()&(~CS_FLAG_UPDATE));
			SetCharacterAttachment(eIGS_FirstPerson, ITEM_ARMS_ATTACHMENT_NAME, pCharacter, 0);
		}
	}
	break;

	case eIGS_FirstPerson:
	case eIGS_ThirdPerson:
	default:
	{
		if(!name || forceReload)
		{
			GetEntity()->FreeSlot(slot);
#ifndef ITEM_USE_SHAREDSTRING
			m_geometry[slot].resize(0);
#else
			m_geometry[slot].reset();
#endif
		}

		DestroyAttachmentHelpers(slot);

		if(name && name[0])
		{
			if(m_geometry[slot] != name)
			{
				const char *ext = PathUtil::GetExt(name.c_str());

				if((stricmp(ext, "chr") == 0) || (stricmp(ext, "cdf") == 0) || (stricmp(ext, "cga") == 0))
					GetEntity()->LoadCharacter(slot, name, 0);
				else
					GetEntity()->LoadGeometry(slot, name, 0, 0);

				changedfp=slot==eIGS_FirstPerson;
			}

			CreateAttachmentHelpers(slot);

			SetDefaultIdleAnimation(slot, g_pItemStrings->idle);
		}

		if(slot == eIGS_FirstPerson)
		{
			ICharacterInstance *pCharacter = GetEntity()->GetCharacter(eIGS_FirstPerson);

			if(pCharacter)
			{
				pCharacter->SetFlags(pCharacter->GetFlags()&(~CS_FLAG_UPDATE));
			}
		}
		else if(slot == eIGS_Destroyed)
			DrawSlot(eIGS_Destroyed, false);
	}
	break;
	}

	Matrix34 slotTM;
	slotTM = Matrix34::CreateRotationXYZ(aoffset);
	slotTM.Scale(Vec3(scale, scale, scale));
	slotTM.SetTranslation(poffset);
	GetEntity()->SetSlotLocalTM(slot, slotTM);

	if(changedfp && m_stats.mounted)
	{
		PlayAction(m_idleAnimation[eIGS_FirstPerson], 0, true);
		ForceSkinning(true);

		if(!m_mountparams.pivot.empty())
		{
			Matrix34 tm=GetEntity()->GetSlotLocalTM(eIGS_FirstPerson, false);
			Vec3 pivot = GetSlotHelperPos(eIGS_FirstPerson, m_mountparams.pivot.c_str(), false);
			tm.AddTranslation(pivot);

			GetEntity()->SetSlotLocalTM(eIGS_FirstPerson, tm);
		}

		GetEntity()->InvalidateTM();
	}

	m_geometry[slot] = name ? name : "";

	ReAttachAccessories();

	return true;
}