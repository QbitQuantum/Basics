int finalizeLibrary() {
  VPrintf(1, "in esan::%s\n", __FUNCTION__);
  if (WhichTool == ESAN_CacheFrag) {
    // FIXME NYI: we need to add sampling + callstack gathering and have a
    // strategy for how to generate a final report.
    // We'll move this to cache_frag.cpp once we have something.
    Report("%s is not finished: nothing yet to report\n", SanitizerToolName);
  }
  return 0;
}