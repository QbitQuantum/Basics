bool ProcessHelper::GetProcessID(QString path, quint32& dwPID) {

    path.replace("/", "\\");

    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
        return false;

    pe32.dwSize = sizeof(PROCESSENTRY32 );
    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);          // clean the snapshot object
        return(FALSE);
    }

    bool bRes = false;
    do {
        // Retrieve the priority class.
        dwPriorityClass = 0;
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
        if (hProcess)
        {
            CHAR lpPath[MAX_PATH];//will hold .exe path to be returned
            DWORD charsCarried = MAX_PATH; // holds size of path[], will then hold amount of characters returned by QueryFullProcessImageName
            QueryFullProcessImageNameA(hProcess, 0, lpPath, &charsCarried);
            CloseHandle(hProcess);

            QString curPath(lpPath);
            if (curPath.compare(path, Qt::CaseInsensitive) == 0) {
                bRes = true;
                dwPID = pe32.th32ProcessID;
                break;
            }
        }
    } while(Process32Next(hProcessSnap, &pe32));
    CloseHandle(hProcessSnap);
    return bRes;
}