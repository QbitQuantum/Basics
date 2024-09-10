 void write_function_name(std::ostream & os, HANDLE process, DWORD64 program_counter) {
   SYMBOL_INFO_PACKAGE sym = { sizeof(SYMBOL_INFO) };
   sym.si.MaxNameLen = MAX_SYM_NAME;
   if (SymFromAddr(process, program_counter, 0, &sym.si)) {
     os << sym.si.Name << "()";
   } else {
     os << "Unknown function(" << GetLastError() << ")";
   } 
 }