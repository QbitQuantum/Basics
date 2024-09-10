void InjectDLL32( LPPROCESS_INFORMATION ppi, LPCTSTR dll )
{
  CONTEXT context;
  DWORD   len;
  LPVOID  mem;
  DWORD   mem32;
  #define CODESIZE 20
  BYTE	  code[CODESIZE+TSIZE(MAX_PATH)];
  union
  {
    PBYTE  pB;
    PDWORD pL;
  } ip;

#ifdef IMPORT_WOW64
  if (Wow64GetThreadContext == 0)
  {
    #define GETPROC( proc ) proc = (T##proc)GetProcAddress( hKernel, #proc )
    HMODULE hKernel = GetModuleHandle( L"kernel32.dll" );
    GETPROC( Wow64GetThreadContext );
    GETPROC( Wow64SetThreadContext );
    // Assume if one is defined, so is the other.
    if (Wow64GetThreadContext == 0)
    {
      DEBUGSTR( 1, L"Failed to get pointer to Wow64GetThreadContext." );
      return;
    }
  }
#endif

  len = TSIZE(lstrlen( dll ) + 1);
  if (len > TSIZE(MAX_PATH))
    return;

  if (LLW32 == 0)
  {
#ifdef _WIN64
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    // ...ANSI32.dll\0
    CopyMemory( code, dll, len - TSIZE(7) );
    // ...ANSI-LLW.exe\0
    CopyMemory( code + len - TSIZE(7), L"-LLW.exe", TSIZE(9) );
    if (!CreateProcess( (LPCTSTR)code, NULL, NULL, NULL, FALSE, 0, NULL, NULL,
			&si, &pi ))
    {
      DEBUGSTR( 1, L"Failed to execute \"%s\".", (LPCTSTR)code );
      return;
    }
    WaitForSingleObject( pi.hProcess, INFINITE );
    GetExitCodeProcess( pi.hProcess, &LLW32 );
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
#else
    LLW32 = (DWORD)GetProcAddress( GetModuleHandle( L"kernel32.dll" ),
						     "LoadLibraryW" );
#endif
  }

  CopyMemory( code + CODESIZE, dll, len );
  len += CODESIZE;

  context.ContextFlags = CONTEXT_CONTROL;
  GetThreadContext( ppi->hThread, &context );
  mem = VirtualAllocEx( ppi->hProcess, NULL, len, MEM_COMMIT,
			PAGE_EXECUTE_READWRITE );
  mem32 = (DWORD)(DWORD_PTR)mem;

  ip.pB = code;

  *ip.pB++ = 0x68;			// push  eip
  *ip.pL++ = context.Eip;
  *ip.pB++ = 0x9c;			// pushf
  *ip.pB++ = 0x60;			// pusha
  *ip.pB++ = 0x68;			// push  L"path\to\ANSI32.dll"
  *ip.pL++ = mem32 + CODESIZE;
  *ip.pB++ = 0xe8;			// call  LoadLibraryW
  *ip.pL++ = LLW32 - (mem32 + (DWORD)(ip.pB+4 - code));
  *ip.pB++ = 0x61;			// popa
  *ip.pB++ = 0x9d;			// popf
  *ip.pB++ = 0xc3;			// ret

  WriteProcessMemory( ppi->hProcess, mem, code, len, NULL );
  FlushInstructionCache( ppi->hProcess, mem, len );
  context.Eip = mem32;
  SetThreadContext( ppi->hThread, &context );
}