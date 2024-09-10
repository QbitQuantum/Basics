bool  CCustomDetector::CheckCompatibilityInt(CHudItem* itm)
{
	if(itm==NULL)
		return true;

	CInventoryItem iitm				= itm->item();
	u32 slot						= iitm.GetSlot();
	bool bres = (slot==PISTOL_SLOT || slot==KNIFE_SLOT || slot==BOLT_SLOT);

	if(itm->GetState()!=CHUDState::eShowing)
		bres = bres && !itm->IsPending();

	if(bres)
	{
		CWeapon* W = smart_cast<CWeapon*>(itm);
		if(W)
			bres = bres && (W->GetState() != CHUDState::eBore) && (W->GetState() != CWeapon::eReload) &&
			(W->GetState() != CWeapon::eSwitch) && !W->IsZoomed();//+
	}
	return bres;
}