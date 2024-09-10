void CWeaponMagazined::StartIdleAnim			()
{
	if(IsZoomed())	m_pHUD->animDisplay(mhud.mhud_idle_aim[Random.randI(mhud.mhud_idle_aim.size())], TRUE);
	else			m_pHUD->animDisplay(mhud.mhud_idle[Random.randI(mhud.mhud_idle.size())], TRUE);
}