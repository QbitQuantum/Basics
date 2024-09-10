bool TryRun(const int argc, const wchar_t* argv[], Logger &log, const bool verbose, const bool waitForDebugger, DWORD &exitCode, wchar_t* programPath)
{
    // Assume failure
    exitCode = -1;

    HostEnvironment hostEnvironment(&log);

    wchar_t appPath[MAX_PATH] = W("");
    wchar_t appNiPath[MAX_PATH * 2] = W("");
    wchar_t managedAssemblyFullName[MAX_PATH] = W("");

    wchar_t* filePart = NULL;
    
    if (!::GetFullPathName(programPath, MAX_PATH, appPath, &filePart)) {
        log << W("Failed to get full path: ") << programPath << Logger::endl;
        log << W("Error code: ") << GetLastError() << Logger::endl;
        return false;
    } 

    wcscpy_s(managedAssemblyFullName, appPath);

    *(filePart) = W('\0');

    log << W("Loading: ") << managedAssemblyFullName << Logger::endl;

    wcscpy_s(appNiPath, appPath);
    wcscat_s(appNiPath, MAX_PATH * 2, W(";"));
    wcscat_s(appNiPath, MAX_PATH * 2, appPath);

    // Construct native search directory paths
    wchar_t nativeDllSearchDirs[MAX_PATH * 3];

    wcscpy_s(nativeDllSearchDirs, appPath);
    wchar_t coreLibraries[MAX_PATH];
    size_t outSize;
    if (_wgetenv_s(&outSize, coreLibraries, MAX_PATH, W("CORE_LIBRARIES")) == 0 && outSize > 0)
    {
        wcscat_s(nativeDllSearchDirs, MAX_PATH * 3, W(";"));
        wcscat_s(nativeDllSearchDirs, MAX_PATH * 3, coreLibraries);
    }
    wcscat_s(nativeDllSearchDirs, MAX_PATH * 3, W(";"));
    wcscat_s(nativeDllSearchDirs, MAX_PATH * 3, hostEnvironment.m_coreCLRDirectoryPath);

    // Start the CoreCLR

    ICLRRuntimeHost2 *host = hostEnvironment.GetCLRRuntimeHost();
    if (!host) {
        return false;
    }

    HRESULT hr;

    log << W("Setting ICLRRuntimeHost2 startup flags") << Logger::endl;

    // Default startup flags
    hr = host->SetStartupFlags((STARTUP_FLAGS)
        (STARTUP_FLAGS::STARTUP_LOADER_OPTIMIZATION_SINGLE_DOMAIN | 
        STARTUP_FLAGS::STARTUP_SINGLE_APPDOMAIN)); 
    if (FAILED(hr)) {
        log << W("Failed to set startup flags. ERRORCODE: ") << hr << Logger::endl;
        return false;
    }

    log << W("Starting ICLRRuntimeHost2") << Logger::endl;

    hr = host->Start();
    if (FAILED(hr)) {
        log << W("Failed to start CoreCLR. ERRORCODE: ") << hr << Logger:: endl;
        return false;
    }

    //-------------------------------------------------------------

    // Create an AppDomain

    // Allowed property names:
    // APPBASE
    // - The base path of the application from which the exe and other assemblies will be loaded
    //
    // TRUSTED_PLATFORM_ASSEMBLIES
    // - The list of complete paths to each of the fully trusted assemblies
    //
    // APP_PATHS
    // - The list of paths which will be probed by the assembly loader
    //
    // APP_NI_PATHS
    // - The list of additional paths that the assembly loader will probe for ngen images
    //
    // NATIVE_DLL_SEARCH_DIRECTORIES
    // - The list of paths that will be probed for native DLLs called by PInvoke
    //
    const wchar_t *property_keys[] = { 
        W("TRUSTED_PLATFORM_ASSEMBLIES"),
        W("APP_PATHS"),
        W("APP_NI_PATHS"),
        W("NATIVE_DLL_SEARCH_DIRECTORIES")
		W("AppDomainCompatSwitch"),
    };
    const wchar_t *property_values[] = { 
        // TRUSTED_PLATFORM_ASSEMBLIES
        hostEnvironment.GetTpaList(),
        // APP_PATHS
        appPath,
        // APP_NI_PATHS
        appNiPath,
        // NATIVE_DLL_SEARCH_DIRECTORIES
        nativeDllSearchDirs,
    };


    log << W("Creating an AppDomain") << Logger::endl;
    log << W("TRUSTED_PLATFORM_ASSEMBLIES=") << property_values[0] << Logger::endl;
    log << W("APP_PATHS=") << property_values[1] << Logger::endl;
    log << W("APP_NI_PATHS=") << property_values[2] << Logger::endl;
    log << W("NATIVE_DLL_SEARCH_DIRECTORIES=") << property_values[3] << Logger::endl;

    DWORD domainId;

    hr = host->CreateAppDomainWithManager(
        hostEnvironment.GetHostExeName(),   // The friendly name of the AppDomain
        // Flags:
        // APPDOMAIN_ENABLE_PLATFORM_SPECIFIC_APPS
        // - By default CoreCLR only allows platform neutral assembly to be run. To allow
        //   assemblies marked as platform specific, include this flag
        //
        // APPDOMAIN_ENABLE_PINVOKE_AND_CLASSIC_COMINTEROP
        // - Allows sandboxed applications to make P/Invoke calls and use COM interop
        //
        // APPDOMAIN_SECURITY_SANDBOXED
        // - Enables sandboxing. If not set, the app is considered full trust
        //
        // APPDOMAIN_IGNORE_UNHANDLED_EXCEPTION
        // - Prevents the application from being torn down if a managed exception is unhandled
        //
        APPDOMAIN_ENABLE_PLATFORM_SPECIFIC_APPS | 
        APPDOMAIN_ENABLE_PINVOKE_AND_CLASSIC_COMINTEROP |
        APPDOMAIN_DISABLE_TRANSPARENCY_ENFORCEMENT,
        NULL,                // Name of the assembly that contains the AppDomainManager implementation
        NULL,                    // The AppDomainManager implementation type name
        sizeof(property_keys)/sizeof(wchar_t*),  // The number of properties
        property_keys,
        property_values,
        &domainId);

    if (FAILED(hr)) {
        log << W("Failed call to CreateAppDomainWithManager. ERRORCODE: ") << hr << Logger::endl;
        return false;
    }

    if(waitForDebugger)
    {
        if(!IsDebuggerPresent())
        {
            log << W("Waiting for the debugger to attach. Press any key to continue ...") << Logger::endl;
            getchar();
            if (IsDebuggerPresent())
            {
                log << "Debugger is attached." << Logger::endl;
            }
            else
            {
                log << "Debugger failed to attach." << Logger::endl;
            }
        }
    }

    hr = host->ExecuteAssembly(domainId, managedAssemblyFullName, argc, (argc)?&(argv[0]):NULL, &exitCode);
    if (FAILED(hr)) {
        log << W("Failed call to ExecuteAssembly. ERRORCODE: ") << hr << Logger::endl;
        return false;
    }

    log << W("App exit value = ") << exitCode << Logger::endl;


    //-------------------------------------------------------------

    // Unload the AppDomain

    log << W("Unloading the AppDomain") << Logger::endl;

    hr = host->UnloadAppDomain(
        domainId, 
        true);                          // Wait until done

    if (FAILED(hr)) {
        log << W("Failed to unload the AppDomain. ERRORCODE: ") << hr << Logger::endl;
        return false;
    }


    //-------------------------------------------------------------

    // Stop the host

    log << W("Stopping the host") << Logger::endl;

    hr = host->Stop();

    if (FAILED(hr)) {
        log << W("Failed to stop the host. ERRORCODE: ") << hr << Logger::endl;
        return false;
    }

    //-------------------------------------------------------------

    // Release the reference to the host

    log << W("Releasing ICLRRuntimeHost2") << Logger::endl;

    host->Release();

    return true;

}