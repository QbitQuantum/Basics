/***************************************************************************
 * DirectSoundCaptureEnumerateW [DSOUND.8]
 *
 * Enumerate all DirectSound drivers installed in the system.
 *
 * PARAMS
 *    lpDSEnumCallback  [I] Address of callback function.
 *    lpContext         [I] Address of user defined context passed to callback function.
 *
 * RETURNS
 *    Success: DS_OK
 *    Failure: DSERR_INVALIDPARAM
 */
HRESULT WINAPI
DirectSoundCaptureEnumerateW(
    LPDSENUMCALLBACKW lpDSEnumCallback,
    LPVOID lpContext)
{
    unsigned devs, wid;
    DSDRIVERDESC desc;
    GUID guid;
    int err;
    WCHAR wDesc[MAXPNAMELEN];
    WCHAR wName[MAXPNAMELEN];

    TRACE("(%p,%p)\n", lpDSEnumCallback, lpContext );

    if (lpDSEnumCallback == NULL) {
	WARN("invalid parameter: lpDSEnumCallback == NULL\n");
        return DSERR_INVALIDPARAM;
    }

    setup_dsound_options();

    devs = waveInGetNumDevs();
    if (devs > 0) {
	if (GetDeviceID(&DSDEVID_DefaultCapture, &guid) == DS_OK) {
	    for (wid = 0; wid < devs; ++wid) {
                if (IsEqualGUID( &guid, &DSOUND_capture_guids[wid] ) ) {
                    err = mmErr(waveInMessage(UlongToHandle(wid),DRV_QUERYDSOUNDDESC,(DWORD_PTR)&desc,ds_hw_accel));
                    if (err == DS_OK) {
                        TRACE("calling lpDSEnumCallback(NULL,\"%s\",\"%s\",%p)\n",
                              "Primary Sound Capture Driver",desc.szDrvname,lpContext);
                        MultiByteToWideChar( CP_ACP, 0, "Primary Sound Capture Driver", -1,
                                             wDesc, sizeof(wDesc)/sizeof(WCHAR) );
                        MultiByteToWideChar( CP_ACP, 0, desc.szDrvname, -1,
                                             wName, sizeof(wName)/sizeof(WCHAR) );
                        wName[(sizeof(wName)/sizeof(WCHAR)) - 1] = '\0';

                        if (lpDSEnumCallback(NULL, wDesc, wName, lpContext) == FALSE)
                            return DS_OK;
                    }
                }
	    }
	}
    }

    for (wid = 0; wid < devs; ++wid) {
        err = mmErr(waveInMessage(UlongToHandle(wid),DRV_QUERYDSOUNDDESC,(DWORD_PTR)&desc,ds_hw_accel));
	if (err == DS_OK) {
            TRACE("calling lpDSEnumCallback(%s,\"%s\",\"%s\",%p)\n",
                  debugstr_guid(&DSOUND_capture_guids[wid]),desc.szDesc,desc.szDrvname,lpContext);
            MultiByteToWideChar( CP_ACP, 0, desc.szDesc, -1,
                                 wDesc, sizeof(wDesc)/sizeof(WCHAR) );
            wDesc[(sizeof(wDesc)/sizeof(WCHAR)) - 1] = '\0';

            MultiByteToWideChar( CP_ACP, 0, desc.szDrvname, -1,
                                 wName, sizeof(wName)/sizeof(WCHAR) );
            wName[(sizeof(wName)/sizeof(WCHAR)) - 1] = '\0';

            if (lpDSEnumCallback(&DSOUND_capture_guids[wid], wDesc, wName, lpContext) == FALSE)
                return DS_OK;
	}
    }

    return DS_OK;
}