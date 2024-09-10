HRESULT typeLibForInterface(REFIID iid, ITypeLib** typeLib )
{
	if ( !typeLib )
		return E_POINTER;

	*typeLib = 0;
	mol::RegKey root(HKEY_CLASSES_ROOT);
	mol::RegKey interfaces = root.open(_T("Interface"),KEY_READ);
	std::wstring siid = stringFromCLSID(iid);
	mol::RegKey iface = interfaces.open(siid,KEY_READ);
	if ( iface )
	{
		mol::RegKey lib = iface.open(_T("TypeLib"),KEY_READ);
		if ( lib )
		{
			std::wstring guid = lib.get();
			std::wstring version = _T("1.0");
			try {
				version = lib.get(_T("Version"));
			}
			catch(...) {}

			size_t pos = version.find(_T("."));
			if ( pos == std::wstring::npos )
				return E_FAIL;
#ifdef _UNICODE
			int major = _wtoi( version.substr(0,pos).c_str() );
			int minor = _wtoi( version.substr(pos+1).c_str() );
#else
			int major = atoi( version.substr(0,pos).c_str() );
			int minor = atoi( version.substr(pos+1).c_str() );
#endif

			CLSID clsid;
			if ( S_OK == CLSIDFromString( (LPOLESTR)(mol::towstring(guid).c_str()),&clsid) )
			{
				TypeLib tl;
				tl.load(clsid,major,minor);
				return tl.queryInterface(typeLib);				
			}
		}
	}
	return S_OK;
}