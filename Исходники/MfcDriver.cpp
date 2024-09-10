/*
** Function Name : MFC_Close
**
** Function Description : This function close MFC instance.
**                        The instance handle and memory block free here.
*/
BOOL
MFC_Close(
    DWORD OpenHandle
    )
{
    MFC_HANDLE *handle;
    BOOL        ret;

    handle = (MFC_HANDLE *) OpenHandle;
    if (handle == NULL)
        return FALSE;

    if(handle->pStrmBuf)
    {
        ret = VirtualFreeEx(handle->hUsrProc,    // HANDLE hProcess
                          handle->pStrmBuf,
                          0,
                          MEM_RELEASE);
        if (ret == FALSE)
            RETAILMSG(1, (L"\n[MFC_Close] VirtualFreeEx(STRM_BUF) returns FALSE.\n"));
    }

    if(handle->pFramBuf)
    {
        ret = VirtualFreeEx(handle->hUsrProc,    // HANDLE hProcess
                              handle->pFramBuf,
                              0,
                              MEM_RELEASE);
        if (ret == FALSE)
            RETAILMSG(1, (L"\n[MFC_Close] VirtualFreeEx(FRAM_BUF) returns FALSE.\n"));
    }

    if (handle->mfc_inst)
    {
        MFCInst_Delete(handle->mfc_inst);
    }

    free(handle);

    // Decrement OpenHandle Count
    InterlockedDecrement(&_openhandle_count);

    if (_openhandle_count == 1)
    {   // Remain Power Control handle only.
        // MFC is now sw-reset.
        Mfc_Clk_On();
        MfcReset();
        Mfc_Clk_Off();

        // MFC Power Off
        Mfc_Pwr_Off();
    }
    else if (_openhandle_count == 0)
    {
        RETAILMSG(1, (L"\n[MFC_Close] Power Manager Handle closed...\n"));
        gMfcHandlePower = NULL;
    }

    return TRUE;
}