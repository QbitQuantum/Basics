HRESULT CBaseDSPropPage::ShowPropPageDialog(IBaseFilter *pFilter, HWND hwndOwner)
{
  CheckPointer(pFilter, E_INVALIDARG);
  CoInitialize(nullptr);

  // Get PropertyPages interface
  ISpecifyPropertyPages *pProp = nullptr;
  HRESULT hr = pFilter->QueryInterface<ISpecifyPropertyPages>(&pProp);
  if (SUCCEEDED(hr) && pProp) {
    // Get the filter's name and IUnknown pointer.
    FILTER_INFO FilterInfo;
    hr = pFilter->QueryFilterInfo(&FilterInfo);
    // We don't need the graph, so don't sit on a ref to it
    if (FilterInfo.pGraph)
      FilterInfo.pGraph->Release();

    IUnknown *pFilterUnk = nullptr;
    pFilter->QueryInterface<IUnknown>(&pFilterUnk);

    // Show the page.
    CAUUID caGUID;
    pProp->GetPages(&caGUID);
    pProp->Release();
    hr = OleCreatePropertyFrame(
        hwndOwner,              // Parent window
        0, 0,                   // Reserved
        FilterInfo.achName,     // Caption for the dialog box
        1,                      // Number of objects (just the filter)
        &pFilterUnk,            // Array of object pointers.
        caGUID.cElems,          // Number of property pages
        caGUID.pElems,          // Array of property page CLSIDs
        0,                      // Locale identifier
        0, nullptr              // Reserved
    );

    // Clean up.
    pFilterUnk->Release();
    CoTaskMemFree(caGUID.pElems);

    hr = S_OK;
  }
  CoUninitialize();
  return hr;
}