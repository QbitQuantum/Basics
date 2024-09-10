DWORD FindProcess(TCHAR *szName) 
{ 
  HINSTANCE            hProcessSnap   = NULL; 
  PROCESSENTRY32    pe32           = {0}; 
  DWORD                dwTaskCount    = 0; 
  
  hProcessSnap = (HINSTANCE)CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPNOHEAPS, 0); 
  if (hProcessSnap == (HANDLE)-1) return 0; 

  dwTaskCount = 0; 
  pe32.dwSize = sizeof(PROCESSENTRY32);   // must be filled out before use 
  if (Process32First(hProcessSnap, &pe32)) { 
    do { 
      if (_wcsicmp(pe32.szExeFile,szName)==0) 
     { 
        CloseToolhelp32Snapshot(hProcessSnap); 
        return pe32.th32ProcessID; 
     } 
    } 
    while (Process32Next(hProcessSnap, &pe32)); 
  } 
  CloseToolhelp32Snapshot(hProcessSnap); 
  return 0; 
} 