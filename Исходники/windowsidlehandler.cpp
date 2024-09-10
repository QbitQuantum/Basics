void WindowsIdleHandler::Inhibit(const char*) {
  switch (IdleHandler::inbtr_) {
    case IdleHandler::Screensaver :
      // resetting the display idle timer.
      previous_state_ =
          SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
      break;
    case IdleHandler::Suspend :
      // resetting the system idle timer.
      previous_state_ =
          SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED);
      break;
  }

  if (previous_state_ != 0) {
    is_inhibit_ = true;
  } else {
    qLog(Warning) << "Failed to inhibit screensaver/suspend";
  }
}