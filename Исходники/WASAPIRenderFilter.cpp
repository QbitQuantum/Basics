void CWASAPIRenderFilter::CancelDataEvent()
{
  if (!m_pSettings->m_bWASAPIUseEventMode)
  {
    CancelWaitableTimer(m_hDataEvent);
    if (CancelWaitableTimer(m_hDataEvent) == 0)
    {
      DWORD error = GetLastError();
      Log("WASAPIRenderFilter::CancelDataEvent - CancelWaitableTimer failed: %d", error);
    }
  }
}