void ExecScript(int log) {
  char szRet[128] = "";
  char *pExec;
  int nComSpecSize;
  char meDLLPath[MAX_PATH];    
  char *p;
  char *executor;
  char *g_exec;
  unsigned int g_to;

  nComSpecSize = GetModuleFileName(g_hInst, meDLLPath, MAX_PATH) + 2; // 2 chars for quotes
  p = meDLLPath + nComSpecSize - 2; // point p at null char of meDLLPath
  g_exec = (char *)GlobalAlloc(GPTR, sizeof(char)*g_stringsize+nComSpecSize+2); // 1 for space, 1 for null
  *g_exec = '"';
  executor = g_exec + 1;

  do
  {
    if (*p == '\\')
      break;
    p = CharPrev(meDLLPath, p);
  }
  while (p > meDLLPath);
  if (p == meDLLPath)
  {
    // bad path
    lstrcpy(szRet, "error");
    goto done;
  }

  *p = 0;
  GetTempFileName(meDLLPath, "ns", 0, executor);
  *p = '\\';
  if (CopyFile(meDLLPath, executor, FALSE))
  {
    HANDLE hFile, hMapping;
    LPBYTE pMapView;
    PIMAGE_NT_HEADERS pNTHeaders;
    hFile = CreateFile(executor, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING,0, 0);
    hMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);
    pMapView = MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, 0);
    if (pMapView)
    {
      pNTHeaders = (PIMAGE_NT_HEADERS)(pMapView + ((PIMAGE_DOS_HEADER)pMapView)->e_lfanew);
      pNTHeaders->FileHeader.Characteristics = IMAGE_FILE_32BIT_MACHINE | IMAGE_FILE_LOCAL_SYMS_STRIPPED | 
        IMAGE_FILE_LINE_NUMS_STRIPPED | IMAGE_FILE_EXECUTABLE_IMAGE;
      pNTHeaders->OptionalHeader.Subsystem = IMAGE_SUBSYSTEM_WINDOWS_CUI;
      pNTHeaders->OptionalHeader.AddressOfEntryPoint = (DWORD)WinMain - (DWORD)g_hInst;  
      UnmapViewOfFile(pMapView);
    }
    CloseHandle(hMapping);
    CloseHandle(hFile);
  }

  lstrcat(g_exec, "\"");

  g_to = 0; // default is no timeout

  g_hwndList = FindWindowEx(FindWindowEx(g_hwndParent,NULL,"#32770",NULL),NULL,"SysListView32",NULL);

  // add space
  pExec = g_exec + lstrlen(g_exec);
  *pExec = ' ';
  pExec++;
  
  popstring(pExec);
  if (my_strstr(pExec, "/TIMEOUT=")) {
    char *szTimeout = pExec + 9;
    g_to = my_atoi(szTimeout);
    popstring(pExec);
  }

  if (!g_exec[0]) 
  {
    lstrcpy(szRet, "error");
    goto done;
  }
  
  {
    STARTUPINFO si={sizeof(si),};
    SECURITY_ATTRIBUTES sa={sizeof(sa),};
    SECURITY_DESCRIPTOR sd={0,};
    PROCESS_INFORMATION pi={0,};
    OSVERSIONINFO osv={sizeof(osv)};
    HANDLE newstdout=0,read_stdout=0;
    HANDLE newstdin=0,read_stdin=0;
    DWORD dwRead = 1;
    DWORD dwExit = !STILL_ACTIVE;
    DWORD dwLastOutput;
    static char szBuf[1024];
    HGLOBAL hUnusedBuf;
    char *szUnusedBuf = 0;

    if (log) {
      hUnusedBuf = GlobalAlloc(GHND, log & 2 ? g_stringsize : sizeof(szBuf)*4);
      if (!hUnusedBuf) {
        lstrcpy(szRet, "error");
        goto done;
      }
      szUnusedBuf = (char *)GlobalLock(hUnusedBuf);
    }

    GetVersionEx(&osv);
    if (osv.dwPlatformId == VER_PLATFORM_WIN32_NT) {
      InitializeSecurityDescriptor(&sd,SECURITY_DESCRIPTOR_REVISION);
      SetSecurityDescriptorDacl(&sd,true,NULL,false);
      sa.lpSecurityDescriptor = &sd;
    }
    else 
      sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = true;
    if (!CreatePipe(&read_stdout,&newstdout,&sa,0)) {
      lstrcpy(szRet, "error");
      goto done;
    }
    if (!CreatePipe(&read_stdin,&newstdin,&sa,0)) {
      lstrcpy(szRet, "error");
      goto done;
    }

    GetStartupInfo(&si);
    si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    si.hStdInput = newstdin;
    si.hStdOutput = newstdout;
    si.hStdError = newstdout;
    if (!CreateProcess(NULL,g_exec,NULL,NULL,TRUE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi)) {
      lstrcpy(szRet, "error");
      goto done;
    }

    dwLastOutput = GetTickCount();

    while (dwExit == STILL_ACTIVE || dwRead) {
      PeekNamedPipe(read_stdout, 0, 0, 0, &dwRead, NULL);
      if (dwRead) {
        dwLastOutput = GetTickCount();
        ReadFile(read_stdout, szBuf, sizeof(szBuf)-1, &dwRead, NULL);
        szBuf[dwRead] = 0;
        if (log) {
          char *p, *p2;
          SIZE_T iReqLen = lstrlen(szBuf) + lstrlen(szUnusedBuf);
          if (GlobalSize(hUnusedBuf) < iReqLen && (iReqLen < g_stringsize || !(log & 2))) {
            GlobalUnlock(hUnusedBuf);
            hUnusedBuf = GlobalReAlloc(hUnusedBuf, iReqLen+sizeof(szBuf), GHND);
            if (!hUnusedBuf) {
              lstrcpy(szRet, "error");
              break;
            }
            szUnusedBuf = (char *)GlobalLock(hUnusedBuf);
          }
          p = szUnusedBuf; // get the old left overs
          if (iReqLen < g_stringsize || !(log & 2)) lstrcat(p, szBuf);
          else {
            lstrcpyn(p + lstrlen(p), szBuf, g_stringsize - lstrlen(p));
          }

          if (!(log & 2)) {
            while (p = my_strstr(p, "\t")) {
              if ((int)(p - szUnusedBuf) > (int)(GlobalSize(hUnusedBuf) - TAB_REPLACE_SIZE - 1))
              {
                *p++ = ' ';
              }
              else
              {
                int len = lstrlen(p);
                char *c_out=(char*)p+TAB_REPLACE_SIZE+len;
                char *c_in=(char *)p+len;
                while (len-- > 0) {
                  *c_out--=*c_in--;
                }

                lstrcpy(p, TAB_REPLACE);
                p += TAB_REPLACE_SIZE;
                *p = ' ';
              }
            }
            
            p = szUnusedBuf; // get the old left overs
            for (p2 = p; *p2;) {
              if (*p2 == '\r') {
                *p2++ = 0;
                continue;
              }
              if (*p2 == '\n') {
                *p2 = 0;
                while (!*p && p != p2) p++;
                LogMessage(p);
                p = ++p2;
                continue;
              }
              p2 = CharNext(p2);
            }
            
            // If data was taken out from the unused buffer, move p contents to the start of szUnusedBuf
            if (p != szUnusedBuf) {
              char *p2 = szUnusedBuf;
              while (*p) *p2++ = *p++;
              *p2 = 0;
            }
          }
        }
      }
      else {
        if (g_to && GetTickCount() > dwLastOutput+g_to) {
          TerminateProcess(pi.hProcess, -1);
          lstrcpy(szRet, "timeout");
        }
        else Sleep(LOOPTIMEOUT);
      }
      GetExitCodeProcess(pi.hProcess, &dwExit);
      if (dwExit != STILL_ACTIVE) {
        PeekNamedPipe(read_stdout, 0, 0, 0, &dwRead, NULL);
      }
    }
done:
    if (log & 2) pushstring(szUnusedBuf);
    if (log & 1 && *szUnusedBuf) LogMessage(szUnusedBuf);
    if ( dwExit == STATUS_ILLEGAL_INSTRUCTION )
      lstrcpy(szRet, "error");
    if (!szRet[0]) wsprintf(szRet,"%d",dwExit);
    pushstring(szRet);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    CloseHandle(newstdout);
    CloseHandle(read_stdout);
    CloseHandle(newstdin);
    CloseHandle(read_stdin);
    *(pExec-2) = '\0'; // skip space and quote
    DeleteFile(executor);
    GlobalFree(g_exec);
    if (log) {
      GlobalUnlock(hUnusedBuf);
      GlobalFree(hUnusedBuf);
    }
  }
}