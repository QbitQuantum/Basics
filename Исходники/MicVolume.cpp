void CMicVolume::SetDeviceCtrl(MCS *pData, float vol)
{
	int nCnt = 1;

	MIXERCONTROLDETAILS_UNSIGNED mixer_control_details_unsigned[10];
	MIXERCONTROLDETAILS mixer_control_details;
	mixer_control_details.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mixer_control_details.dwControlID = pData->m_ctlMixerSpeaker.dwControlID;
	mixer_control_details.cChannels = 1;
	mixer_control_details.cMultipleItems = pData->m_ctlMixerSpeaker.cMultipleItems;
	mixer_control_details.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mixer_control_details.paDetails = mixer_control_details_unsigned;

    if(MIXERCONTROL_CONTROLF_MULTIPLE & pData->m_ctlMixerSpeaker.fdwControl) nCnt = pData->m_ctlMixerSpeaker.cMultipleItems;

	for(int i = 0; i < nCnt; i++){
		mixer_control_details_unsigned[i].dwValue = (int)((vol * 65535 + pData->nMax/2) / pData->nMax);
	}
	if(mixerSetControlDetails((HMIXEROBJ)h_mix, &mixer_control_details, 0))
	{
#ifdef _DEBUG
		MessageBox(NULL,"내부 함수 오류(mixerSetControlDetails)", "내부 함수 오류", MB_ICONSTOP);
#endif
	}
	return;
}