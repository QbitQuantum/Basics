void PerformanceMonitor::BlockShutdown() {
  if (block_)
    return;

  block_ = true;

  if (!SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED |
                               ES_AWAYMODE_REQUIRED) &&
      !SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED))
    ATLTRACE2(L"Failed to set thread execution state.\n");

  CString text;
  text.LoadString(IDS_NETWORK_ACTIVE);
  ShutdownBlockReasonCreate(message_window_, text);
}