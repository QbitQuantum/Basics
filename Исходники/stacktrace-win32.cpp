StackTrace::StackTrace(void *their_context) {
  PCONTEXT context = reinterpret_cast<PCONTEXT>(their_context);
  CONTEXT current_context;
  if (their_context == NULL) {
    RtlCaptureContext(&current_context);
    context = &current_context;
  }

  HANDLE process = GetCurrentProcess();
  DbgHelp dbghelp(process);
  if (!dbghelp.is_loaded()) {
    goto fail;
  }

  STACKFRAME64 stack_frame;
  ZeroMemory(&stack_frame, sizeof(stack_frame));

  // http://stackoverflow.com/a/136942/249230
  stack_frame.AddrPC.Offset = context->Eip;
  stack_frame.AddrReturn.Offset = context->Eip;
  stack_frame.AddrPC.Mode = AddrModeFlat;
  stack_frame.AddrFrame.Offset = context->Ebp;
  stack_frame.AddrFrame.Mode = AddrModeFlat;
  stack_frame.AddrStack.Offset = context->Esp;
  stack_frame.AddrStack.Mode = AddrModeFlat;

  if (!dbghelp.HaveStackWalk64()) {
    goto fail;
  }

  SYMBOL_INFO *symbol = NULL;

  if (dbghelp.is_initialized()) {
    symbol = reinterpret_cast<SYMBOL_INFO*>(std::calloc(sizeof(*symbol) + kMaxSymbolNameLength, 1));
    symbol->SizeOfStruct = sizeof(*symbol);
    symbol->MaxNameLen = kMaxSymbolNameLength;

    if (dbghelp.HaveSymGetOptions() && dbghelp.HaveSymSetOptions()) {
      DWORD options = dbghelp.SymGetOptions();
      options |= SYMOPT_FAIL_CRITICAL_ERRORS;
      dbghelp.SymSetOptions(options);
    }
  }

  while (true) {
    DWORD64 address = stack_frame.AddrReturn.Offset;
    if (address <= 0) {
      break;
    }

    bool have_symbols = true;
    if (dbghelp.HaveSymGetModuleInfo64()) {
      IMAGEHLP_MODULE64 module;
      ZeroMemory(&module, sizeof(IMAGEHLP_MODULE64));
      module.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);
      if (dbghelp.SymGetModuleInfo64(process, address, &module)) {
        if (!module.GlobalSymbols) {
          have_symbols = false;
        }
      }
    }

    const char *name = "";
    if (have_symbols) {
      if (dbghelp.is_initialized() && dbghelp.HaveSymFromAddr() && symbol != NULL) {
        if (dbghelp.SymFromAddr(process, address, NULL, symbol)) {
          name = symbol->Name;
        }
      }
    }

    frames_.push_back(StackFrame(reinterpret_cast<void*>(address), name));

    BOOL result = dbghelp.StackWalk64(IMAGE_FILE_MACHINE_I386, process, GetCurrentThread(), &stack_frame,
                                      (PVOID)context, NULL, NULL, NULL, NULL);
    if (!result) {
      break;
    }
  }

  if (symbol != NULL) {
    std::free(symbol);
  }

  return;

fail:
  frames_ = StackTraceGeneric(
    reinterpret_cast<void*>(context->Ebp),
    reinterpret_cast<void*>(context->Eip)).GetFrames();
}