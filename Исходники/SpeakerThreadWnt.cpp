static int openSpeakerDevices(WAVEHDR*& pWH, HWAVEOUT& hOut)
{
    DWORD    bufLen = ((N_SAMPLES * BITS_PER_SAMPLE) / 8);
    int i ;
    MMRESULT ret;
    MSG tMsg;
    BOOL bSuccess ;    

	// set the different device ids
	gRingDeviceId = WAVE_MAPPER;
	gCallDeviceId = WAVE_MAPPER;


    // If either the ringer or call device is set to NONE, don't engage any audio devices
    if ((strcasecmp(DmaTask::getRingDevice(), "NONE") == 0) ||
        (strcasecmp(DmaTask::getCallDevice(), "NONE") == 0))
    {
        ResumeThread(hMicThread);
        return 1;
    }

    /*
     * Select in-call / ringer devices
     */
	int ii;
	WAVEOUTCAPS devcaps;
	int numberOfDevicesOnSystem = waveOutGetNumDevs();
	for(ii=0; ii<numberOfDevicesOnSystem; ii++)
    {
        waveOutGetDevCaps(ii,&devcaps,sizeof(WAVEOUTCAPS));
        if (strcmp(devcaps.szPname, DmaTask::getRingDevice())==0) 
        {
            gRingDeviceId = ii;
            osPrintf("SpkrThread: Selected ring device: %s\n",devcaps.szPname);
        }

		if (strcmp(devcaps.szPname, DmaTask::getCallDevice())==0) 
        {
            gCallDeviceId = ii;
            osPrintf("SpkrThread: Selected call device: %s\n",devcaps.szPname);
        }
    }

    /*
     * Open ringer device
     */ 
    if (!openAudioOut(gRingDeviceId, &audioOutH, 1, SAMPLES_PER_SEC, BITS_PER_SAMPLE))
    {
        osPrintf("SpkrThread: Failed to open ring audio output channel\n\n");
        ResumeThread(hMicThread);
        return 1;
    }

    do 
    {
        bSuccess = GetMessage(&tMsg, NULL, 0, 0) ;
    } while (bSuccess && (tMsg.message != WOM_OPEN)) ;


    /*
     * Open in-call device
     */
    if (!openAudioOut(gCallDeviceId,&audioOutCallH, 1, SAMPLES_PER_SEC, BITS_PER_SAMPLE))
    {
        osPrintf("SpkrThread: Failed to open call audio output channel\n\n");
        ResumeThread(hMicThread);
        return 1;
    }

    do 
    {
        bSuccess = GetMessage(&tMsg, NULL, 0, 0) ;
    } while (bSuccess && tMsg.message != WOM_OPEN) ;


    // Pre load some data    
    for (i=0; i<smSpkrQPreload; i++)
    {
        pWH = outPrePrep(i, bufLen);

        hOut = selectSpeakerDevice() ;
        if (hOut)
        {
            ret = waveOutPrepareHeader(hOut, pWH, sizeof(WAVEHDR));
            if (ret != MMSYSERR_NOERROR)
            {
                showWaveError("waveOutPrepareHeader", ret, i, __LINE__);
            }
	        ret = waveOutWrite(hOut, pWH, sizeof(WAVEHDR));
            if (ret != MMSYSERR_NOERROR)
            {
   	            showWaveError("waveOutWrite", ret, i, __LINE__);
            }
        }      
    }

    return 0 ;
}