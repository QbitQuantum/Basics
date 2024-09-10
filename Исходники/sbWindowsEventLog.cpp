void
sbWindowsEventLogInitialize()
{
  // Do nothing if already initialized.
  if (gSBWindowsEventLogInitialized)
    return;

  // Set up to finalize on exit.
  atexit(sbWindowsEventLogFinalize);

  // Register the event source.
  gSBWindowsEventLogEventSource = RegisterEventSourceA
                                    (NULL,
                                     SB_WINDOWS_EVENT_LOG_EVENT_SOURCE_NAME);

  // Service is initialized.
  gSBWindowsEventLogInitialized = TRUE;
}