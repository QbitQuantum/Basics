UIWin::UIWin()
    : menu(0)
    , contextMenu(0)
    , iconPath("")
{
    // Initialize common controls so that our Win32 native
    // components look swanky.
    INITCOMMONCONTROLSEX InitCtrlEx;
    InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
    InitCtrlEx.dwICC = 0x00004000; //ICC_STANDARD_CLASSES;
    InitCommonControlsEx(&InitCtrlEx);
    
    // Set the cert path for Curl so that HTTPS works properly.
    // We are using _puetenv here since WebKit uses getenv internally 
    // which is incompatible with the Win32 envvar API.
    std::wstring pemPath = ::UTF8ToWide(FileUtils::Join(
        Host::GetInstance()->GetApplication()->runtime->path.c_str(),
        "rootcert.pem", 0));
    std::wstring var = L"CURL_CA_BUNDLE_PATH=" + pemPath;
    _wputenv(var.c_str());

    // Hook app:// and ti:// URL support to WebKit
    setNormalizeURLCallback(NormalizeURLCallback);
    setURLToFileURLCallback(URLToFileURLCallback);
    //setCanPreprocessCallback(CanPreprocessURLCallback);
    //setPreprocessCallback(PreprocessURLCallback);
    setProxyCallback(ProxyForURLCallback);

    std::string cookieJarFilename(FileUtils::Join(
        Host::GetInstance()->GetApplication()->GetDataPath().c_str(),
        "cookies.dat", 0));
    setCookieJarFilename(cookieJarFilename.c_str());
}