void CVisualPage::OnCamSetupButton()
{
  CComboBox * box = (CComboBox*)(GetDlgItem(IDC_RECORDING_COMBO));
  int i = box->GetCurSel();
  int n = box->GetLBTextLen(i);
  CString s;
  box->GetLBText(i, s.GetBuffer(n));
  PString setupDeviceName = s;
  s.ReleaseBuffer();

  if (setupDeviceName.IsEmpty()) return;
  if (setupDeviceName.Find("fake") == 0) return;
  if (setupDeviceName.Find("monitor") == 0) return;
  if (setupDeviceName.Find("zmonitor") == 0) return;
  PTRACE(4,"PVidDirectShow\tCurrent device: " << setupDeviceName);

  HRESULT hr;
  IBaseFilter * pFilter = NULL;
  IMoniker *pMoniker =NULL;
  ICreateDevEnum *pDevEnum =NULL;
  IEnumMoniker *pClassEnum = NULL;
  ULONG cFetched;

  ::CoInitialize(NULL);

  // Create the system device enumerator
  hr = CoCreateInstance (CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC, IID_ICreateDevEnum, (void **) &pDevEnum);
  if (FAILED(hr)) { ::CoUninitialize(); return; }

  // Create an enumerator for the video capture devices
  hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pClassEnum, 0);
  if (FAILED(hr)) { ::CoUninitialize(); return; }

  if (pClassEnum == NULL) { ::CoUninitialize(); return; }

  PTRACE(4,"PVidDirectShow\tEntering device enumeration loop...");
  while (1)
  { // Get the next device
    hr = pClassEnum->Next(1, &pMoniker, &cFetched);
    if (hr != S_OK) { PTRACE(4, "PVidDirectShow\tGetInputDeviceNames() No more video capture device"); break; }

    // Get the property bag
    IPropertyBag *pPropBag;

    hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void**)(&pPropBag));
    if (FAILED(hr))
    { PTRACE(4,"PVidDerectShow\tBindToStorage failed, continue");
      pMoniker->Release();
      continue;
    }

    // Find the description or friendly name.
    VARIANT DeviceName;
    DeviceName.vt = VT_BSTR;
    hr = pPropBag->Read(L"Description", &DeviceName, NULL);
    if (FAILED(hr)) hr = pPropBag->Read(L"FriendlyName", &DeviceName, NULL);
    if (SUCCEEDED(hr))
    { char *pDeviceName = BSTR_to_ANSI(DeviceName.bstrVal);
      if (pDeviceName)
      { PTRACE(4, "PVidDirectShow\tGetInputDeviceNames() Found this capture device '"<< pDeviceName <<"'");
        if(PString(pDeviceName) == setupDeviceName)
        {
          PTRACE(4, "PVidDirectShow\tCamera Setup: device found");
          pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**) &pFilter);
          ISpecifyPropertyPages *p_spec; CAUUID cauuid;
          HRESULT hr = pFilter->QueryInterface( IID_ISpecifyPropertyPages, (void **)&p_spec );
          if( !FAILED(hr) )
          if( SUCCEEDED(p_spec->GetPages( &cauuid )) )
          { if( cauuid.cElems > 0 )
            { HWND hwnd_desktop = ::GetDesktopWindow();
              OleCreatePropertyFrame( hwnd_desktop, 30, 30, NULL, 1, (LPUNKNOWN *)(&pFilter), cauuid.cElems, cauuid.pElems, 0, 0, NULL );
              CoTaskMemFree( cauuid.pElems );
            }
            p_spec->Release();
          }
        }
        free(pDeviceName);
      }
    }
    pPropBag->Release();
    pMoniker->Release();
  }

  ::CoUninitialize();
}