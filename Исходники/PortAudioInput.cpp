bool PortAudioInput::SetMicrophoneLevel(DWORD dwLevel)
{
  MMRESULT mmresult;
  MIXERCONTROLDETAILS_UNSIGNED mxcdVolume_Set = {
    dwLevel
  };
  MIXERCONTROLDETAILS mxcd_Set;
  mxcd_Set.cbStruct = sizeof(MIXERCONTROLDETAILS);
  mxcd_Set.dwControlID = m_dwCntlID;
  mxcd_Set.cChannels = 1;
  mxcd_Set.cMultipleItems = 0;
  mxcd_Set.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
  mxcd_Set.paDetails = &mxcdVolume_Set;
  mmresult = mixerSetControlDetails(reinterpret_cast<HMIXEROBJ>(m_mixerMic),
				    &mxcd_Set,
				    MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE);
  return ( mmresult == MMSYSERR_NOERROR );
}