// The primary exception filter
LONG WINAPI BWAPIExceptionFilter(EXCEPTION_POINTERS *ep)
{
  // Destroy fullscreen mode and show the cursor (something the original doesn't do!)
  DDrawDestroy();
  ShowCursor(TRUE);

  // Create the log file path
  char szLogFilename[MAX_PATH];
  time_t myTime = time(nullptr);
  strftime(szLogFilename, sizeof(szLogFilename), "Errors\\%Y %b %d.txt", localtime(&myTime));
  
  // Create the file
  FILE *hFile = fopen( (installPath + szLogFilename).c_str(), "a+");
  if ( hFile )
  {
    fprintf(hFile, "\n//////////////////////////////////////////////////\n");

    // Print the time
    fprintf(hFile, "TIME: %s\n", ctime(&myTime));

    // Print version data
    WORD w1,w2,w3,w4;
    GetCurrentProductVersion(w1, w2, w3, w4);
    fprintf(hFile, "VERSION: %hu.%hu.%hu.%hu\n", w1, w2, w3, w4);

    // BWAPI/Broodwar specific
    fprintf(hFile, "BWAPI:\n");
    fprintf(hFile, "  REVISION: %d\n", BWAPI::BroodwarImpl.getRevision());
    fprintf(hFile, "  BUILD: %s\n", BWAPI::BroodwarImpl.isDebug() ? "DEBUG" : "RELEASE");
    fprintf(hFile, "  ERROR: %s\n", BWAPI::BroodwarImpl.getLastError().c_str());
    fprintf(hFile, "  LOCATION: %s %s\n", BWAPI::BroodwarImpl.isMultiplayer() ? (BWAPI::BroodwarImpl.isBattleNet() ? "Battle.net" : "Multiplayer") : "Single Player", BWAPI::BroodwarImpl.isReplay() ? "Replay" : "");
    
    if ( BWAPI::BroodwarImpl.isInGame() )
    {
      fprintf(hFile, "MAP: %s\n     %s\n", BWAPI::BroodwarImpl.mapName().c_str(), BWAPI::BroodwarImpl.mapFileName().c_str());
      NULLCHECK(BWAPI::BroodwarImpl.self());
      NULLCHECK(BWAPI::BroodwarImpl.enemy());
      NULLCHECK(BWAPI::BroodwarImpl.neutral());
      if ( BWAPI::BroodwarImpl.hAIModule && !BWAPI::BroodwarImpl.client )
        fprintf(hFile, "\"Broodwar\" pointer was not initialized for AI module.\n");
      if ( BWAPI::BroodwarImpl.hTournamentModule && !BWAPI::BroodwarImpl.tournamentAI )
        fprintf(hFile, "\"Broodwar\" pointer was not initialized for Tournament module.\n");
    }

    // Print the exception info
    DWORD dwExceptionCode = ep->ExceptionRecord->ExceptionCode;
    fprintf(hFile, "\nEXCEPTION: 0x%08X    %s\n", dwExceptionCode, GetExceptionName(dwExceptionCode));

    // Store exception address
    PVOID pExceptionAddr = ep->ExceptionRecord->ExceptionAddress;

    // Print offending module info
    fprintf(hFile, "FAULT:     0x%p    %s\n", pExceptionAddr, getModuleNameFrom(pExceptionAddr).c_str());

    // Print register information
    fprintf(hFile, "REGISTERS:\n");
    DWORD dwCntxtFlags = ep->ContextRecord->ContextFlags;
    if ( dwCntxtFlags & CONTEXT_INTEGER )
      fprintf(hFile,  "  EDI: %08X\n"
              "  ESI: %08X\n"
              "  EBX: %08X\n"
              "  EDX: %08X\n"
              "  ECX: %08X\n"
              "  EAX: %08X\n",
              ep->ContextRecord->Edi,
              ep->ContextRecord->Esi,
              ep->ContextRecord->Ebx,
              ep->ContextRecord->Edx,
              ep->ContextRecord->Ecx,
              ep->ContextRecord->Eax);
    if ( dwCntxtFlags & CONTEXT_CONTROL )
      fprintf(hFile,  "  EBP: %08X\n"
              "  EIP: %08X\n"
              "  ESP: %08X\n",
              ep->ContextRecord->Ebp,
              ep->ContextRecord->Eip,
              ep->ContextRecord->Esp);

    // Get the stack frame
    STACKFRAME sf = { 0 };
    sf.AddrPC.Mode    = AddrModeFlat;
    sf.AddrPC.Offset  = ep->ContextRecord->Eip;
    sf.AddrFrame.Mode  = AddrModeFlat;
    sf.AddrFrame.Offset = ep->ContextRecord->Ebp;
    sf.AddrStack.Mode  = AddrModeFlat;
    sf.AddrStack.Offset = ep->ContextRecord->Esp;

    // Create a context record copy
    CONTEXT c = *ep->ContextRecord;

    // Do the stack trace
    fprintf(hFile, "STACK:\n");

    // Get frequently used handles
    HANDLE hProcess = GetCurrentProcess();
    HANDLE hThread  = GetCurrentThread();

    // Initialize symbols and stuff
    if ( _SymInitialize )
    {
      _SymInitialize(hProcess, NULL, FALSE);
      if ( _SymSetOptions )
        _SymSetOptions(SYMOPT_ALLOW_ABSOLUTE_SYMBOLS | SYMOPT_AUTO_PUBLICS |
                SYMOPT_DEFERRED_LOADS | SYMOPT_FAVOR_COMPRESSED |
                SYMOPT_INCLUDE_32BIT_MODULES | SYMOPT_LOAD_ANYTHING |
                SYMOPT_LOAD_LINES);

      // Load all module symbols
      if ( _SymLoadModule )
      {
        MODULEENTRY32 me32;
        me32.dwSize = sizeof(MODULEENTRY32);

        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
        if ( Module32First(hSnapshot, &me32) )
        {
          do
          {
            _SymLoadModule(hProcess, NULL, me32.szExePath, me32.szModule, (DWORD)me32.modBaseAddr, me32.modBaseSize);
          } while( Module32Next(hSnapshot, &me32) );
        }
        CloseHandle(hSnapshot);
      } // if _SymLoadModule is valid
    }

    // Load custom symbols for Broodwar, etc
    std::vector<_customSymbolStore> customSymbols;
    std::string symbolMapPath = installPath + "bwapi-data\\data\\Broodwar.map";
    FILE *hBWSymbols = fopen(symbolMapPath.c_str(), "r");
    if ( hBWSymbols )
    {
      char szSymbolName[512];
      DWORD dwAddress = 0;
      DWORD dwSize = 0;
      for (;;)
      {
        int iResult = fscanf(hBWSymbols, "%511s %8x %8x", szSymbolName, &dwAddress, &dwSize);
        if ( iResult == EOF || iResult == 0 )
          break;
        _customSymbolStore sym = { szSymbolName, dwAddress, dwAddress + dwSize };
        customSymbols.push_back(sym);
      }
      fclose(hBWSymbols);
    }
    /*std::ifstream bwSymbols( installPath + "bwapi-data\\data\\Broodwar.map");
    if ( bwSymbols )
    {
      DWORD dwAddr = 0, dwSize = 0;
      std::string symName("");
      while ( bwSymbols >> symName >> std::hex >> dwAddr >> dwSize )
      {
        _customSymbolStore sym = { symName, dwAddr, dwAddr + dwSize };
        customSymbols.push_back(sym);
      }
      bwSymbols.close();
    }*/
    
    // Walk, don't run
    if ( _StackWalk && _SymFunctionTableAccess && _SymGetModuleBase )
    {
      while ( _StackWalk(IMAGE_FILE_MACHINE_I386, 
                          hProcess, 
                          hThread, 
                          &sf, 
                          &c, 
                          nullptr, 
                          _SymFunctionTableAccess,
                          _SymGetModuleBase,
                          nullptr) )
      {
        DWORD dwOffset = sf.AddrPC.Offset;
        fprintf(hFile, "  %-16s  0x%08X    ", getModuleNameFrom((LPCVOID)dwOffset).c_str(), dwOffset);
        bool foundSomething = false;
        if ( dwOffset )
        {
          // Get the symbol name
          IMAGEHLP_SYMBOL_PACKAGE sip = { 0 };
          sip.sym.SizeOfStruct  = sizeof(IMAGEHLP_SYMBOL);
          sip.sym.MaxNameLength = MAX_SYM_NAME;

          DWORD dwJunk = 0;
          if ( _SymInitialize && _SymGetSymFromAddr && _SymGetSymFromAddr(hProcess, dwOffset, &dwJunk, &sip.sym) )
          {
            fprintf(hFile, "%s", sip.sym.Name);
            foundSomething = true;
          }

          // Get the file name + line
          IMAGEHLP_LINE il = { 0 };
          il.SizeOfStruct = sizeof(IMAGEHLP_LINE);
          dwJunk = 0;
          if ( _SymInitialize && _SymGetLineFromAddr && _SymGetLineFromAddr(hProcess, dwOffset, &dwJunk, &il) )
          {
            fprintf(hFile, "\n                                     %s:%u", il.FileName, il.LineNumber);
            foundSomething = true;
          }

          if ( !foundSomething )
          {
            // Iterate custom symbols, @TODO: make this a map?
            for ( auto i = customSymbols.cbegin(); i != customSymbols.end(); ++i )
            {
              if ( dwOffset >= i->dwStartAddress && dwOffset < i->dwEndAddress )
              {
                fprintf(hFile, "%s", i->name.c_str());
                foundSomething = true;
                break;
              }
            }
          }
        }

        if ( !foundSomething )
          fprintf(hFile, "  ----");

        fprintf(hFile, "\n");
      }
    }
    // Clean up
    if ( _SymInitialize && _SymCleanup )
      _SymCleanup(hProcess);
    fclose(hFile);
  } // ^if hFile

  ShowCursor(FALSE);

  // Call the previous exception filter
  return TopExceptionFilter.DefFilterProc(ep);
}