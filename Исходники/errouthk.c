BOOL HookAPIAllMod( PHookFn Hooks, BOOL restore )
{
  HANDLE	hModuleSnap;
  MODULEENTRY32 me;
  BOOL		fOk;

  // Take a snapshot of all modules in the current process.
  hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE,
					  GetCurrentProcessId() );

  if (hModuleSnap == INVALID_HANDLE_VALUE)
    return FALSE;

  // Fill the size of the structure before using it.
  me.dwSize = sizeof(MODULEENTRY32);

  // Walk the module list of the modules.
  for (fOk = Module32First( hModuleSnap, &me ); fOk;
       fOk = Module32Next( hModuleSnap, &me ))
  {
    // We don't hook functions in our own module.
    if (me.hModule != hDllInstance && me.hModule != hKernel)
    {
      // Hook this function in this module.
      if (!HookAPIOneMod( me.hModule, Hooks, restore ))
      {
	CloseHandle( hModuleSnap );
	return FALSE;
      }
    }
  }
  CloseHandle( hModuleSnap );
  return TRUE;
}