BOOL install_util::CreateLnkPath(std::wstring wsSourceFilePath, std::wstring wsDestLnkPath, std::wstring wsArgument, std::wstring wsAppId)
{
  IShellLink *pisl = NULL;
  HRESULT hr = CoCreateInstance(CLSID_ShellLink,
    NULL,
    CLSCTX_INPROC_SERVER,
    IID_IShellLink,
    (void**)&pisl);
  if (FAILED(hr))
  {
    return FALSE;
  }

  pisl->SetPath(wsSourceFilePath.c_str());
  pisl->SetArguments(wsArgument.c_str());
  int nStart = wsSourceFilePath.find_last_of(_T("/\\")); 
  pisl->SetWorkingDirectory(wsSourceFilePath.substr(0,nStart).c_str());
  IPersistFile *plPF = NULL; 
  hr = pisl->QueryInterface(IID_IPersistFile, (void**)&plPF);
  bool shortcut_existed = false;
  if (SUCCEEDED(hr))
  {
    if (PathExists(wsDestLnkPath))
    {
      shortcut_existed = true;
      install_util::DeleteFile(wsDestLnkPath.c_str());
    }
	if (Win7OrLater() && !wsAppId.empty() && wsAppId.length() < 64)
	{
		IPropertyStore *piPS = NULL;
		if (SUCCEEDED(pisl->QueryInterface(IID_IPropertyStore, (void**)&piPS)))
		{
			PROPVARIANT property_value;
			if (SUCCEEDED(InitPropVariantFromString(wsAppId.c_str(), &property_value)))
			{
				if (piPS->SetValue(PKEY_AppUserModel_ID, property_value) == S_OK)
					piPS->Commit();
				PropVariantClear(&property_value);
			}
			piPS->Release();
		}
	}

    hr = plPF->Save(wsDestLnkPath.c_str(), TRUE);
    plPF->Release();
  }

  pisl->Release();
  SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);

  return SUCCEEDED(hr);
}