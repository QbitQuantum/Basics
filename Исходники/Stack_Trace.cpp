static int
cs_operate(int (*func)(struct frame_state const *, void *), void *usrarg,
           size_t starting_frame, size_t num_frames)
{
  dbghelp_functions dbg;
  if (!load_dbghelp_library_if_needed (&dbg))
    {
      ACE_OS::strcpy (static_cast<char *> (usrarg),
                      "<error loading dbghelp.dll>");
      if (dbg.hMod) FreeLibrary (dbg.hMod);
      return 1;
    }

  frame_state fs;
  ZeroMemory (&fs.sf, sizeof (fs.sf));
  fs.pDbg = &dbg;
  emptyStack ();   //Not sure what this should do, Chad?

  CONTEXT c;
  ZeroMemory (&c, sizeof (CONTEXT));
  c.ContextFlags = CONTEXT_FULL;

#  if defined (_M_IX86)
  DWORD machine = IMAGE_FILE_MACHINE_I386;
  __asm {
    call x
    x: pop eax
    mov c.Eip, eax
    mov c.Ebp, ebp
    mov c.Esp, esp
  }
  fs.sf.AddrPC.Offset = c.Eip;
  fs.sf.AddrStack.Offset = c.Esp;
  fs.sf.AddrFrame.Offset = c.Ebp;
  fs.sf.AddrPC.Mode = AddrModeFlat;
  fs.sf.AddrStack.Mode = AddrModeFlat;
  fs.sf.AddrFrame.Mode = AddrModeFlat;
#  elif defined (_M_X64)
  DWORD machine = IMAGE_FILE_MACHINE_AMD64;
  RtlCaptureContext (&c);
  fs.sf.AddrPC.Offset = c.Rip;
  fs.sf.AddrFrame.Offset = c.Rsp; //should be Rbp or Rdi instead?
  fs.sf.AddrStack.Offset = c.Rsp;
  fs.sf.AddrPC.Mode = AddrModeFlat;
  fs.sf.AddrFrame.Mode = AddrModeFlat;
  fs.sf.AddrStack.Mode = AddrModeFlat;
#  elif defined (_M_IA64)
  DWORD machine = IMAGE_FILE_MACHINE_IA64;
  RtlCaptureContext (&c);
  fs.sf.AddrPC.Offset = c.StIIP;
  fs.sf.AddrFrame.Offset = c.RsBSP;
  fs.sf.AddrBStore.Offset = c.RsBSP;
  fs.sf.AddrStack.Offset = c.IntSp;
  fs.sf.AddrPC.Mode = AddrModeFlat;
  fs.sf.AddrFrame.Mode = AddrModeFlat;
  fs.sf.AddrBStore.Mode = AddrModeFlat;
  fs.sf.AddrStack.Mode = AddrModeFlat;
#  endif

  fs.pSym = (PSYMBOL_INFO) GlobalAlloc (GMEM_FIXED,
                                        sizeof (SYMBOL_INFO) +
                                        sizeof (ACE_TCHAR) * (SYMSIZE - 1));
  fs.pSym->SizeOfStruct = sizeof (SYMBOL_INFO);
  fs.pSym->MaxNameLen = SYMSIZE * sizeof (ACE_TCHAR);
  dbg.SymSetOptions (SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES
                     | SYMOPT_FAIL_CRITICAL_ERRORS | dbg.SymGetOptions ());
  dbg.SymInitialize (GetCurrentProcess (), 0, true);
  //What does the "true" parameter mean when tracing the current process?

  for (size_t current_frame = 0; current_frame < num_frames + starting_frame;
       ++current_frame)
    {
      BOOL ok = dbg.StackWalk64 (machine,
                                 GetCurrentProcess (),
                                 GetCurrentThread (),
                                 &fs.sf, &c, 0,
                                 dbg.SymFunctionTableAccess64,
                                 dbg.SymGetModuleBase64, 0);
      if (!ok || fs.sf.AddrFrame.Offset == 0)
        break;

      if (current_frame < starting_frame)
        continue;

      func (&fs, usrarg);
    }

  dbg.SymCleanup (GetCurrentProcess ());
  GlobalFree (fs.pSym);
  FreeLibrary (dbg.hMod);

  return 0;
}