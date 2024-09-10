NO_SANITIZE_MEMORY
void Fuzzer::AlarmCallback() {
  assert(Options.UnitTimeoutSec > 0);
  if (InOOMState) {
    Printf("==%d== ERROR: libFuzzer: out-of-memory (used: %zdMb; limit: %zdMb)\n",
           GetPid(), GetPeakRSSMb(), Options.RssLimitMb);
    Printf("   To change the out-of-memory limit use -rss_limit_mb=<N>\n");
    if (CurrentUnitSize && CurrentUnitData) {
      DumpCurrentUnit("oom-");
      if (__sanitizer_print_stack_trace)
        __sanitizer_print_stack_trace();
    }
    Printf("SUMMARY: libFuzzer: out-of-memory\n");
    PrintFinalStats();
    _Exit(Options.ErrorExitCode); // Stop right now.
  }

  if (!CurrentUnitSize)
    return; // We have not started running units yet.
  size_t Seconds =
      duration_cast<seconds>(system_clock::now() - UnitStartTime).count();
  if (Seconds == 0)
    return;
  if (Options.Verbosity >= 2)
    Printf("AlarmCallback %zd\n", Seconds);
  if (Seconds >= (size_t)Options.UnitTimeoutSec) {
    Printf("ALARM: working on the last Unit for %zd seconds\n", Seconds);
    Printf("       and the timeout value is %d (use -timeout=N to change)\n",
           Options.UnitTimeoutSec);
    DumpCurrentUnit("timeout-");
    Printf("==%d== ERROR: libFuzzer: timeout after %d seconds\n", GetPid(),
           Seconds);
    if (__sanitizer_print_stack_trace)
      __sanitizer_print_stack_trace();
    Printf("SUMMARY: libFuzzer: timeout\n");
    PrintFinalStats();
    _Exit(Options.TimeoutExitCode); // Stop right now.
  }
}