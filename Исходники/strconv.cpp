std::wstring strconv::a2w(std::string str)
{
    if(!bSetLocale)
    {
        setlocale (LC_ALL,"");
        bSetLocale = true;
    }

	// Calculate output buffer size
    size_t nmax = 0;
#ifdef _WIN32
    mbstowcs_s(&nmax, NULL, 0, str.c_str(), 0);
#else
    nmax = mbstowcs(NULL, str.c_str(), 0);
#endif

	// Check if buffer size calculated
	if(nmax==0 || nmax==(size_t)-1)
		return std::wstring(); // error 

	// Allocate buffer
    wchar_t* buf = new wchar_t[nmax+1];
	if(buf==NULL)
		return std::wstring(); // error 

	// Convert string
    size_t count = 0;
#ifdef _WIN32
    mbstowcs_s(&count, buf, nmax, str.c_str(), nmax+1);
#else
    mbstowcs(buf, str.c_str(), nmax+1);
#endif

	buf[nmax]=0; // ensure buffer is zero terminated

    std::wstring wstr(buf);

	// Free buffer
    delete [] buf;

    return wstr;
}