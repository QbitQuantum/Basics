bool CASW_Weapon_Sniper_Rifle::ShouldMarineMoveSlow()
{
	return (gpGlobals->curtime < m_fSlowTime) || IsZoomed();
}