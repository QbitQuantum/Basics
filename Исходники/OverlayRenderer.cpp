void COverlayRenderer::CancelTimers()
{
  if (m_hOverlayTimerIG != NULL && CancelWaitableTimer(m_hOverlayTimerIG) == 0)
  {
    DWORD error = GetLastError();
    LogDebug("COverlayRenderer::CancelTimers - CancelWaitableTimer failed: %d", error);
  }

  if (m_hOverlayTimerPG != NULL  && CancelWaitableTimer(m_hOverlayTimerPG) == 0)
  {
    DWORD error = GetLastError();
    LogDebug("COverlayRenderer::CancelTimers - CancelWaitableTimer failed: %d", error);
  }
}