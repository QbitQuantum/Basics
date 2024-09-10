static void winsnd_detect(MSSndCardManager *m){
    MMRESULT mr = NOERROR;
    unsigned int nInDevices = waveInGetNumDevs ();
    unsigned int item;
	char pcmdev[1024];
	char mixdev[1024];

    for (item = 0; item < nInDevices; item++)
    {
        WAVEINCAPS caps;
        mr = waveInGetDevCaps (item, &caps, sizeof (WAVEINCAPS));
        if (mr == MMSYSERR_NOERROR)
        {
            MSSndCard *card;
	        snprintf(pcmdev,sizeof(pcmdev),"%s",caps.szPname);
	        snprintf(mixdev,sizeof(mixdev),"%s",caps.szPname);
            if (item == 0)
            {
		        card=winsnd_card_new(pcmdev,mixdev, item-1);
		        ms_snd_card_manager_add_card(m,card);
            }
			card=winsnd_card_new(pcmdev,mixdev, item);
			ms_snd_card_manager_add_card(m,card);
        }
    }
#if 0
	nInDevices = mixerGetNumDevs ();
    for (item = 0; item < nInDevices; item++)
    {
        MIXERCAPS caps;
        mr = mixerGetDevCaps (item, &caps, sizeof (MIXERCAPS));
        if (mr == MMSYSERR_NOERROR)
        {
	        snprintf(pcmdev,sizeof(pcmdev),"%s",caps.szPname);
	        snprintf(mixdev,sizeof(mixdev),"%s",caps.szPname);
        }
    }
#endif
}