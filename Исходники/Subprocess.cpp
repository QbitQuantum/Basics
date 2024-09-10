bool CSubprocess::PSExtract(CSubprocess::PInfoArray &arPinfo)
{
  bool rc=false;
  arPinfo.clear();
  // If Windows NT:
  switch(GetPlatform()) {
  case VER_PLATFORM_WIN32_NT:
    if(hInstLib1) {
      
      // Get procedure addresses.
      static BOOL (WINAPI *lpfEnumProcesses)( DWORD *, DWORD cb, DWORD * ) = (BOOL(WINAPI *)(DWORD *,DWORD,DWORD*))GetProcAddress( hInstLib1, "EnumProcesses" ) ;
      if( lpfEnumProcesses) {
        
        if(hInstLib2) {
          
          static DWORD (WINAPI *lpfNtQueryInformationProcess)( HANDLE, int, void *, DWORD, LPDWORD ) =
            (DWORD(WINAPI *)(HANDLE, int, void *, DWORD, LPDWORD)) GetProcAddress( hInstLib2,"NtQueryInformationProcess" ) ;
          
          if(lpfNtQueryInformationProcess){
            DWORD dwMaxPids=256;
            DWORD dwPidSize;
            DWORD *arPids = NULL ;
            do {
              delete [] arPids;
              arPids=new DWORD[dwMaxPids];
            } while(lpfEnumProcesses(arPids, dwMaxPids, &dwPidSize) && dwPidSize/sizeof(DWORD)==dwMaxPids) ;
            
            if(dwPidSize/sizeof(DWORD)<dwMaxPids){
              rc=true;
              for( DWORD dwIndex = 0 ; dwIndex < dwPidSize/sizeof(DWORD); dwIndex++ ) {
                // Regardless of OpenProcess success or failure, we
                // still call the enum func with the ProcID.
                DWORD pid=arPids[dwIndex];
                HANDLE hProcess=::OpenProcess( PROCESS_QUERY_INFORMATION, FALSE, pid ); 
                if (hProcess ) {
                  struct {
                    DWORD ExitStatus; // receives process termination status
                    DWORD PebBaseAddress; // receives process environment block address
                    DWORD AffinityMask; // receives process affinity mask
                    DWORD BasePriority; // receives process priority class
                    ULONG UniqueProcessId; // receives process identifier
                    ULONG InheritedFromUniqueProcessId; // receives parent process identifier
                  } pbi;
                  memset( &pbi, 0, sizeof(pbi)); 
                  DWORD retLen; 
                  __int64 ftCreation,ftExit,ftKernel,ftUser;
                  if(lpfNtQueryInformationProcess(hProcess, 0 /*ProcessBasicInformation*/, &pbi, sizeof(pbi), &retLen)>=0 &&
                    TRUE==::GetProcessTimes (hProcess,(FILETIME *)&ftCreation,(FILETIME *)&ftExit,(FILETIME *)&ftKernel,(FILETIME *)&ftUser)){
                    // The second test is important.  It excludes orphaned processes who appear to have been adopted by virtue of a new
                    // process having been created with the same ID as their original parent.
                    PInfo p;
                    p.PID=pid;
                    p.PPID=pbi.InheritedFromUniqueProcessId;
                    p.tCreation=ftCreation;
                    p.tCpu=Time((ftKernel+ftUser)/10000);
                    arPinfo.push_back(p);
                  }
                  
                  CloseHandle(hProcess); 

                }
              }
            }
            delete [] arPids;
          }          
        }
      }      
    }
    break;
  case VER_PLATFORM_WIN32_WINDOWS:
    
    if( hInstLib1) {
      
      static HANDLE (WINAPI *lpfCreateToolhelp32Snapshot)(DWORD,DWORD)=
        (HANDLE(WINAPI *)(DWORD,DWORD))GetProcAddress( hInstLib1,"CreateToolhelp32Snapshot" ) ;
      static BOOL (WINAPI *lpfProcess32First)(HANDLE,LPPROCESSENTRY32)=
        (BOOL(WINAPI *)(HANDLE,LPPROCESSENTRY32))GetProcAddress( hInstLib1, "Process32First" ) ;
      static BOOL (WINAPI *lpfProcess32Next)(HANDLE,LPPROCESSENTRY32)=
        (BOOL(WINAPI *)(HANDLE,LPPROCESSENTRY32))GetProcAddress( hInstLib1, "Process32Next" ) ;
      if( lpfProcess32Next && lpfProcess32First && lpfCreateToolhelp32Snapshot) {
        
        // Get a handle to a Toolhelp snapshot of the systems
        // processes.
        HANDLE hSnapShot = lpfCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) ;
        if(INVALID_HANDLE_VALUE != hSnapShot) {
          // Get the first process' information.
          PROCESSENTRY32 procentry;
          procentry.dwSize = sizeof(PROCESSENTRY32) ;
          if(lpfProcess32First( hSnapShot, &procentry )){
            rc=true;
            do {
              PInfo p;
              p.PID=procentry.th32ProcessID;
              p.PPID=procentry.th32ParentProcessID;
              arPinfo.push_back(p);
            } while(lpfProcess32Next( hSnapShot, &procentry ));
          }
          CloseHandle(hSnapShot);
        }
      }
    }
    break;
  default:
    break;
  }    

  SetParents(arPinfo);

  if(!rc){
    ERROR(_T("Couldn't get process information!\n"));
  }
  return rc;
}