ScreenUserPacks::ScreenUserPacks( CString sName ) : ScreenWithMenuElements( sName )
{
	m_bRestart = false;
	m_bPrompt = false;
	m_CurPlayer = PLAYER_INVALID;
	MEMCARDMAN->UnlockCards();
	DrawTimer.SetZero();
}