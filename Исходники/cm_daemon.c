void cm_IpAddrDaemon(long parm)
{
    extern void smb_CheckVCs(void);
    char * name = "cm_IPAddrDaemon_ShutdownEvent";

    cm_IPAddrDaemon_ShutdownEvent = thrd_CreateEvent(NULL, FALSE, FALSE, name);
    if ( GetLastError() == ERROR_ALREADY_EXISTS )
        afsi_log("Event Object Already Exists: %s", name);

    rx_StartClientThread();

    while (daemon_ShutdownFlag == 0) {
	DWORD Result;
        
        thrd_SetEvent(cm_IPAddrDaemon_ShutdownEvent);
        Result = NotifyAddrChange(NULL,NULL);
        if (Result == NO_ERROR && daemon_ShutdownFlag == 0) {
            lastIPAddrChange = osi_Time();
            smb_SetLanAdapterChangeDetected();
            cm_SetLanAdapterChangeDetected();
            thrd_ResetEvent(cm_IPAddrDaemon_ShutdownEvent);
	}	
    }

    thrd_SetEvent(cm_IPAddrDaemon_ShutdownEvent);
}