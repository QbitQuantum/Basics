std::string
formatStackTrace(StackTrace *trace)
{
   auto process = GetCurrentProcess();
   static bool symInitialise = false;

   if (!symInitialise) {
      SymInitialize(process, NULL, TRUE);
      symInitialise = true;
   }

   auto symbol = new MySymbol();
   symbol->MaxNameLen = 256;
   symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

   fmt::MemoryWriter out;

   for (auto i = 0u; i < trace->frames; ++i) {
      SymFromAddr(process, (DWORD64)trace->data[i], 0, symbol);
      out.write("{}: {} - 0x{:X}x\n", trace->frames - i - 1, (const char*)symbol->Name, symbol->Address);
   }

   delete symbol;
   return out.str();
}