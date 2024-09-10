//--------------------------------------------------------------------------- 
BOOL CMyVolumeCtrl::vSetMuteValue(HMIXER   hmixer   ,MIXERCONTROL   *mxc,   BOOL   mute) 
{ 
	MIXERCONTROLDETAILS   mxcd; 
	MIXERCONTROLDETAILS_BOOLEAN   mxcdMute;mxcdMute.fValue=mute; 
	mxcd.hwndOwner   =   0; 
	mxcd.dwControlID   =   mxc-> dwControlID; 
	mxcd.cbStruct   =   sizeof(mxcd); 
	mxcd.cbDetails   =   sizeof(mxcdMute); 
	mxcd.paDetails   =   &mxcdMute; 
	mxcd.cChannels   =   1; 
	mxcd.cMultipleItems   =   0; 
	if   (mixerSetControlDetails((HMIXEROBJ)hmixer,   &mxcd,   MIXER_OBJECTF_HMIXER|MIXER_SETCONTROLDETAILSF_VALUE)) 
		return   FALSE; 
	return TRUE; 
} 