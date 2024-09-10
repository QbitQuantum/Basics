sbTestHarnessConsoleListener::sbTestHarnessConsoleListener()
{
  // XXX Mook temp hack
  #if XP_WIN
    _set_purecall_handler(sb_purecall_handler);
  #endif
  MOZ_COUNT_CTOR(sbTestHarnessConsoleListener);
}