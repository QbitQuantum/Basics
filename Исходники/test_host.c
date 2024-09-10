static void PrintSymbolForAddress(DWORD64 addr) {
  /*
   * Code adapted from Chromium's stack_trace_win.cc, in turn adapted
   * from an MSDN example:
   * http://msdn.microsoft.com/en-us/library/ms680578(VS.85).aspx
   */
  ULONG64 buffer[(sizeof(SYMBOL_INFO) +
                  MAX_SYMBOL_NAME_LENGTH * sizeof(wchar_t) +
                  sizeof(ULONG64) - 1) /
                 sizeof(ULONG64)];
  DWORD64 sym_displacement = 0;
  PSYMBOL_INFO symbol = (PSYMBOL_INFO) buffer;
  BOOL has_symbol;
  memset(buffer, 0, sizeof(buffer));

  SymInitialize(GetCurrentProcess(), NULL, TRUE);

  symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
  symbol->MaxNameLen = MAX_SYMBOL_NAME_LENGTH - 1;
  has_symbol = SymFromAddr(GetCurrentProcess(),
                           addr, &sym_displacement, symbol);
  if (has_symbol) {
    fprintf(stderr, "%s + 0x%x\n", symbol->Name, sym_displacement);
  } else {
    fprintf(stderr, "<no symbol>\n");
  }
}