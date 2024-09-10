//------------------------------------------------------------------------
void CWeapon::OnDropped(EntityId actorId, bool ownerWasAI)
{
	BROADCAST_WEAPON_EVENT(OnDropped, (this, actorId));

	BaseClass::OnDropped(actorId, ownerWasAI);

	IEntity * pEntity = GetEntity();

	if(gEnv->bServer)
	{
		bool removeWeapon = true;

		if(gEnv->bMultiplayer && GetParams().check_clip_size_after_drop)
		{
			TFireModeVector::const_iterator firemodesEndIt = m_firemodes.end();
			for (TFireModeVector::const_iterator firemodeCit = m_firemodes.begin(); firemodeCit != firemodesEndIt && removeWeapon; ++firemodeCit)
			{
				const CFireMode* pFiremode = *firemodeCit;
				if (pFiremode)
				{
					IEntityClass* pFiremodeAmmo = pFiremode->GetAmmoType();
					if (pFiremodeAmmo)
					{
						//only check the main ammo type given with the weapon
						if(SWeaponAmmoUtils::FindAmmoConst(m_weaponsharedparams->ammoParams.ammo, pFiremodeAmmo))
						{
							int currentClipAmount = GetAmmoCount(pFiremodeAmmo);
							int clipSize = pFiremode->GetClipSize();

							if(currentClipAmount > 0 && currentClipAmount >= clipSize)
							{
								removeWeapon = false;
							}
						}
					}
				}
			}
		}
		else
		{
			const bool outOfAmmo = OutOfAmmo(true) && !ownerWasAI;
			const bool removeOnDrop = GetSharedItemParams()->params.remove_on_drop;
			removeWeapon = !gEnv->pSystem->IsSerializingFile() && (outOfAmmo && removeOnDrop);
		}

		if(removeWeapon && GetParams().check_bonus_ammo_after_drop)
		{
			for(unsigned int i = 0; i < m_bonusammo.size(); ++i)
			{
				if(m_bonusammo[i].count > 0)
				{
					removeWeapon = false;
					break;
				}
			}
		}

		if(removeWeapon)
		{
			if(gEnv->IsEditor())
			{
				pEntity->Hide(true);
			}
			else
			{
				gEnv->pEntitySystem->RemoveEntity(pEntity->GetId());
			}		
		}
	}

	uint32 flags = pEntity->GetFlags();
	
	flags &= ~ENTITY_FLAG_NO_PROXIMITY;

	pEntity->SetFlags(flags);

	m_expended_ammo = 0;

	if(gEnv->bMultiplayer && (g_pGameCVars->i_highlight_dropped_weapons == 2) || (IsHeavyWeapon() && g_pGameCVars->i_highlight_dropped_weapons == 1))
	{
		HighlightWeapon(true, true);
	}
}