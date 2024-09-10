SessionChangesWatcher::SessionChangesWatcher(AnEventListener *extSessionChangesListener,
                                             LogWriter *log)
: m_extSessionChangesListener(extSessionChangesListener),
  m_log(log)
{
  ProcessIdToSessionId(GetCurrentProcessId(), &m_baseSessionId);
  resume();
}