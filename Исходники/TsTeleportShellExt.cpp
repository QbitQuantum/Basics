HRESULT CTsTeleportShellExt::GetVirtualChannelHandle(HANDLE *phFile)
{
    HRESULT hr = S_OK;

    HANDLE hWTSHandle = NULL;
    PVOID vcFileHandlePtr = NULL;

    //
    // Open Virtual channel
    //
    
    hWTSHandle = WTSVirtualChannelOpenEx(
        WTS_CURRENT_SESSION,
        TSTELE_CHANNEL_NAME,
        WTS_CHANNEL_OPTION_DYNAMIC);

    if (NULL == hWTSHandle)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
    }
    LEAVE_IF_FAILED("WTSVirtualChannelOpenEx failed");

    //
    // Get channel file handle
    //
  
    DWORD len;
    BOOL bSucc = WTSVirtualChannelQuery(
        hWTSHandle,
        WTSVirtualFileHandle,
        &vcFileHandlePtr,
        &len);

    if (!bSucc)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
    }
    LEAVE_IF_FAILED("WTSVirtualChannelQuery failed");

    if (len != sizeof(HANDLE))
    {
        hr = E_UNEXPECTED;
    }
    LEAVE_IF_FAILED("WTSVirtualChannelQuery return unexpected");

    HANDLE hWTSFileHandle = *(HANDLE *)vcFileHandlePtr;

    //
    // Duplicate handle so that we can close
    //
     
    bSucc = DuplicateHandle(
            GetCurrentProcess(),
            hWTSFileHandle,
            GetCurrentProcess(),
            phFile,
            0,
            FALSE,
            DUPLICATE_SAME_ACCESS);
    
    if (!bSucc)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
    }
    LEAVE_IF_FAILED("DuplicateHandle failed");

_Function_Exit:

    //
    // Cleanup
    //

    if (vcFileHandlePtr)
    {
        WTSFreeMemory(vcFileHandlePtr);
    }
    
    if (hWTSHandle)
    {
        WTSVirtualChannelClose(hWTSHandle);
    }

    return hr;
}