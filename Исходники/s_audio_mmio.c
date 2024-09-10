void mmio_close_audio( void)
{
    int errcode;
    int nda, nad;
    if (sys_verbose)
    	post("closing audio...");

    for (nda=0; nda < nt_nwaveout; nda++) /*if (nt_nwaveout) wini */
    {
       errcode = waveOutReset(ntsnd_outdev[nda]);
       if (errcode != MMSYSERR_NOERROR)
	   printf("error resetting output %d: %d\n", nda, errcode);
       errcode = waveOutClose(ntsnd_outdev[nda]);
       if (errcode != MMSYSERR_NOERROR)
	   printf("error closing output %d: %d\n",nda , errcode);	   
    }
    nt_nwaveout = 0;

    for(nad=0; nad < nt_nwavein;nad++) /* if (nt_nwavein) wini */
    {
	errcode = waveInReset(ntsnd_indev[nad]);
	if (errcode != MMSYSERR_NOERROR)
	    printf("error resetting input: %d\n", errcode);
	errcode = waveInClose(ntsnd_indev[nad]);
	if (errcode != MMSYSERR_NOERROR)
	    printf("error closing input: %d\n", errcode);
    }
    nt_nwavein = 0;
}