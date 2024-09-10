//----------------------------------------------------------------------------
//  Cleanup
HRESULT CAnchoRuntime::Cleanup()
{
  AtlUnadvise(m_pWebBrowser, DIID_DWebBrowserEvents2, m_WebBrowserEventsCookie);
  AtlUnadvise(m_pBrowserEventSource, IID_DAnchoBrowserEvents, m_AnchoBrowserEventsCookie);

  gWindowDocumentMap.eraseTab(m_TabID);
  return S_OK;
}