//------------------------------------------------------------------*
HRESULT CControlMgt::MessageThread()
{
    while (!m_bShutdownRequest) {
      BSTR lpNextMessage = NULL;
      CSingleLock lock(&m_csMessageQueue, TRUE);
      if (!m_qMessageQueue.IsEmpty())
          lpNextMessage = m_qMessageQueue.RemoveHead();
      lock.Unlock();
      if (lpNextMessage == NULL) {
          WaitForSingleObject(m_hWakeup, INFINITE);
      }
      else {
        HRESULT hr = Fire_OnNewMessage(lpNextMessage);
        SysFreeString(lpNextMessage);
        if (FAILED(hr)) {
            CoDisconnectObject(GetUnknown(), 0);
            return S_OK;//this usually deletes all references, so I can't touch this here any more...
        }
      }
    }

    CSingleLock lock(&m_csMessageQueue, TRUE);
    while (!m_qMessageQueue.IsEmpty()) {
        BSTR pDummy = m_qMessageQueue.RemoveHead();
        SysFreeString(pDummy);
    }
    return S_OK;
}