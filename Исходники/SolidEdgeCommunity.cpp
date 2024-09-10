	void CAddInRegistrar::Unregister(CLSID clsid)
	{
		LPOLESTR lpClsidString;
		StringFromCLSID(clsid, &lpClsidString);

		CString strKeyCLSID = lpClsidString;

		CRegKey key;
		key.Open(HKEY_CLASSES_ROOT, L"CLSID");
		key.RecurseDeleteKey(strKeyCLSID);
		key.Close();

		CoTaskMemFree(lpClsidString);
	}