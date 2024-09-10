void PreviewGenerator::GetClsidsFromExt(CString ext, std::vector<CLSID> &retVal)
{
	std::vector<CLSID> res;
	DWORD size = 1024;
	TCHAR buff[1024];
	LPCWSTR extra = L"{8895B1C6-B41F-4C1C-A562-0D564250836F}";
	CString cs = L"";
	cs.Format(L".%s", ext);
	HRESULT hr = AssocQueryString(ASSOCF_VERIFY, ASSOCSTR_SHELLEXTENSION, cs, extra, buff, &size);
	if (hr == S_OK)
	{
		CLSID cls;
		CLSIDFromString(buff, &cls);
		res.push_back(cls);
	}
	extra = L"{BB2E617C-0920-11d1-9A0B-00C04FC2D6C1}";
	hr = AssocQueryString(ASSOCF_VERIFY, ASSOCSTR_SHELLEXTENSION, cs, extra, buff, &size);
	if (hr == S_OK)
	{
		CLSID cls;
		CLSIDFromString(buff, &cls);
		std::vector<CLSID>::iterator it = find(res.begin(), res.end(), cls);
		if (it == res.end())
			res.push_back(cls);
	}
	extra = L"{e357fccd-a995-4576-b01f-234630154e96}";
	hr = AssocQueryString(ASSOCF_VERIFY, ASSOCSTR_SHELLEXTENSION, cs, extra, buff, &size);
	if (hr == S_OK)
	{
		CLSID cls;
		CLSIDFromString(buff, &cls);
		std::vector<CLSID>::iterator it = find(res.begin(), res.end(), cls);
		if (it == res.end())
			res.push_back(cls);
	}
	//extra = L"{534A1E02-D58F-44f0-B58B-36CBED287C7C}";
	//CLSID cls;
	//CLSIDFromString(extra, &cls);
	//res.push_back(cls);
	//hr = AssocQueryString(ASSOCF_VERIFY, ASSOCSTR_SHELLEXTENSION, cs, extra, buff, &size);
	//if (hr == S_OK)
	//{
	//	std::vector<CString>::iterator it = find(res.begin(), res.end(), buff);
	//	if (it == res.end())
	//		res.push_back(buff);
	//}
	
	PERCEIVED     ptype;
	PERCEIVEDFLAG pflag;
	PWSTR         ppszType;
	cs = L"";
	WCHAR wcData[MAX_PATH];
	LONG cData = sizeof(wcData);
	cs.Format(L".%s", ext);
	hr = RegQueryValue(HKEY_CLASSES_ROOT, cs, wcData, &cData);
	if (hr == S_OK)
	{
		cs.Format(L"%s\\shellex\\{8895b1c6-b41f-4c1c-a562-0d564250836f}", wcData);
		cData = sizeof(wcData);
		hr = RegQueryValue(HKEY_CLASSES_ROOT, cs, wcData, &cData);
		if (hr == S_OK)
		{
			CLSID cls;
			CLSIDFromString(wcData, &cls);
			res.push_back(cls);
		}
	}

	cs.Format(L".%s", ext);
	hr = AssocGetPerceivedType(cs, &ptype, &pflag, &ppszType);
	if (hr == S_OK)
	{
		cs.Format(L"SystemFileAssociations\\%s\\ShellEx\\{e357fccd-a995-4576-b01f-234630154e96}", ppszType);
		hr = RegQueryValue(HKEY_CLASSES_ROOT, cs, wcData, &cData);
		if (hr == S_OK)
		{
			CLSID cls;
			CLSIDFromString(buff, &cls);
			std::vector<CLSID>::iterator it = find(res.begin(), res.end(), cls);
			if (it == res.end())
				res.push_back(cls);
		}

		cs.Format(L"SystemFileAssociations\\%s\\ShellEx\\{BB2E617C-0920-11d1-9A0B-00C04FC2D6C1}", ppszType);
		hr = RegQueryValue(HKEY_CLASSES_ROOT, cs, wcData, &cData);
		if (hr == S_OK)
		{
			CLSID cls;
			CLSIDFromString(buff, &cls);
			std::vector<CLSID>::iterator it = find(res.begin(), res.end(), cls);
			if (it == res.end())
				res.push_back(cls);
		}
		cs.Format(L"SystemFileAssociations\\%s\\ShellEx\\ContextMenuHandlers\\ShellVideoSlideshow", ppszType);
		hr = RegQueryValue(HKEY_CLASSES_ROOT, cs, wcData, &cData);
		if (hr == S_OK)
		{
			CLSID cls;
			CLSIDFromString(buff, &cls);
			std::vector<CLSID>::iterator it = find(res.begin(), res.end(), cls);
			if (it == res.end())
				res.push_back(cls);
		}
	}

	retVal.swap(res);
}