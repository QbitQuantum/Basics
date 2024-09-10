void CUIWeaponCellItem::Update()
{
	bool b						= Heading();
	inherited::Update			();
	
	bool bForceReInitAddons		= (b!=Heading());

	if (object()->SilencerAttachable())
	{
		if (object()->IsSilencerAttached())
		{
			if (!GetIcon(eSilencer) || bForceReInitAddons)
			{
				CreateIcon	(eSilencer);
				InitAddon	(GetIcon(eSilencer), *object()->GetSilencerName(), m_addon_offset[eSilencer], Heading());
			}
		}
		else
		{
			if (m_addons[eSilencer])
				DestroyIcon(eSilencer);
		}
	}

	if (object()->ScopeAttachable()){
		if (object()->IsScopeAttached())
		{
			if (!GetIcon(eScope) || bForceReInitAddons)
			{
				CreateIcon	(eScope);
				InitAddon	(GetIcon(eScope), *object()->GetScopeName(), m_addon_offset[eScope], Heading());
			}
		}
		else
		{
			if (m_addons[eScope])
				DestroyIcon(eScope);
		}
	}

	if (object()->GrenadeLauncherAttachable()){
		if (object()->IsGrenadeLauncherAttached())
		{
			if (!GetIcon(eLauncher) || bForceReInitAddons)
			{
				CreateIcon	(eLauncher);
				InitAddon	(GetIcon(eLauncher), *object()->GetGrenadeLauncherName(), m_addon_offset[eLauncher], Heading());
			}
		}
		else
		{
			if (m_addons[eLauncher])
				DestroyIcon(eLauncher);
		}
	}
}