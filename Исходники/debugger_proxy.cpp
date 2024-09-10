// Waits until this thread is the one that the proxy considers the current
// thread. This also check to see if the given cmd has any breakpoints or
// flow control that we should stop for. Note: while stepping, pretty much all
// of the stepping logic is handled below here and this will return false if
// the stepping operation has not completed.
bool DebuggerProxy::blockUntilOwn(CmdInterrupt &cmd, bool check) {
  TRACE(2, "DebuggerProxy::blockUntilOwn\n");
  int64_t self = cmd.getThreadId();

  Lock lock(this);
  if (m_thread && m_thread != self) {
    if (check && (m_threadMode == Exclusive || !checkBreakPoints(cmd))) {
      // Flow control commands only belong to sticky thread
      return false;
    }
    m_threads[self] = createThreadInfo(cmd.desc());
    while (!m_stopped && m_thread && m_thread != self) {
      wait(1);

      // if for whatever reason, m_thread isn't debugging anymore (for example,
      // it runs in Sticky mode, but it finishes running), kick it out.
      if (!Debugger::IsThreadDebugging(m_thread)) {
        m_threadMode = Normal;
        m_thread = self;
        m_newThread.reset();
        m_flow.reset();
      }
    }
    m_threads.erase(self);
    if (m_stopped) return false;
    if (!checkBreakPoints(cmd)) {
      // The breakpoint might have been removed while I'm waiting
      return false;
    }
  } else if (check && !checkFlowBreak(cmd)) {
    return false;
  }

  if (m_thread == 0) {
    m_thread = self;
  }
  return true;
}