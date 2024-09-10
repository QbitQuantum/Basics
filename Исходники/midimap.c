static	DWORD	modReset(MIDIMAPDATA* mom)
{
    WORD	chn;
    DWORD	ret = MMSYSERR_NOERROR;

    if (MIDIMAP_IsBadData(mom))
	return MMSYSERR_ERROR;

    for (chn = 0; chn < 16; chn++)
    {
	if (mom->ChannelMap[chn] && mom->ChannelMap[chn]->loaded > 0)
	{
	    ret = midiOutReset(mom->ChannelMap[chn]->hMidi);
	    if (ret != MMSYSERR_NOERROR) break;
	}
    }
    return ret;
}