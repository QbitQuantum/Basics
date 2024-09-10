void
Startup()
{
  // The hang detector only runs in chrome processes. If you change this,
  // you must also deal with the threadsafety of AnnotateCrashReport in
  // non-chrome processes!
  if (GoannaProcessType_Default != XRE_GetProcessType()) {
    return;
  }

  MOZ_ASSERT(!gMonitor, "Hang monitor already initialized");
  gMonitor = new Monitor("HangMonitor");

  Preferences::RegisterCallback(PrefChanged, kHangMonitorPrefName, nullptr);
  PrefChanged(nullptr, nullptr);

#ifdef REPORT_CHROME_HANGS
  Preferences::RegisterCallback(PrefChanged, kTelemetryPrefName, nullptr);
  winMainThreadHandle =
    OpenThread(THREAD_ALL_ACCESS, FALSE, GetCurrentThreadId());
  if (!winMainThreadHandle) {
    return;
  }
  gAnnotators = new std::set<Annotator*>();
#endif

  // Don't actually start measuring hangs until we hit the main event loop.
  // This potentially misses a small class of really early startup hangs,
  // but avoids dealing with some xpcshell tests and other situations which
  // start XPCOM but don't ever start the event loop.
  Suspend();

  gThread = PR_CreateThread(PR_USER_THREAD,
                            ThreadMain,
                            nullptr, PR_PRIORITY_LOW, PR_GLOBAL_THREAD,
                            PR_JOINABLE_THREAD, 0);
}