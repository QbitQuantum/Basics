static HRESULT DSPROPERTY_DescriptionW(
    LPVOID pPropData,
    ULONG cbPropData,
    PULONG pcbReturned )
{
    PDSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_W_DATA ppd = pPropData;
    HRESULT err;
    GUID dev_guid;
    ULONG wod, wid, wodn, widn;
    DSDRIVERDESC desc;

    TRACE("pPropData=%p,cbPropData=%d,pcbReturned=%p)\n",
          pPropData,cbPropData,pcbReturned);

    TRACE("DeviceId=%s\n",debugstr_guid(&ppd->DeviceId));
    if ( IsEqualGUID( &ppd->DeviceId , &GUID_NULL) ) {
        /* default device of type specified by ppd->DataFlow */
        if (ppd->DataFlow == DIRECTSOUNDDEVICE_DATAFLOW_CAPTURE) {
            TRACE("DataFlow=DIRECTSOUNDDEVICE_DATAFLOW_CAPTURE\n");
            ppd->DeviceId = DSDEVID_DefaultCapture;
        } else if (ppd->DataFlow == DIRECTSOUNDDEVICE_DATAFLOW_RENDER) {
            TRACE("DataFlow=DIRECTSOUNDDEVICE_DATAFLOW_RENDER\n");
            ppd->DeviceId = DSDEVID_DefaultPlayback;
        } else {
            WARN("DataFlow=Unknown(%d)\n", ppd->DataFlow);
            return E_PROP_ID_UNSUPPORTED;
        }
    }

    setup_dsound_options();

    GetDeviceID(&ppd->DeviceId, &dev_guid);

    wodn = waveOutGetNumDevs();
    widn = waveInGetNumDevs();
    wid = wod = dev_guid.Data4[7];
    if (!memcmp(&dev_guid, &DSOUND_renderer_guids[0], sizeof(GUID)-1)
        && wod < wodn)
    {
        ppd->DataFlow = DIRECTSOUNDDEVICE_DATAFLOW_RENDER;
        ppd->WaveDeviceId = wod;
    }
    else if (!memcmp(&dev_guid, &DSOUND_capture_guids[0], sizeof(GUID)-1)
             && wid < widn)
    {
        ppd->DataFlow = DIRECTSOUNDDEVICE_DATAFLOW_CAPTURE;
        ppd->WaveDeviceId = wid;
    }
    else
    {
        WARN("Device not found\n");
        return E_PROP_ID_UNSUPPORTED;
    }

    if (ppd->DataFlow == DIRECTSOUNDDEVICE_DATAFLOW_RENDER)
        err = waveOutMessage(UlongToHandle(wod),DRV_QUERYDSOUNDDESC,(DWORD_PTR)&desc,ds_hw_accel);
    else
        err = waveInMessage(UlongToHandle(wod),DRV_QUERYDSOUNDDESC,(DWORD_PTR)&desc,ds_hw_accel);

    if (err != MMSYSERR_NOERROR)
    {
        WARN("waveMessage(DRV_QUERYDSOUNDDESC) failed!\n");
        return E_PROP_ID_UNSUPPORTED;
    }
    else
    {
        /* FIXME: Still a memory leak.. */
        int desclen, modlen;
        static WCHAR wInterface[] = { 'I','n','t','e','r','f','a','c','e',0 };

        modlen = MultiByteToWideChar( CP_ACP, 0, desc.szDrvname, -1, NULL, 0 );
        desclen = MultiByteToWideChar( CP_ACP, 0, desc.szDesc, -1, NULL, 0 );
        ppd->Module = HeapAlloc(GetProcessHeap(),0,modlen*sizeof(WCHAR));
        ppd->Description = HeapAlloc(GetProcessHeap(),0,desclen*sizeof(WCHAR));
        ppd->Interface = wInterface;
        if (!ppd->Description || !ppd->Module)
        {
            WARN("Out of memory\n");
            HeapFree(GetProcessHeap(), 0, ppd->Description);
            HeapFree(GetProcessHeap(), 0, ppd->Module);
            ppd->Description = ppd->Module = NULL;
            return E_OUTOFMEMORY;
        }

        MultiByteToWideChar( CP_ACP, 0, desc.szDrvname, -1, ppd->Module, modlen );
        MultiByteToWideChar( CP_ACP, 0, desc.szDesc, -1, ppd->Description, desclen );
    }

    ppd->Type = DIRECTSOUNDDEVICE_TYPE_VXD;

    if (pcbReturned) {
        *pcbReturned = sizeof(*ppd);
        TRACE("*pcbReturned=%d\n", *pcbReturned);
    }

    return S_OK;
}