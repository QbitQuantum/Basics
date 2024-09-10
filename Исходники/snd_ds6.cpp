static int Detect()
{
	DX_Context ds;
    g_lpDSDevice = NULL;
    sysMemZero(g_pDSHandles, DSOUNDMAXBUFFER * sizeof(DS_handle));
    ds.lpGUID = NULL;

    if (RLX.Audio.WaveDeviceId)
    {
       ds.index = 0;
       ds.mode = 1;
       DirectSoundEnumerate((LPDSENUMCALLBACKA)DSEnumCallback, &ds);
    }

    if (SYS_DXTRACE(DirectSoundCreate(ds.lpGUID, &g_lpDSDevice, NULL)))
    {
       if (ds.lpGUID)
       {
			ds.lpGUID = NULL;
			RLX.Audio.WaveDeviceId = 0;
       }
	   if (SYS_DXTRACE(DirectSoundCreate(ds.lpGUID, &g_lpDSDevice, NULL)))
		   return -1;
    }
    return 0;
}