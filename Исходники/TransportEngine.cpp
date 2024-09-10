VOID CNktDvTransportEngine::CDispatcher::RemoveConnection(__in CNktDvTransportEngine::CConnection *lpConn)
{
  CNktAutoFastMutex cLock(this);
  TNktLnkLst<CNktDvTransportOverlapped>::Iterator it;
  CNktDvTransportOverlapped *lpOvr;

  for (lpOvr=it.Begin(cQueueBufferList); lpOvr!=NULL; lpOvr=it.Next())
  {
    if (lpOvr->sEngineInternals.lpConn == lpConn)
    {
      lpConn->FreeBuffer(lpOvr);
      lpConn->Release();
    }
  }
  return;
}