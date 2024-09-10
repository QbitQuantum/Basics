void CNewStatusBar::ToggleObjectives()
{
	PlaySoundInfo playSoundInfo;

	PLAYSOUNDINFO_INIT(playSoundInfo);
	playSoundInfo.m_dwFlags = PLAYSOUND_LOCAL;
	playSoundInfo.m_dwFlags |= PLAYSOUND_FILESTREAM;
	playSoundInfo.m_nPriority = SOUNDPRIORITY_MISC_MEDIUM;
	_mbsncpy((unsigned char*)playSoundInfo.m_szSoundName, (const unsigned char*)"Sounds\\Interface\\MainMenus\\missionobj.wav", sizeof(playSoundInfo.m_szSoundName) - 1);

	if(m_nObjLevel == OBJTAB_INVISIBLE)
	{
		m_nObjLevel = OBJTAB_SCALE_UP;
		m_fObjUpdateTime = m_pClientDE->GetTime();
		m_nObjIcon = OBJICON_INVISIBLE;
		m_pClientDE->PlaySound (&playSoundInfo);
	}
	else if(m_nObjLevel == OBJTAB_STOPPED)
	{
		m_nObjLevel = OBJTAB_SCALE_DOWN;
		m_fObjUpdateTime = m_pClientDE->GetTime();
		m_pClientDE->PlaySound (&playSoundInfo);
	}
}