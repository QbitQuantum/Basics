IFileIsInUse* CreateIFileIsInUse(const string& File)
{
	IFileIsInUse *pfiu = nullptr;
	IRunningObjectTable *prot;
	if (SUCCEEDED(GetRunningObjectTable(0, &prot)))
	{
		IMoniker *pmkFile;
		if (SUCCEEDED(CreateFileMoniker(File.data(), &pmkFile)))
		{
			IEnumMoniker *penumMk;
			if (SUCCEEDED(prot->EnumRunning(&penumMk)))
			{
				HRESULT hr = E_FAIL;
				ULONG celt;
				IMoniker *pmk;
				while (FAILED(hr) && (penumMk->Next(1, &pmk, &celt) == S_OK))
				{
					DWORD dwType;
					if (SUCCEEDED(pmk->IsSystemMoniker(&dwType)) && dwType == MKSYS_FILEMONIKER)
					{
						IMoniker *pmkPrefix;
						if (SUCCEEDED(pmkFile->CommonPrefixWith(pmk, &pmkPrefix)))
						{
							if (pmkFile->IsEqual(pmkPrefix) == S_OK)
							{
								IUnknown *punk;
								if (prot->GetObject(pmk, &punk) == S_OK)
								{
									hr = punk->QueryInterface(
#ifdef __GNUC__
										IID_IFileIsInUse, IID_PPV_ARGS_Helper(&pfiu)
#else
										IID_PPV_ARGS(&pfiu)
#endif
										);
									punk->Release();
								}
							}
							pmkPrefix->Release();
						}
					}
					pmk->Release();
				}
				penumMk->Release();
			}
			pmkFile->Release();
		}
		prot->Release();
	}
	return pfiu;
}