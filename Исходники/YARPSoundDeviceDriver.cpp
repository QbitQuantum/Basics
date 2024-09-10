//--------------------------------------------------------------------------------------
//       Class:  YARPSoundDeviceDriver
//      Method:  set_mute
// Description:  This function set the mute state in the already selected line.
// Use:
// 	0 -> mute
// 	1 -> No mute
//--------------------------------------------------------------------------------------
int 
YARPSoundDeviceDriver::set_mute(void *cmd)
{
	MIXERCONTROLDETAILS_UNSIGNED	value[2];
	MIXERCONTROLDETAILS				mixerControlDetails;
	MMRESULT						err;
	
	SoundResources& d = RES(system_resources);

	unsigned int * m_mute_state = (unsigned int *) cmd;
	
	//----------------------------------------------------------------------
	//  Select the mute control in the selected line
	//----------------------------------------------------------------------
	//d._select_control(MIXERCONTROL_CONTROLTYPE_MUTE);
	d._select_control(MIXERCONTROL_CONTROLTYPE_ONOFF);
	
	mixerControlDetails.cbStruct    = sizeof(MIXERCONTROLDETAILS);
	mixerControlDetails.dwControlID = d.m_mixerControlArray.dwControlID;
	mixerControlDetails.cChannels   = d.m_mixerLine.cChannels;
	
	if (mixerControlDetails.cChannels > 2) mixerControlDetails.cChannels = 2;
	
	if (d.m_mixerControlArray.fdwControl & MIXERCONTROL_CONTROLF_UNIFORM) mixerControlDetails.cChannels = 1;

	mixerControlDetails.cMultipleItems = 0;
	mixerControlDetails.paDetails      = &value[0];
	mixerControlDetails.cbDetails      = sizeof(MIXERCONTROLDETAILS_UNSIGNED);

	value[0].dwValue = value[1].dwValue = (*m_mute_state);

	err = mixerSetControlDetails((HMIXEROBJ)d.m_MixerHandle, 
								 &mixerControlDetails, 
								 MIXER_SETCONTROLDETAILSF_VALUE);
	
	if( err != MMSYSERR_NOERROR) printf("yarpsounddriver: Error #%d setting mute for %s!\n", err, d.m_mixerLine.szName);

	return YARP_OK;
}