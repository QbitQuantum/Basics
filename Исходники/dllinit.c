BOOL GdiProcessSetup()
{
    NTSTATUS status;
    PTEB pteb = NtCurrentTeb();

    // who ever calls this first needs to initialize the global variables.

    if (gbFirst)
    {

    #ifdef GL_METAFILE

        //
        // Initialize the GL metafile support semaphore
        //

        status = (NTSTATUS)INITIALIZECRITICALSECTION(&semGlLoad);
        if (!NT_SUCCESS(status))
        {
            WARNING("InitializeCriticalSection failed\n");
            return FALSE;
        }

    #endif

        //
        // Initialize the local semaphore and reserve the Local Handle Table
        // for the process.
        //

        status = (NTSTATUS)INITIALIZECRITICALSECTION(&semLocal);
        if (!NT_SUCCESS(status))
        {
            WARNING("InitializeCriticalSection failed\n");
            return(FALSE);
        }

        pAFRTNodeList = NULL;
        guintAcp = GetACP();

        if(IS_ANY_DBCS_CODEPAGE(guintAcp))
        {
        // if the default code page is a DBCS code page then set guintACP to 1252
        // since we want to compute client wide widths for SBCS fonts for code page
        // 1252 in addition to DBCS fonts for the default code page

            vSetCheckDBCSTrailByte(guintAcp);
            guintDBCScp = guintAcp;
            guintAcp = 1252;
        }
        else
        {
            guintDBCScp = 0xFFFFFFFF;  // assume this will never be a valid CP
        }

#ifdef FE_SB
        fFontAssocStatus = NtGdiQueryFontAssocInfo(NULL);
#endif        
        
        // assign unique process ID

        gW32PID = (W32PID)pteb->ClientId.UniqueProcess;

        //
        // !!! Add back in thread attatck and detach
        //
        //LdrDisableThreadCalloutsForDll(pvDllHandle);
        //

        gbFirst = FALSE;
    }

    // The pshared handle table needs to be set everytime this routine gets
    // called in case the PEB doesn't have it yet for the first.

    pGdiSharedMemory      = (PGDI_SHARED_MEMORY) NtCurrentPeb()->GdiSharedHandleTable;
    pGdiSharedHandleTable = pGdiSharedMemory->aentryHmgr;
    pGdiDevCaps           = &pGdiSharedMemory->DevCaps;

    GdiBatchLimit         = (ULONG)NtCurrentPeb()->GdiDCAttributeList & 0xff;
    pGdiHandleCache       = (PGDIHANDLECACHE)(&NtCurrentPeb()->GdiHandleBuffer[0]);

    return(TRUE);
}