bool AttachToWorkstation()
{
    DWORD dwThreadId;
 
    // Ensure connection to service window station and desktop, and 
    // save their handles. 

    hwinstaSave = GetProcessWindowStation(); 
    dwThreadId = GetCurrentThreadId(); 
    hdeskSave = GetThreadDesktop(dwThreadId); 
 
    // connect to the User's window station and desktop. 

    //RpcImpersonateClient(h); 
    hwinstaUser = OpenWindowStation("WinSta0", TRUE, MAXIMUM_ALLOWED); 
    if (hwinstaUser == NULL) 
    { 
        //RpcRevertToSelf();
	err_printf("AttachToWorkstation:OpenWindowStation failed, error %d.\n", GetLastError());
        return false; 
    } 
    SetProcessWindowStation(hwinstaUser); 
    hdeskUser = OpenInputDesktop(DF_ALLOWOTHERACCOUNTHOOK, TRUE, MAXIMUM_ALLOWED); 
    /*
	DESKTOP_CREATEMENU | DESKTOP_CREATEWINDOW | DESKTOP_ENUMERATE |
	DESKTOP_HOOKCONTROL | DESKTOP_JOURNALPLAYBACK | DESKTOP_JOURNALRECORD |
	DESKTOP_READOBJECTS | DESKTOP_SWITCHDESKTOP | DESKTOP_WRITEOBJECTS);
	*/
    //RpcRevertToSelf(); 
    if (hdeskUser == NULL) 
    { 
        SetProcessWindowStation(hwinstaSave); 
        CloseWindowStation(hwinstaUser);
	err_printf("AttachToWorkstation:OpenInputDesktop failed, error %d\n", GetLastError());
        return false;
    } 
    SetThreadDesktop(hdeskUser);

    return true;
}