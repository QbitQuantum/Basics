void MouseShapeDetector::execute()
{
  Log::info(_T("mouse shape detector thread id = %d"), getThreadId());

  while (!isTerminating()) {
    bool isCursorShapeChanged;
    {
      AutoLock al(m_mouseGrabLocMut);
      isCursorShapeChanged = m_mouseGrabber->isCursorShapeChanged();
    }
    if (isCursorShapeChanged) {
      m_updateKeeper->setCursorShapeChanged();
      doUpdate();
    }
    Sleep(SLEEP_TIME);
  }
}