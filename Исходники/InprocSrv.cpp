static std::wstring GetFsBoxCLSID()
{
	LPOLESTR olestr_CLSID_FsBox = 0;
	if (FAILED(StringFromCLSID(CLSID_FsBox, &olestr_CLSID_FsBox)))
	{
		return L"";
	}
	std::wstring result(olestr_CLSID_FsBox, olestr_CLSID_FsBox + wcslen(olestr_CLSID_FsBox));
	CoTaskMemFree(olestr_CLSID_FsBox);
	return result;
}