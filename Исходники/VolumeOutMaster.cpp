void CVolumeOutMaster::SetCurrentVolume( DWORD dwValue )
{
	if ( !m_bAvailable || (dwValue<m_dwMinimalVolume) || (dwValue>m_dwMaximalVolume) )
		return;
	MIXERCONTROLDETAILS_UNSIGNED* aDetails = (MIXERCONTROLDETAILS_UNSIGNED*)malloc(m_nChannelCount*sizeof(MIXERCONTROLDETAILS_UNSIGNED));
	if ( !aDetails )
		return;
	for ( int i = 0; i < m_nChannelCount; i++ )
	{
		aDetails[i].dwValue = dwValue;
	}
	MIXERCONTROLDETAILS ControlDetails;
	memset( &ControlDetails, 0, sizeof(MIXERCONTROLDETAILS) );
	ControlDetails.cbStruct = sizeof(MIXERCONTROLDETAILS);
	ControlDetails.dwControlID = m_dwVolumeControlID;
	ControlDetails.cChannels = m_nChannelCount;
	ControlDetails.cMultipleItems = 0;
	ControlDetails.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	ControlDetails.paDetails = &aDetails[0];
	MMRESULT mmResult = mixerSetControlDetails( (HMIXEROBJ)m_dwMixerHandle, &ControlDetails, MIXER_SETCONTROLDETAILSF_VALUE );
	free( aDetails );
	if ( mmResult != MMSYSERR_NOERROR )
	{
		ssi_wrn (".MasterOutputVolume: FAILURE: Could not set volume(%d) mmResult=%d\n", dwValue, mmResult );
	}
}