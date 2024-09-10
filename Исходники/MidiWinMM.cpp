void MidiWinMM::openDevices()
{
	m_inputDevices.clear();
	for( unsigned int i = 0; i < midiInGetNumDevs(); ++i )
	{
		MIDIINCAPS c;
		midiInGetDevCaps( i, &c, sizeof( c ) );
		HMIDIIN hm = 0;
		MMRESULT res = midiInOpen( &hm, i, (DWORD_PTR) &inputCallback,
						(DWORD_PTR) this,
							CALLBACK_FUNCTION );
		if( res == MMSYSERR_NOERROR )
		{
			m_inputDevices[hm] = qstrdup( c.szPname );
			midiInStart( hm );
		}
	}

	m_outputDevices.clear();
	for( unsigned int i = 0; i < midiOutGetNumDevs(); ++i )
	{
		MIDIOUTCAPS c;
		midiOutGetDevCaps( i, &c, sizeof( c ) );
		HMIDIOUT hm = 0;
		MMRESULT res = midiOutOpen( &hm, i, 0, 0, CALLBACK_NULL );
		if( res == MMSYSERR_NOERROR )
		{
			m_outputDevices[hm] = qstrdup( c.szPname );
		}
	}
}