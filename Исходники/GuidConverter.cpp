void GUID2String(GUID *guid, LPOLESTR *str)
{
	if (guid && str)
	{
		CLSID clsid = *guid;
		StringFromCLSID(clsid, str);
	}
}