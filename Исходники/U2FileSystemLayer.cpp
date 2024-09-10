U2EG_NAMESPACE_USING


bool widePathToOgreString(String& dest, const WCHAR* wpath)
{
    // need to convert to narrow (OEM or ANSI) codepage so that fstream can use it 
    // properly on international systems.
    char npath[MAX_PATH];
#if U2_PLATFORM == U2_PLATFORM_WIN32
    // Note, that on legacy CRT versions codepage for narrow CRT file functions can be changed using 
    // SetFileApisANSI/OEM, but on modern runtimes narrow pathes are always widened using ANSI codepage.
    // We suppose that on such runtimes file APIs codepage is left in default, ANSI state.
    UINT codepage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;
#elif U2_PLATFORM == U2_PLATFORM_WINRT
    // Runtime is modern, narrow calls are widened inside CRT using CP_ACP codepage.
    UINT codepage = CP_ACP;
#endif
    if (0 == WideCharToMultiByte(codepage, 0 /* Use default flags */, wpath, -1, npath, sizeof(npath), NULL, NULL))
    {
        dest.clear();
        return false;
    }

    // success
    dest = npath;
    return true;
}