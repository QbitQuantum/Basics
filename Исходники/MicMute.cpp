BOOL MicMute::selectMic(int val)
{
	if (m_mixer == NULL)
	{
		return FALSE;
	}

	log.WriteString("\n Selecting mic...");
	MIXERCONTROLDETAILS_BOOLEAN *pValue =
		new MIXERCONTROLDETAILS_BOOLEAN;

	pValue->fValue=val;
	
	mxcd.cMultipleItems=0;
	mxcd.cbDetails=sizeof(MIXERCONTROLDETAILS_BOOLEAN);
	mxcd.paDetails=pValue;
	

	

	if( mixerSetControlDetails( ( HMIXEROBJ )m_mixer, &mxcd, 
			                      MIXER_SETCONTROLDETAILSF_VALUE | MIXER_OBJECTF_HMIXER ) 
		!= MMSYSERR_NOERROR )
	{
	log.WriteString("\nError while setting value");
	return FALSE;
	}

	log.WriteString("Mic selected properly");
	return TRUE;

}