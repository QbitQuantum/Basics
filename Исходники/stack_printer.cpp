  void windows_print_stacktrace(CONTEXT* context)
  {
    SymInitialize(GetCurrentProcess(), 0, true);

    STACKFRAME frame = { 0 };

    /* setup initial stack frame */
#ifdef AMD64
    frame.AddrPC.Offset         = context->Rip;
    frame.AddrStack.Offset      = context->Rsp;
    frame.AddrFrame.Offset      = context->Rsp;
#else
    frame.AddrPC.Offset         = context->Eip;
    frame.AddrStack.Offset      = context->Esp;
    frame.AddrFrame.Offset      = context->Ebp;
#endif
    frame.AddrPC.Mode           = AddrModeFlat;
    frame.AddrStack.Mode        = AddrModeFlat;
    frame.AddrFrame.Mode        = AddrModeFlat;

#ifdef AMD64
    while (StackWalk64(IMAGE_FILE_MACHINE_AMD64,
#else
    while (StackWalk(IMAGE_FILE_MACHINE_I386,
#endif
                     GetCurrentProcess(),
                     GetCurrentThread(),
                     &frame,
                     context,
                     0,
                     SymFunctionTableAccess,
                     SymGetModuleBase,
                     0 ) )
    {
      addr2line(icky_global_program_name, (void*)frame.AddrPC.Offset);
    }

    SymCleanup( GetCurrentProcess() );
  }