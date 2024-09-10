void TracePC::PrintModuleInfo() {
  if (NumGuards) {
    Printf("INFO: Loaded %zd modules   (%zd guards): ", NumModules, NumGuards);
    for (size_t i = 0; i < NumModules; i++)
      Printf("%zd [%p, %p), ", Modules[i].Stop - Modules[i].Start,
             Modules[i].Start, Modules[i].Stop);
    Printf("\n");
  }
  if (NumModulesWithInline8bitCounters) {
    Printf("INFO: Loaded %zd modules   (%zd inline 8-bit counters): ",
           NumModulesWithInline8bitCounters, NumInline8bitCounters);
    for (size_t i = 0; i < NumModulesWithInline8bitCounters; i++)
      Printf("%zd [%p, %p), ", ModuleCounters[i].Stop - ModuleCounters[i].Start,
             ModuleCounters[i].Start, ModuleCounters[i].Stop);
    Printf("\n");
  }
  if (NumPCTables) {
    Printf("INFO: Loaded %zd PC tables (%zd PCs): ", NumPCTables,
           NumPCsInPCTables);
    for (size_t i = 0; i < NumPCTables; i++) {
      Printf("%zd [%p,%p), ", ModulePCTable[i].Stop - ModulePCTable[i].Start,
             ModulePCTable[i].Start, ModulePCTable[i].Stop);
    }
    Printf("\n");

    if ((NumGuards && NumGuards != NumPCsInPCTables) ||
        (NumInline8bitCounters && NumInline8bitCounters != NumPCsInPCTables)) {
      Printf("ERROR: The size of coverage PC tables does not match the"
             " number of instrumented PCs. This might be a bug in the compiler,"
             " please contact the libFuzzer developers.\n");
      _Exit(1);
    }
  }
  if (size_t NumClangCounters = ClangCountersEnd() - ClangCountersBegin())
    Printf("INFO: %zd Clang Coverage Counters\n", NumClangCounters);
}