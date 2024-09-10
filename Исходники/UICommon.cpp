void EnableScreenSaver(bool enable)
#endif
{
// Inhibit the screensaver. Depending on the operating system this may also
// disable low-power states and/or screen dimming.

#if defined(HAVE_X11) && HAVE_X11
  if (Config::Get(Config::MAIN_DISABLE_SCREENSAVER))
  {
    X11Utils::InhibitScreensaver(win, !enable);
  }
#endif

#ifdef _WIN32
  // Prevents Windows from sleeping, turning off the display, or idling
  if (enable)
  {
    SetThreadExecutionState(ES_CONTINUOUS);
  }
  else
  {
    EXECUTION_STATE should_screen_save =
        Config::Get(Config::MAIN_DISABLE_SCREENSAVER) ? ES_DISPLAY_REQUIRED : 0;
    SetThreadExecutionState(ES_CONTINUOUS | should_screen_save | ES_SYSTEM_REQUIRED);
  }
#endif

#ifdef __APPLE__
  static IOPMAssertionID s_power_assertion = kIOPMNullAssertionID;

  if (Config::Get(Config::MAIN_DISABLE_SCREENSAVER))
  {
    if (enable)
    {
      if (s_power_assertion != kIOPMNullAssertionID)
      {
        IOPMAssertionRelease(s_power_assertion);
        s_power_assertion = kIOPMNullAssertionID;
      }
    }
    else
    {
      CFStringRef reason_for_activity = CFSTR("Emulation Running");
      if (IOPMAssertionCreateWithName(kIOPMAssertionTypePreventUserIdleDisplaySleep,
                                      kIOPMAssertionLevelOn, reason_for_activity,
                                      &s_power_assertion) != kIOReturnSuccess)
      {
        s_power_assertion = kIOPMNullAssertionID;
      }
    }
  }
#endif
}