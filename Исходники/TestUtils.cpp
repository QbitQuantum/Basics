std::wstring TestUtils::exec(LPCTSTR szCmd) 
{
    FILE* pipe = _tpopen(szCmd, _T("rt"));
    if (!pipe) return L"ERROR";
    wchar_t buffer[4096];
    std::wstring result;
    while(!feof(pipe)) 
	{
    	if(fgetws(buffer, 4096, pipe) != NULL)
    		result += buffer;
    }
	wtrim(result);
    _pclose(pipe);
    return result;
}