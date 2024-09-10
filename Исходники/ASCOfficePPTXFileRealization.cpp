HRESULT CPPTXFile::put_TempDirectory(std::wstring newVal)
{
    std::wstring TempStr(newVal);

#if defined(_WIN32) || defined (_WIN64)
    if(PathIsDirectoryW(TempStr.c_str()))
	{
        if(TempStr.substr(TempStr.length() - 2, 1) != L"\\")
			TempStr += L"\\";
		m_strTempDir = TempStr;
		return S_OK;
	}
#else
    if(NSDirectory::PathIsDirectory(TempStr))
    {
        if(TempStr[TempStr.length() - 1] != L'/')
            TempStr += L"/";
        m_strTempDir = TempStr;
    }
#endif
	return S_FALSE;
}