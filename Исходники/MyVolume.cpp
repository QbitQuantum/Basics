BOOL CMyVolume::SetValue(int nVol)
{
	BOOL bSet = FALSE;
	HMIXER hmier;
	if (mixerOpen(&hmier, 0, 0, 0, 0))
	{
		return FALSE;
	}
	long device = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
	MIXERCONTROL volCtrl;
	BOOL bRet(FALSE);
	if ( GetVolumeControl(hmier, device, MIXERCONTROL_CONTROLTYPE_VOLUME, &volCtrl) )
	{
		nVol = nVol* volCtrl.Bounds.lMaximum/MAX_VOL;
		if ( SetVolumeValue(hmier,&volCtrl, nVol ) )
		{
			bRet = TRUE;			
		}

	}
	mixerClose(hmier);
	return bRet;
}