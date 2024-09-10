/**********************************************************************
 * DEVENUM_CreateSpecialCategories (INTERNAL)
 *
 * Creates the keys in the registry for the dynamic categories
 */
static HRESULT DEVENUM_CreateSpecialCategories(void)
{
    HRESULT res;
    WCHAR szDSoundNameFormat[MAX_PATH + 1];
    WCHAR szDSoundName[MAX_PATH + 1];
    DWORD iDefaultDevice = -1;
    UINT numDevs;
    IFilterMapper2 * pMapper = NULL;
    REGFILTER2 rf2;
    REGFILTERPINS2 rfp2;
    WCHAR path[MAX_PATH];
    HKEY basekey;

    if (DEVENUM_populate_handle)
        return S_OK;
    DEVENUM_populate_handle = CreateEventW(NULL, TRUE, FALSE, DEVENUM_populate_handle_nameW);
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        /* Webcams can take some time to scan if the driver is badly written and it enables them,
         * so have a 10 s timeout here
         */
        if (WaitForSingleObject(DEVENUM_populate_handle, 10000) == WAIT_TIMEOUT)
            WARN("Waiting for object timed out\n");
        TRACE("No need to rescan\n");
        return S_OK;
    }
    TRACE("Scanning for devices\n");

    /* Since devices can change between session, for example because you just plugged in a webcam
     * or switched from pulseaudio to alsa, delete all old devices first
     */
    if (SUCCEEDED(DEVENUM_GetCategoryKey(&CLSID_AudioRendererCategory, &basekey, path, MAX_PATH)))
        RegDeleteTreeW(basekey, path);
    if (SUCCEEDED(DEVENUM_GetCategoryKey(&CLSID_AudioInputDeviceCategory, &basekey, path, MAX_PATH)))
        RegDeleteTreeW(basekey, path);
    if (SUCCEEDED(DEVENUM_GetCategoryKey(&CLSID_VideoInputDeviceCategory, &basekey, path, MAX_PATH)))
        RegDeleteTreeW(basekey, path);
    if (SUCCEEDED(DEVENUM_GetCategoryKey(&CLSID_MidiRendererCategory, &basekey, path, MAX_PATH)))
        RegDeleteTreeW(basekey, path);

    rf2.dwVersion = 2;
    rf2.dwMerit = MERIT_PREFERRED;
    rf2.u.s1.cPins2 = 1;
    rf2.u.s1.rgPins2 = &rfp2;
    rfp2.cInstances = 1;
    rfp2.nMediums = 0;
    rfp2.lpMedium = NULL;
    rfp2.clsPinCategory = &IID_NULL;

    if (!LoadStringW(DEVENUM_hInstance, IDS_DEVENUM_DS, szDSoundNameFormat, sizeof(szDSoundNameFormat)/sizeof(szDSoundNameFormat[0])-1))
    {
        ERR("Couldn't get string resource (GetLastError() is %d)\n", GetLastError());
        return HRESULT_FROM_WIN32(GetLastError());
    }

    res = CoCreateInstance(&CLSID_FilterMapper2, NULL, CLSCTX_INPROC,
                           &IID_IFilterMapper2, (void **) &pMapper);
    /*
     * Fill in info for devices
     */
    if (SUCCEEDED(res))
    {
        UINT i;
        WAVEOUTCAPSW wocaps;
	WAVEINCAPSW wicaps;
        MIDIOUTCAPSW mocaps;
        REGPINTYPES * pTypes;

	numDevs = waveOutGetNumDevs();

        res = DEVENUM_CreateAMCategoryKey(&CLSID_AudioRendererCategory);
        if (FAILED(res)) /* can't register any devices in this category */
            numDevs = 0;

	rfp2.dwFlags = REG_PINFLAG_B_RENDERER;
	for (i = 0; i < numDevs; i++)
	{
	    if (waveOutGetDevCapsW(i, &wocaps, sizeof(WAVEOUTCAPSW))
	        == MMSYSERR_NOERROR)
	    {
                IMoniker * pMoniker = NULL;

                rfp2.nMediaTypes = 1;
                pTypes = CoTaskMemAlloc(rfp2.nMediaTypes * sizeof(REGPINTYPES));
                if (!pTypes)
                {
                    IFilterMapper2_Release(pMapper);
                    return E_OUTOFMEMORY;
                }
                /* FIXME: Native devenum seems to register a lot more types for
                 * DSound than we do. Not sure what purpose they serve */
                pTypes[0].clsMajorType = &MEDIATYPE_Audio;
                pTypes[0].clsMinorType = &MEDIASUBTYPE_PCM;

                rfp2.lpMediaType = pTypes;

                res = IFilterMapper2_RegisterFilter(pMapper,
		                              &CLSID_AudioRender,
					      wocaps.szPname,
					      &pMoniker,
					      &CLSID_AudioRendererCategory,
					      wocaps.szPname,
					      &rf2);

                /* FIXME: do additional stuff with IMoniker here, depending on what RegisterFilter does */

                if (pMoniker)
                {
                    IMoniker_Release(pMoniker);
                    pMoniker = NULL;
                }

		wsprintfW(szDSoundName, szDSoundNameFormat, wocaps.szPname);
	        res = IFilterMapper2_RegisterFilter(pMapper,
		                              &CLSID_DSoundRender,
					      szDSoundName,
					      &pMoniker,
					      &CLSID_AudioRendererCategory,
					      szDSoundName,
					      &rf2);

                /* FIXME: do additional stuff with IMoniker here, depending on what RegisterFilter does */

		if (pMoniker)
		    IMoniker_Release(pMoniker);

		if (i == iDefaultDevice)
		{
		    FIXME("Default device\n");
		}

                CoTaskMemFree(pTypes);
	    }
	}

        numDevs = waveInGetNumDevs();

        res = DEVENUM_CreateAMCategoryKey(&CLSID_AudioInputDeviceCategory);
        if (FAILED(res)) /* can't register any devices in this category */
            numDevs = 0;

	rfp2.dwFlags = REG_PINFLAG_B_OUTPUT;
        for (i = 0; i < numDevs; i++)
        {
            if (waveInGetDevCapsW(i, &wicaps, sizeof(WAVEINCAPSW))
                == MMSYSERR_NOERROR)
            {
                IMoniker * pMoniker = NULL;

                rfp2.nMediaTypes = 1;
                pTypes = CoTaskMemAlloc(rfp2.nMediaTypes * sizeof(REGPINTYPES));
                if (!pTypes)
                {
                    IFilterMapper2_Release(pMapper);
                    return E_OUTOFMEMORY;
                }

                /* FIXME: Not sure if these are correct */
                pTypes[0].clsMajorType = &MEDIATYPE_Audio;
                pTypes[0].clsMinorType = &MEDIASUBTYPE_PCM;

                rfp2.lpMediaType = pTypes;

	        res = IFilterMapper2_RegisterFilter(pMapper,
		                              &CLSID_AudioRecord,
					      wicaps.szPname,
					      &pMoniker,
					      &CLSID_AudioInputDeviceCategory,
					      wicaps.szPname,
					      &rf2);

                /* FIXME: do additional stuff with IMoniker here, depending on what RegisterFilter does */

		if (pMoniker)
		    IMoniker_Release(pMoniker);

                CoTaskMemFree(pTypes);
	    }
	}

	numDevs = midiOutGetNumDevs();

        res = DEVENUM_CreateAMCategoryKey(&CLSID_MidiRendererCategory);
        if (FAILED(res)) /* can't register any devices in this category */
            numDevs = 0;

	rfp2.dwFlags = REG_PINFLAG_B_RENDERER;
	for (i = 0; i < numDevs; i++)
	{
	    if (midiOutGetDevCapsW(i, &mocaps, sizeof(MIDIOUTCAPSW))
	        == MMSYSERR_NOERROR)
	    {
                IMoniker * pMoniker = NULL;

                rfp2.nMediaTypes = 1;
                pTypes = CoTaskMemAlloc(rfp2.nMediaTypes * sizeof(REGPINTYPES));
                if (!pTypes)
                {
                    IFilterMapper2_Release(pMapper);
                    return E_OUTOFMEMORY;
                }

                /* FIXME: Not sure if these are correct */
                pTypes[0].clsMajorType = &MEDIATYPE_Midi;
                pTypes[0].clsMinorType = &MEDIASUBTYPE_None;

                rfp2.lpMediaType = pTypes;

                res = IFilterMapper2_RegisterFilter(pMapper,
		                              &CLSID_AVIMIDIRender,
					      mocaps.szPname,
					      &pMoniker,
					      &CLSID_MidiRendererCategory,
					      mocaps.szPname,
					      &rf2);

                /* FIXME: do additional stuff with IMoniker here, depending on what RegisterFilter does */
		/* Native version sets MidiOutId */

		if (pMoniker)
		    IMoniker_Release(pMoniker);

		if (i == iDefaultDevice)
		{
		    FIXME("Default device\n");
		}

                CoTaskMemFree(pTypes);
	    }
	}
        res = DEVENUM_CreateAMCategoryKey(&CLSID_VideoInputDeviceCategory);
        if (SUCCEEDED(res))
            for (i = 0; i < 10; i++)
            {
                WCHAR szDeviceName[32], szDeviceVersion[32], szDevicePath[10];

                if (capGetDriverDescriptionW ((WORD) i,
                                              szDeviceName, sizeof(szDeviceName)/sizeof(WCHAR),
                                              szDeviceVersion, sizeof(szDeviceVersion)/sizeof(WCHAR)))
                {
                    IMoniker * pMoniker = NULL;
                    IPropertyBag * pPropBag = NULL;
                    WCHAR dprintf[] = { 'v','i','d','e','o','%','d',0 };
                    snprintfW(szDevicePath, sizeof(szDevicePath)/sizeof(WCHAR), dprintf, i);
                    /* The above code prevents 1 device with a different ID overwriting another */

                    rfp2.nMediaTypes = 1;
                    pTypes = CoTaskMemAlloc(rfp2.nMediaTypes * sizeof(REGPINTYPES));
                    if (!pTypes) {
                        IFilterMapper2_Release(pMapper);
                        return E_OUTOFMEMORY;
                    }

                    pTypes[0].clsMajorType = &MEDIATYPE_Video;
                    pTypes[0].clsMinorType = &MEDIASUBTYPE_None;

                    rfp2.lpMediaType = pTypes;

                    res = IFilterMapper2_RegisterFilter(pMapper,
                                                        &CLSID_VfwCapture,
                                                        szDeviceName,
                                                        &pMoniker,
                                                        &CLSID_VideoInputDeviceCategory,
                                                        szDevicePath,
                                                        &rf2);

                    if (pMoniker) {
                       OLECHAR wszVfwIndex[] = { 'V','F','W','I','n','d','e','x',0 };
                       VARIANT var;
                       V_VT(&var) = VT_I4;
                       V_UNION(&var, ulVal) = i;
                       res = IMoniker_BindToStorage(pMoniker, NULL, NULL, &IID_IPropertyBag, (LPVOID)&pPropBag);
                       if (SUCCEEDED(res))
                          res = IPropertyBag_Write(pPropBag, wszVfwIndex, &var);
                       IMoniker_Release(pMoniker);
                    }

                    if (i == iDefaultDevice) FIXME("Default device\n");
                    CoTaskMemFree(pTypes);
                }
            }
    }

    if (pMapper)
        IFilterMapper2_Release(pMapper);
    SetEvent(DEVENUM_populate_handle);
    return res;
}