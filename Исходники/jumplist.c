static HRESULT
register_task(IObjectCollection *pobjs, wstring title, wstring cmd, wstring icon, int ii)
{
  HRESULT hr = S_OK;
  IShellLinkW *pShellLink;

  if (!cmd || !*cmd)
    return S_OK;

  wstring show_title = (!title || !*title) ? cmd : title;

  wchar exe_path[MAX_PATH + 1];
  if (GetModuleFileNameW(NULL, exe_path, MAX_PATH) == 0)
    return S_FALSE;

  //printf("register_task <%ls>: <%ls> <%ls>\n", title, exe_path, cmd);
  hr = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, &IID_IShellLinkW, (void **)&pShellLink);
  if (SUCCEEDED(hr)) {
    do {
      // set title
      IPropertyStore *pPropertyStore;
      hr = pShellLink->lpVtbl->QueryInterface((void *)pShellLink, &IID_IPropertyStore, (void **)&pPropertyStore);
      if (SUCCEEDED(hr)) {
        PROPVARIANT propVariant;

        hr = InitPropVariantFromString(show_title, &propVariant);
        if (SUCCEEDED(hr)) {
          hr = pPropertyStore->lpVtbl->SetValue((void *)pPropertyStore, &PKEY_Title, &propVariant);
          if (SUCCEEDED(hr)) {
            pPropertyStore->lpVtbl->Commit((void *)pPropertyStore);
          }
        }
      }
      if (FAILED(hr))
        break;

      // set icon path and index
      if (icon)
        hr = pShellLink->lpVtbl->SetIconLocation((void *)pShellLink, icon, ii);
      else
        hr = pShellLink->lpVtbl->SetIconLocation((void *)pShellLink, exe_path, 0);
      if (FAILED(hr))
        break;

      // set full path of mintty.exe
      hr = pShellLink->lpVtbl->SetPath((void *)pShellLink, exe_path);
      if (FAILED(hr))
        break;

      // set arguments
      hr = pShellLink->lpVtbl->SetArguments((void *)pShellLink, cmd);
      if (FAILED(hr))
        break;

      // finally, register this column into the jump list
      hr = pobjs->lpVtbl->AddObject((void *)pobjs, (IUnknown *)pShellLink);
    } while (0);

    pShellLink->lpVtbl->Release((void *)pShellLink);
  }

  return hr;
}