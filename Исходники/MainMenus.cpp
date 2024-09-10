// Plays a sound
HSOUNDDE CMainMenus::PlaySound(char *lpszSound, DBOOL bStream, DBOOL bLoop, DBOOL bGetHandle)
{
	PlaySoundInfo playSoundInfo;

	PLAYSOUNDINFO_INIT(playSoundInfo);
	playSoundInfo.m_dwFlags = PLAYSOUND_LOCAL;

	if (bStream)
	{
		playSoundInfo.m_dwFlags |= PLAYSOUND_FILESTREAM;
	}
	if (bLoop)
	{
		playSoundInfo.m_dwFlags |= PLAYSOUND_LOOP;
	}
	if (bGetHandle)
	{
		playSoundInfo.m_dwFlags |= PLAYSOUND_GETHANDLE;
	}

	_mbsncpy((unsigned char*)playSoundInfo.m_szSoundName, (const unsigned char*)lpszSound, sizeof( playSoundInfo.m_szSoundName ) - 1 );
	playSoundInfo.m_nPriority = SOUNDPRIORITY_MISC_MEDIUM;

	// Play the sound
	if( m_pClientDE->PlaySound (&playSoundInfo) != LT_OK )
		return NULL;

	return playSoundInfo.m_hSound;
}