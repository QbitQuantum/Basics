std::string GLCaps::getDriverVersion() {
    if (computeVendor() == MESA) {
        // Mesa includes the driver version in the renderer version
        // e.g., "1.5 Mesa 6.4.2"
        
        static std::string _glVersion = (char*)glGetString(GL_VERSION);
        int i = _glVersion.rfind(' ');
        if (i == (int)std::string::npos) {
            return "Unknown (bad MESA driver string)";
        } else {
            return _glVersion.substr(i + 1, _glVersion.length() - i);
        }
    }
    
#   ifdef G3D_WIN32
    
    std::string driver;
    
        // Locate the windows\system directory
    {
            char sysDir[1024];
            int sysSize = GetSystemDirectoryA(sysDir, 1024);
            if (sysSize == 0) {
                return "Unknown (can't find Windows directory)";
            }
            driver = sysDir;
        }

        switch (computeVendor()) {
        case ATI:
            driver = driver + "\\ati2dvag.dll";
            break;

        case NVIDIA:
            driver = driver + "\\nv4_disp.dll";
            break;
		
        default:
            return "Unknown (Unknown vendor)";

        }

        char* lpdriver = const_cast<char*>(driver.c_str());
        DWORD dummy;

        int size = GetFileVersionInfoSizeA(lpdriver, &dummy);
        if (size == 0) {
            return "Unknown (Can't find driver)";
        }

        void* buffer = new uint8[size];

        if (GetFileVersionInfoA(lpdriver, 0, size, buffer) == 0) {
            delete[] (uint8*)buffer;
            return "Unknown";
        }

	    // Interpret the VS_VERSIONINFO header pseudo-struct
	    VS_VERSIONINFO* pVS = (VS_VERSIONINFO*)buffer;
        debugAssert(!wcscmp(pVS->szKey, L"VS_VERSION_INFO"));

	    uint8* pVt = (uint8*) &pVS->szKey[wcslen(pVS->szKey) + 1];

        #define roundoffs(a,b,r)	(((uint8*)(b) - (uint8*)(a) + ((r) - 1)) & ~((r) - 1))
        #define roundpos(b, a, r)	(((uint8*)(a)) + roundoffs(a, b, r))

	    VS_FIXEDFILEINFO* pValue = (VS_FIXEDFILEINFO*) roundpos(pVt, pVS, 4);

        #undef roundoffs
        #undef roundpos

        std::string result = "Unknown (No information)";

	    if (pVS->wValueLength) {
	        result = format("%d.%d.%d.%d",
                pValue->dwProductVersionMS >> 16,
                pValue->dwProductVersionMS & 0xFFFF,
	            pValue->dwProductVersionLS >> 16,
                pValue->dwProductVersionLS & 0xFFFF);
        }