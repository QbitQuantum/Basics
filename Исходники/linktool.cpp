HRESULT
SetShortcutProps(LPCWSTR aShortcutPath, LPCWSTR aAppModelID, bool aSetID, bool aSetMode) 
{
  HRESULT hres; 
  ::CoInitialize(nullptr);

  IPropertyStore *m_pps = nullptr;
  if (FAILED(hres = SHGetPropertyStoreFromParsingName(aShortcutPath,
                                                      nullptr,
                                                      GPS_READWRITE,
                                                      IID_PPV_ARGS(&m_pps)))) {
    printf("SHGetPropertyStoreFromParsingName failed\n");
    goto Exit;
  }

  if (aSetMode) {
    PROPVARIANT propvar;
    if (FAILED(hres = InitPropVariantFromBoolean(true, &propvar)) ||
        FAILED(hres = m_pps->SetValue(PKEY_AppUserModel_IsDualMode, propvar))) {
      goto Exit;
    }
    PropVariantClear(&propvar);
  }

  if (aSetID && aAppModelID) {
    PROPVARIANT propvar;
    if (FAILED(hres = InitPropVariantFromString(aAppModelID, &propvar)) ||
        FAILED(hres = m_pps->SetValue(PKEY_AppUserModel_ID, propvar))) {
      goto Exit;
    }
    PropVariantClear(&propvar);
  }

  hres = m_pps->Commit();

  Exit:

  if (m_pps) {
    m_pps->Release();
  }

  CoUninitialize();
  return hres;
}