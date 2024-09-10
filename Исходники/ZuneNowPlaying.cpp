BOOL AppIsAlreadyRunning()
{
    BOOL bRunning=FALSE;
    CString strAppName;
    strAppName = "ZuneNowPlaying.exe";
    DWORD dwOwnPID = GetProcessId(GetCurrentProcess());
    HANDLE hSnapShot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    PROCESSENTRY32* processInfo=new PROCESSENTRY32;
    processInfo->dwSize=sizeof(PROCESSENTRY32);
    int index=0;
    while(Process32Next(hSnapShot,processInfo)!=FALSE)
    {
		CString pName = (LPCWSTR)processInfo->szExeFile;
		if (pName.CompareNoCase(strAppName) == 0)
        {
            if (processInfo->th32ProcessID != dwOwnPID)
            {
                bRunning=TRUE;
                break;
            }
        }
    }
    CloseHandle(hSnapShot);
    delete processInfo;
    return bRunning;
}