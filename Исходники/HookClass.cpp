//---------------------------------------------------------------------------
//ReplaceIATEntryInAllModules
void WINAPI TAPIHook::ReplaceIATEntryInAllModules(PCSTR DllName,
  PROC pfnCurrent,PROC pfnNew,bool IsHookSelfDll)
{
  // 是否Hook DLL本身的相应函数。对一些系统函数，如GetProcAddress、LoadLibraryA、
  // LoadLibraryW、LoadLibraryEx、LoadLibraryExW这些函数，DLL本身是不能对它们进
  // 行Hook的，否则会引起死循环。

  HMODULE hThisModule = NULL;

  hThisModule = (IsHookSelfDll) ? NULL : ModuleFromAddress(ReplaceIATEntryInAllModules);

  /////
  HANDLE hSnapshot;
  MODULEENTRY32 ModEntry32;
  DWORD dwProcessId;
  BOOL Result;

  dwProcessId = GetCurrentProcessId();
  hSnapshot = CreateToolhelp32Snapshot((DWORD)TH32CS_SNAPMODULE,dwProcessId);

  ModEntry32.dwSize = sizeof(MODULEENTRY32);
  Result = Module32First(hSnapshot,&ModEntry32);
  while(Result)
  {
    if(ModEntry32.hModule != hThisModule)
      ReplaceIATEntryInModule(DllName,pfnCurrent,pfnNew,ModEntry32.hModule);

    Result = Module32Next(hSnapshot,&ModEntry32);
  }

  CloseHandle(hSnapshot);
}