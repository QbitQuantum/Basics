bool GpuCapabilitiesWindows::WMIinit() {

    // Code based upon:  "Example: Getting WMI Data from the Local Computer"
    // http://msdn2.microsoft.com/en-us/library/aa390423.aspx

    if (isWMIinited()) {
        LWARNING("The WMI connection has already been inited.");
        return false;
    }

    HRESULT hRes;

    // Step 1: --------------------------------------------------
    // Initialize COM. ------------------------------------------

    hRes = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
    if (FAILED(hRes)) {
        LWARNING("CoInitializeEx() failed");
        return false;
    }

    // Step 2: --------------------------------------------------
    // Set general COM security levels --------------------------
    // Note: If you are using Windows 2000, you need to specify -
    // the default authentication credentials for a user by using
    // a SOLE_AUTHENTICATION_LIST structure in the pAuthList ----
    // parameter of CoInitializeSecurity ------------------------

    hRes =  CoInitializeSecurity(
        NULL,
        -1,                          // COM authentication
        NULL,                        // Authentication services
        NULL,                        // Reserved
        RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
        RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
        NULL,                        // Authentication info
        EOAC_NONE,                   // Additional capabilities
        NULL                         // Reserved
        );

    if (FAILED(hRes)) {

        // Failure of CoInitializeSecurity is not necessarily critical
        // => do not abort initialization

        if (hRes == RPC_E_TOO_LATE) {
            LDEBUG("CoInitializeSecurity failed. HRESULT = RPC_E_TOO_LATE.");
        }
        else if (hRes == RPC_E_NO_GOOD_SECURITY_PACKAGES) {
            LDEBUG("CoInitializeSecurity failed. HRESULT = RPC_E_NO_GOOD_SECURITY_PACKAGES.");
        }
        /*else if (hres == E_OUT_OF_MEMORY) {
            LDEBUG("CoInitializeSecurity failed. HRESULT = E_OUT_OF_MEMORY.");
        } */
        else {
            LDEBUG("CoInitializeSecurity failed. HRESULT = " << hRes);
        }
    }
    else {
        LDEBUG("CoInitializeSecurity successful");

    }

    // Step 3: ---------------------------------------------------
    // Obtain the initial locator to WMI -------------------------

    hRes = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID *) &pIWbemLocator_);

    if (FAILED(hRes)) {
        LWARNING("Failed to create IWbemLocator object. Err code = 0x" << hRes);
        pIWbemLocator_ = 0;
        CoUninitialize();
        return false;     // error is critical
    }

    LDEBUG("IWbemLocator object successfully created");

    // Step 4: -----------------------------------------------------
    // Connect to WMI through the IWbemLocator::ConnectServer method

    // Connect to the root\cimv2 namespace with
    // the current user and obtain pointer pSvc
    // to make IWbemServices calls.
    hRes = pIWbemLocator_->ConnectServer(
         _bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
         NULL,                    // User name. NULL = current user
         NULL,                    // User password. NULL = current
         0,                       // Locale. NULL indicates current
         NULL,                    // Security flags.
         0,                       // Authority (e.g. Kerberos)
         0,                       // Context object
         &pWbemServices_          // pointer to IWbemServices proxy
         );

    if (FAILED(hRes)) {
        LWARNING("Could not connect to WMI server. Error code = 0x" << hRes);
        pIWbemLocator_->Release();
        CoUninitialize();
        pIWbemLocator_ = 0;
        pWbemServices_ = 0;
        return false;            // error is critical
    }

    LDEBUG("Connected to ROOT\\CIMV2 WMI namespace");


    // Step 5: --------------------------------------------------
    // Set security levels on the proxy -------------------------

    hRes = CoSetProxyBlanket(
       pWbemServices_,              // Indicates the proxy to set
       RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
       RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
       NULL,                        // Server principal name
       RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx
       RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
       NULL,                        // client identity
       EOAC_NONE                    // proxy capabilities
    );

    if (FAILED(hRes)) {
        LWARNING("Could not set proxy blanket. Error code = 0x" << hRes);
        pWbemServices_->Release();
        pIWbemLocator_->Release();
        CoUninitialize();
        pIWbemLocator_ = 0;
        pWbemServices_ = 0;
        return false;               // error is critical
    }
    LDEBUG("WMI successfully inited");
    return true;

}