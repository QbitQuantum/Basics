HRESULT CCamMicro::Init(__in PTSTR ptszMicroDriverName, MCAM_DEVICE_INFO **ppDeviceInfo)
{
    DBG_FN("CCamMicro::CCamMicro");

    HRESULT hr = S_OK;

    //
    // Load the camera microdriver
    //
    m_hModule = LoadLibrary(ptszMicroDriverName);
    REQUIRE_FILEHANDLE(m_hModule, hr, "CCamMicro::CCamMicro", "LoadLibrary failed");

    GET_PROC_ADDRESS(Init);
    GET_PROC_ADDRESS(UnInit);
    GET_PROC_ADDRESS(Open);
    GET_PROC_ADDRESS(Close);
    GET_PROC_ADDRESS(GetDeviceInfo);
    GET_PROC_ADDRESS(ReadEvent);
    GET_PROC_ADDRESS(StopEvents);
    GET_PROC_ADDRESS(GetItemInfo);
    GET_PROC_ADDRESS(FreeItemInfo);
    GET_PROC_ADDRESS(GetThumbnail);
    GET_PROC_ADDRESS(GetItemData);
    GET_PROC_ADDRESS(DeleteItem);
    GET_PROC_ADDRESS(SetItemProt);
    GET_PROC_ADDRESS(TakePicture);
    GET_PROC_ADDRESS(Status);
    GET_PROC_ADDRESS(Reset);

    if (m_pInit) {
        hr = m_pInit(ppDeviceInfo);
    }
    else {
        wiauDbgError("CCamMicro::Init", "m_pInit not initialized");
        hr = E_FAIL;
    }

Cleanup:
    return hr;
}