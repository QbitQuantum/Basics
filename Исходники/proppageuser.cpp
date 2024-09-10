// IShellPropSheetExt interface
STDMETHODIMP CProppageUser::AddPages(LPFNADDPROPSHEETPAGE pAddPageProc, LPARAM lParam)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  TRACE(L"CProppageUser::AddPages()\n");

  // Unpack the data pointer and create the property page.
  // Register clipboard format
  CLIPFORMAT cfDsObjectNames = (CLIPFORMAT)RegisterClipboardFormat(CFSTR_DSOBJECTNAMES);
  ASSERT(cfDsObjectNames != 0);

  FORMATETC fmte = { cfDsObjectNames, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
  STGMEDIUM objMedium;

  HRESULT hr = m_spDataObj->GetData(&fmte, &objMedium);
  if (FAILED(hr))
  {
    AfxMessageBox(_T("Failed to retrieve data from medium."));
    return hr;
  }

  LPDSOBJECTNAMES pDsObjectNames;
  pDsObjectNames = (LPDSOBJECTNAMES)objMedium.hGlobal;
  if (pDsObjectNames->cItems < 1)
  {
    return ERROR_INVALID_DATA;
  }

  PWSTR pszObjADsPath = (PWSTR)BYTE_OFFSET(pDsObjectNames, pDsObjectNames->aObjects[0].offsetName);
  PWSTR pszClass = (PWSTR)BYTE_OFFSET(pDsObjectNames, pDsObjectNames->aObjects[0].offsetClass);
  TRACE(_T("Object path: %s, class: %s\n"), pszObjADsPath, pszClass);

  // Create/contact the notification object.
  HWND hNotifyObj;

  hr = ADsPropCreateNotifyObj(m_spDataObj, pszObjADsPath, &hNotifyObj);
  
  if (FAILED(hr))
  {
    return hr;
  }

  CProppageUserUI* pProppageUI = new CProppageUserUI(hNotifyObj);

  pProppageUI->Init(pszObjADsPath, pszClass);

  ((PROPSHEETPAGE*)&pProppageUI->m_psp)->lParam = (LPARAM)pProppageUI;
  if (!(*pAddPageProc)(CreatePropertySheetPage((PROPSHEETPAGE*)&pProppageUI->m_psp), (LPARAM)lParam))
  {
    delete pProppageUI;
    return E_FAIL;
  }
  return S_OK;
}