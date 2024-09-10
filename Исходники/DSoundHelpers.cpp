CString DSound::Init()
{
	HRESULT hr;
	if( FAILED( hr = DirectSoundCreate(NULL, &m_pDS, NULL) ) )
		return hr_ssprintf( hr, "DirectSoundCreate" );

#ifndef _XBOX
	static bool bShownInfo = false;
	if( !bShownInfo )
	{
		bShownInfo = true;
		DirectSoundEnumerate( EnumCallback, 0 );

		DSCAPS Caps;
		Caps.dwSize = sizeof(Caps);
		HRESULT hr;
		if( FAILED(hr = m_pDS->GetCaps(&Caps)) )
		{
			LOG->Warn( hr_ssprintf(hr, "m_pDS->GetCaps failed") );
		}
		else
		{
			LOG->Info( "DirectSound sample rates: %i..%i %s", Caps.dwMinSecondarySampleRate, Caps.dwMaxSecondarySampleRate,
				(Caps.dwFlags & DSCAPS_CONTINUOUSRATE)?"(continuous)":"" );
		}
	}

	/* Try to set primary mixing privileges */
	hr = m_pDS->SetCooperativeLevel( GetDesktopWindow(), DSSCL_PRIORITY );
#endif

	SetPrimaryBufferMode();

	return "";
}