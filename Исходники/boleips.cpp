HRESULT _IFUNC BOleInProcHandler::Init(PIBDataProvider pDP,
  PIBPart pP, LPCOLESTR szProgId, BOOL fHatchWnd)
{
  HRESULT hr;
  // Initialize back pointers
  //
  pProvider = pDP;
  pPart = pP;

  CLSID cid;
  if (SUCCEEDED(hr = CLSIDFromProgID(szProgId, &cid))) {

    // create the default handler, which will launch the exe server
    //
    OleCreateEmbeddingHelper(cid, AsPIUnknown(pObjOuter),
      EMBDHLP_INPROC_HANDLER | EMBDHLP_DELAYCREATE, NULL, IID_IUnknown,
      &(LPVOID)pDefHandler);

    // initialize default IPS
    //
    hr = pDefHandler->QueryInterface(IID_IBSite, &(LPVOID)pDefSite);
    if (SUCCEEDED(hr)) {
      pDefSite->Release();     // prevent aggregation deadlock
      hr = pDefSite->Init(pDP, pP, szProgId, fHatchWnd);
    }
  }
  return hr;
}