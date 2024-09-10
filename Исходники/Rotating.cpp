void Rotating::StartSound(HSTRING hstrSoundName, DBOOL bLoop)
{
	CServerDE* pServerDE = BaseClass::GetServerDE();
	if (!pServerDE) return;

	// Stop the last sound if there is one...

	if (m_sndLastSound)
	{
		pServerDE->KillSound(m_sndLastSound);
		m_sndLastSound = DNULL;
	}

	if (!hstrSoundName) return;

	char *pSoundName = pServerDE->GetStringData(hstrSoundName);
	if (!pSoundName) return;


	PlaySoundInfo playSoundInfo;
	PLAYSOUNDINFO_INIT(playSoundInfo);

	playSoundInfo.m_dwFlags = PLAYSOUND_3D | PLAYSOUND_REVERB;
	playSoundInfo.m_dwFlags |= PLAYSOUND_ATTACHED;

	if (bLoop)
	{
		playSoundInfo.m_dwFlags |= PLAYSOUND_LOOP | PLAYSOUND_GETHANDLE;
	}

	_mbsncpy((unsigned char*)playSoundInfo.m_szSoundName, (const unsigned char*)pSoundName, _MAX_PATH);
	playSoundInfo.m_hObject = m_hObject;
	playSoundInfo.m_fOuterRadius = m_fSoundRadius;
	playSoundInfo.m_fInnerRadius = 200;

	pServerDE->PlaySound(&playSoundInfo);

	// Save the handle of the sound...

	m_sndLastSound = playSoundInfo.m_hSound;
}