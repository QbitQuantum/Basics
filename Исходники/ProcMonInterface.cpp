//-----------------------------------------------------------------------------
// Name: CallBacksThreadProc
// Object: thread launched on each events
// Parameters :
//     in  : PPROC_MON_THREAD_CALLBACK_PARAM Param : call back parameters
//     out : 
//     return : TRUE on success, FALSE on error
//-----------------------------------------------------------------------------
DWORD WINAPI CProcMonInterface::CallBacksThreadProc(PPROC_MON_THREAD_CALLBACK_PARAM Param)
{
    PROC_MON_CALLBACK pfunc;
    // switch process creation flag
    if (Param->ProcInfo.bCreate)
        pfunc=Param->pProcMonInterface->StartProcCallBack;
    else
        pfunc=Param->pProcMonInterface->StopProcCallBack;

    // check call back pointer
    if (!IsBadCodePtr((FARPROC)pfunc))
        // call the callback
        pfunc(Param->ProcInfo.hParentId,Param->ProcInfo.hProcessId);

    // free allocated memory
    HeapFree(GetProcessHeap(),0,Param);

    return 0;
}