static int beginMonitor(VPLFS_MonitorHandle_t* handle)
{
    // VPL_REPORT_INFO("beginMonitor called");
    int rv = 0;
    handle->overlapped.Internal = 0;
    handle->overlapped.InternalHigh = 0;
    handle->overlapped.Offset = 0;
    handle->overlapped.OffsetHigh = 0;
    handle->overlapped.hEvent = handle;  // hEvent not used by system, used as ctx ptr.
#ifdef VPL_PLAT_IS_WINRT
    // TODO: using WinRT APIs to implement file monitor
    rv = VPL_ERR_NOOP;
#else
    if(!ReadDirectoryChangesW(handle->hDir,
                              handle->pBuffer, //<--FILE_NOTIFY_INFORMATION records are put into this buffer
                              handle->nBufferLength,
                              TRUE,
                              FILE_NOTIFY_CHANGE_FILE_NAME|
                                  FILE_NOTIFY_CHANGE_DIR_NAME|
                                  FILE_NOTIFY_CHANGE_SIZE|
                                  FILE_NOTIFY_CHANGE_LAST_WRITE|
                                  FILE_NOTIFY_CHANGE_CREATION,
                              NULL, // Only defined for synchronous calls.
                              &handle->overlapped,
                              &ChDirCompletionRoutine) )
    {
       rv = VPLError_GetLastWinError();
    }
#endif
    return rv;
}