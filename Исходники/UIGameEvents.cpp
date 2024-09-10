void CUIGameEvents::OnLoadGame( bool shouldResume )
{
	if (gEnv->IsEditor()) return;

	ILevelInfo* pLevel = m_pLevelSystem->GetCurrentLevel();
	if (pLevel)
	{
		m_pGameFramework->LoadGame(pLevel->GetPath(), true);
		if ( shouldResume && m_pGameFramework->IsGamePaused() )
			m_pGameFramework->PauseGame(false, true);
	}
}