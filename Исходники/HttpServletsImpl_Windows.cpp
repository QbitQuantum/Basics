std::string ServerInfoServlet::getSystemInfo(){
    int bufferSize = 100;
    wchar_t* str = new wchar_t[bufferSize];
//#pragma warning (disable : 4996)
    OSVERSIONINFOEX osvi;
    SYSTEM_INFO si;
    BOOL bOsVersionInfoEx;
    DWORD dwType; ZeroMemory(&si, sizeof(SYSTEM_INFO));
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
#pragma warning (disable : 4996)
    bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO*)&osvi);
#pragma warning (default : 4996)
    if (bOsVersionInfoEx == 0)
        return false;
    // Call GetNativeSystemInfo if supported or GetSystemInfo otherwise.
    PGNSI pGNSI = (PGNSI)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetNativeSystemInfo");
    if (NULL != pGNSI)
        pGNSI(&si);
    else
        GetSystemInfo(&si);
    // Check for unsupported OS
    if (VER_PLATFORM_WIN32_NT != osvi.dwPlatformId || osvi.dwMajorVersion <= 4) {
        return false;
    }
    std::wstringstream os;
    os << L"Microsoft ";
    // Test for the specific product.
    if (osvi.dwMajorVersion == 6)
    {
        if (osvi.dwMinorVersion == 0)
        {
            if (osvi.wProductType == VER_NT_WORKSTATION)
                os << "Windows Vista ";
            else
                os << "Windows Server 2008 ";
        }
        else if (osvi.dwMinorVersion == 1)
        {
            if (osvi.wProductType == VER_NT_WORKSTATION)
                os << "Windows 7 ";
            else
                os << "Windows Server 2008 R2 ";
        }
        else if (osvi.dwMinorVersion == 2){
            os << "Windows 8 ";
        }
        else if (osvi.dwMinorVersion == 3){
            os << "Windows 8.1 ";
        }
        else{
            os << "Unkown OS ";
        }
        PGPI pGPI = (PGPI)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetProductInfo");
        pGPI(osvi.dwMajorVersion, osvi.dwMinorVersion, 0, 0, &dwType);
        switch (dwType)
        {
        case PRODUCT_ULTIMATE:
            os << "Ultimate Edition";
            break;
        case PRODUCT_PROFESSIONAL:
            os << "Professional";
            break;
        case PRODUCT_HOME_PREMIUM:
            os << "Home Premium Edition";
            break;
        case PRODUCT_HOME_BASIC:
            os << "Home Basic Edition";
            break;
        case PRODUCT_ENTERPRISE:
            os << "Enterprise Edition";
            break;
        case PRODUCT_BUSINESS:
            os << "Business Edition";
            break;
        case PRODUCT_STARTER:
            os << "Starter Edition";
            break;
        case PRODUCT_CLUSTER_SERVER:
            os << "Cluster Server Edition";
            break;
        case PRODUCT_DATACENTER_SERVER:
            os << "Datacenter Edition";
            break;
        case PRODUCT_DATACENTER_SERVER_CORE:
            os << "Datacenter Edition (core installation)";
            break;
        case PRODUCT_ENTERPRISE_SERVER:
            os << "Enterprise Edition";
            break;
        case PRODUCT_ENTERPRISE_SERVER_CORE:
            os << "Enterprise Edition (core installation)";
            break;
        case PRODUCT_ENTERPRISE_SERVER_IA64:
            os << "Enterprise Edition for Itanium-based Systems";
            break;
        case PRODUCT_SMALLBUSINESS_SERVER:
            os << "Small Business Server";
            break;
        case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
            os << "Small Business Server Premium Edition";
            break;
        case PRODUCT_STANDARD_SERVER:
            os << "Standard Edition";
            break;
        case PRODUCT_STANDARD_SERVER_CORE:
            os << "Standard Edition (core installation)";
            break;
        case PRODUCT_WEB_SERVER:
            os << "Web Server Edition";
            break;
        }
    }
    if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
    {
        if (GetSystemMetrics(SM_SERVERR2))
            os << "Windows Server 2003 R2, ";
        else if (osvi.wSuiteMask & VER_SUITE_STORAGE_SERVER)
            os << "Windows Storage Server 2003";
        else if (osvi.wSuiteMask & VER_SUITE_WH_SERVER)
            os << "Windows Home Server";
        else if (osvi.wProductType == VER_NT_WORKSTATION &&
            si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
        {
            os << "Windows XP Professional x64 Edition";
        }
        else
            os << "Windows Server 2003, ";  // Test for the server type.
        if (osvi.wProductType != VER_NT_WORKSTATION)
        {
            if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
            {
                if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
                    os << "Datacenter Edition for Itanium-based Systems";
                else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
                    os << "Enterprise Edition for Itanium-based Systems";
            }
            else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
            {
                if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
                    os << "Datacenter x64 Edition";
                else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
                    os << "Enterprise x64 Edition";
                else
                    os << "Standard x64 Edition";
            }
            else
            {
                if (osvi.wSuiteMask & VER_SUITE_COMPUTE_SERVER)
                    os << "Compute Cluster Edition";
                else if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
                    os << "Datacenter Edition";
                else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
                    os << "Enterprise Edition";
                else if (osvi.wSuiteMask & VER_SUITE_BLADE)
                    os << "Web Edition";
                else
                    os << "Standard Edition";
            }
        }
    }
    if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
    {
        os << "Windows XP ";
        if (osvi.wSuiteMask & VER_SUITE_PERSONAL)
            os << "Home Edition";
        else
            os << "Professional";
    }
    if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
    {
        os << "Windows 2000 ";  if (osvi.wProductType == VER_NT_WORKSTATION)
        {
            os << "Professional";
        }
        else
        {
            if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
                os << "Datacenter Server";
            else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
                os << "Advanced Server";
            else
                os << "Server";
        }
    }
    // Include service pack (if any) and build number.
    if (wcslen(osvi.szCSDVersion) > 0) {
        os << " " << osvi.szCSDVersion;
    }
    os << L" (build " << osvi.dwBuildNumber << L")"; if (osvi.dwMajorVersion >= 6) {
        if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
            os << ", 64-bit";
        else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
            os << ", 32-bit";
    }
    wcscpy_s(str, bufferSize, os.str().c_str());
    // convert wchar* to string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string narrow = converter.to_bytes(str);
    delete str;

    return narrow;
}