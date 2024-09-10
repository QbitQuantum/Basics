void XBPython::PulseGlobalEvent()
{
  SetEvent(m_globalEvent);
}