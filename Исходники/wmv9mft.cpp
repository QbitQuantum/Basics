// ILAVDecoder
STDMETHODIMP CDecWMV9MFT::Init()
{
  DbgLog((LOG_TRACE, 10, L"CDecWMV9MFT::Init(): Trying to open WMV9 MFT decoder"));
  HRESULT hr = S_OK;

  MF.mfplat = LoadLibrary(L"mfplat.dll");
  if (!MF.mfplat) {
    DbgLog((LOG_TRACE, 10, L"-> Failed to load mfplat.dll"));
    return E_FAIL;
  }

  GET_PROC_MF(Startup);
  GET_PROC_MF(Shutdown);
  GET_PROC_MF(CreateMediaType);
  GET_PROC_MF(CreateSample);
  GET_PROC_MF(CreateAlignedMemoryBuffer);
  GET_PROC_MF(AverageTimePerFrameToFrameRate);

  MF.Startup(MF_VERSION, MFSTARTUP_LITE);

  hr = CoCreateInstance(CLSID_CWMVDecMediaObject, nullptr, CLSCTX_INPROC_SERVER, IID_IMFTransform, (void **)&m_pMFT);
  if (FAILED(hr)) {
    DbgLog((LOG_TRACE, 10, L"-> Failed to create MFT object"));
    return hr;
  }

  // Force decoder deinterlacing, dxva and FI to off
  IPropertyStore *pProp = nullptr;
  hr = m_pMFT->QueryInterface(&pProp);
  if (SUCCEEDED(hr)) {
    PROPVARIANT variant;
    InitPropVariantFromBoolean(FALSE, &variant);
    pProp->SetValue(MFPKEY_DECODER_DEINTERLACING, variant);
    pProp->SetValue(MFPKEY_DXVA_ENABLED, variant);
    pProp->SetValue(MFPKEY_FI_ENABLED, variant);
    SafeRelease(&pProp);
  }

  return S_OK;
}