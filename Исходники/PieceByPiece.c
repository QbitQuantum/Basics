BOOL GetProcessModule (DWORD dwPID, DWORD dwModuleID,
     LPMODULEENTRY32 lpMe32, DWORD cbMe32) 
{ 
    BOOL          bRet        = FALSE; 
    BOOL          bFound      = FALSE; 
    HANDLE        hModuleSnap = NULL; 
    MODULEENTRY32 me32        = {0}; 
 
    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID); 
    if (hModuleSnap == (HANDLE)-1) 
        return (FALSE); 
 
    me32.dwSize = sizeof(MODULEENTRY32); 
 
   if (Module32First(hModuleSnap, &me32)) 
    { 
        do 
        { 
            if (me32.th32ModuleID == dwModuleID) 
            { 
                CopyMemory (lpMe32, &me32, cbMe32); 
                bFound = TRUE; 
            } 
        } 
        while (!bFound && Module32Next(hModuleSnap, &me32)); 
 
        bRet = bFound;  
    } 
    else 
        bRet = FALSE;
    CloseHandle (hModuleSnap); 
 
    return (bRet); 
} 