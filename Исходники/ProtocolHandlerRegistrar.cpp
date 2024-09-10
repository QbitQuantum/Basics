HRESULT CProtocolHandlerRegistrar::UnregisterTemporaryHandler(
  LPCWSTR lpszScheme,
  LPCWSTR lpszHost)
{
  CritSectLock lock(m_CriticalSection);
  // lookup classfactory object for lpszHost
  CComPtr<IClassFactory> pClassFactory;
  if (!m_ClassFactories.Lookup(lpszScheme, pClassFactory))
  {
    // not found
    return S_FALSE;
  }

  // unregister host
  CComObject<CF> * pHandlerFactory = (CComObject<CF> *)pClassFactory.p;
  size_t registeredHosts = pHandlerFactory->RemoveHost(lpszHost);
  if (registeredHosts > 0)
  {
    // the handler has still registered hosts
    return S_OK;
  }

  // there are no more registered hosts, so remove the registration

  // get IInternetSession
  CComPtr<IInternetSession> pInternetSession;
  IF_FAILED_RET(CoInternetGetSession(0, &pInternetSession, 0));

  // unregister
  pInternetSession->UnregisterNameSpace(pClassFactory,
      lpszScheme);

  // and remove from map
  m_ClassFactories.RemoveKey(lpszScheme);

  return S_OK;
}