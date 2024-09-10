bool CMimAPI::getAeroState()
{
	BOOL result = FALSE;
	m_isAero = m_DwmActive = false;
	if (IsWinVerVistaPlus()) {
		m_DwmActive = (m_pfnDwmIsCompositionEnabled && (m_pfnDwmIsCompositionEnabled(&result) == S_OK) && result) ? true : false;
		m_isAero = (CSkin::m_skinEnabled == false) && GetByte("useAero", 1) && CSkin::m_fAeroSkinsValid && m_DwmActive;

	}
	m_isVsThemed = IsThemeActive() != 0;
	return m_isAero;
}