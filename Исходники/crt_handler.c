int
__mingw_init_ehandler (void)
{
  static int was_here = 0;
  size_t e = 0;
  PIMAGE_SECTION_HEADER pSec;
  PBYTE _ImageBase = _GetPEImageBase ();
  
  if (was_here || !_ImageBase)
    return was_here;
  was_here = 1;
  if (_FindPESectionByName (".pdata") != NULL)
    return 1;

  /* Allocate # of e tables and entries.  */
  memset (emu_pdata, 0, sizeof (RUNTIME_FUNCTION) * MAX_PDATA_ENTRIES);
  memset (emu_xdata, 0, sizeof (UNWIND_INFO) * MAX_PDATA_ENTRIES);
    
  e = 0;
  /* Fill tables and entries.  */
  while (e < MAX_PDATA_ENTRIES && (pSec = _FindPESectionExec (e)) != NULL)
    {
      emu_xdata[e].VersionAndFlags = 9; /* UNW_FLAG_EHANDLER | UNW_VERSION */
      emu_xdata[e].AddressOfExceptionHandler =
	(DWORD)(size_t) ((LPBYTE)__mingw_SEH_error_handler - _ImageBase);
      emu_pdata[e].BeginAddress = pSec->VirtualAddress;
      emu_pdata[e].EndAddress = pSec->VirtualAddress + pSec->Misc.VirtualSize;
      emu_pdata[e].UnwindData =
	(DWORD)(size_t)((LPBYTE)&emu_xdata[e] - _ImageBase);
      ++e;
    }
#ifdef _DEBUG_CRT
  if (!e || e > MAX_PDATA_ENTRIES)
    abort ();
#endif
  /* RtlAddFunctionTable.  */
  if (e != 0)
    RtlAddFunctionTable (emu_pdata, e, (DWORD64)_ImageBase);
  return 1;
}