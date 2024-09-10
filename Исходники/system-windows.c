//------------------------------------------------------------------------------
void system_stopSyncThread(void)
{
    CancelIoEx(syncThreadInstance_l.hSyncThreadHandle, NULL);

    // Signal to stop the thread and wait for the thread to terminate
    syncThreadInstance_l.fThreadExit = TRUE;
    WaitForSingleObject(syncThreadInstance_l.hSyncThreadHandle, 1000);
}