// 
// Tries to find aspnetcorerh.dll from the application
// Calls into hostfxr.dll to find it.
// Will leave hostfxr.dll loaded as it will be used again to call hostfxr_main.
// 
HRESULT
APPLICATION_INFO::FindNativeAssemblyFromHostfxr(
    STRU* struFilename
)
{
    HRESULT     hr = S_OK;
    STRU        struApplicationFullPath;
    STRU        struNativeSearchPaths;
    STRU        struNativeDllLocation;
    HMODULE     hmHostFxrDll = NULL;
    INT         intHostFxrExitCode = 0;
    INT         intIndex = -1;
    INT         intPrevIndex = 0;
    BOOL        fFound = FALSE;
    DWORD       dwBufferSize = 1024 * 10;
    DWORD       dwRequiredBufferSize = 0;

    DBG_ASSERT(struFileName != NULL);

    hmHostFxrDll = LoadLibraryW(m_pConfiguration->QueryHostFxrFullPath());

    if (hmHostFxrDll == NULL)
    {
        // Could not load hostfxr
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Finished;
    }

    hostfxr_get_native_search_directories_fn pFnHostFxrSearchDirectories = (hostfxr_get_native_search_directories_fn)
        GetProcAddress(hmHostFxrDll, "hostfxr_get_native_search_directories");

    if (pFnHostFxrSearchDirectories == NULL)
    {
        // Host fxr version is incorrect (need a higher version).
        // TODO log error 
        hr = E_FAIL;
        goto Finished;
    }

    if (FAILED(hr = struNativeSearchPaths.Resize(dwBufferSize)))
    {
        goto Finished;
    }

    while (TRUE)
    {
        intHostFxrExitCode = pFnHostFxrSearchDirectories(
            m_pConfiguration->QueryHostFxrArgCount(),
            m_pConfiguration->QueryHostFxrArguments(),
            struNativeSearchPaths.QueryStr(),
            dwBufferSize,
            &dwRequiredBufferSize
        );

        if (intHostFxrExitCode == 0)
        {
            break;
        }
        else if (dwRequiredBufferSize > dwBufferSize)
        {
            dwBufferSize = dwRequiredBufferSize + 1; // for null terminator

            if (FAILED(hr = struNativeSearchPaths.Resize(dwBufferSize)))
            {
                goto Finished;
            }
        }
        else
        {
            hr = E_FAIL;
            // Log "Error finding native search directories from aspnetcore application.
            goto Finished;
        }
    }

    if (FAILED(hr = struNativeSearchPaths.SyncWithBuffer()))
    {
        goto Finished;
    }

    fFound = FALSE;

    // The native search directories are semicolon delimited.
    // Split on semicolons, append aspnetcorerh.dll, and check if the file exists.
    while ((intIndex = struNativeSearchPaths.IndexOf(L";", intPrevIndex)) != -1)
    {
        if (FAILED(hr = struNativeDllLocation.Copy(&struNativeSearchPaths.QueryStr()[intPrevIndex], intIndex - intPrevIndex)))
        {
            goto Finished;
        }

        if (!struNativeDllLocation.EndsWith(L"\\"))
        {
            if (FAILED(hr = struNativeDllLocation.Append(L"\\")))
            {
                goto Finished;
            }
        }

        if (FAILED(hr = struNativeDllLocation.Append(g_pwzAspnetcoreRequestHandlerName)))
        {
            goto Finished;
        }

        if (UTILITY::CheckIfFileExists(struNativeDllLocation.QueryStr()))
        {
            if (FAILED(hr = struFilename->Copy(struNativeDllLocation)))
            {
                goto Finished;
            }
            fFound = TRUE;
            break;
        }

        intPrevIndex = intIndex + 1;
    }

    if (!fFound)
    {
        hr = E_FAIL;
        goto Finished;
    }

Finished:
    if (FAILED(hr) && hmHostFxrDll != NULL)
    {
        FreeLibrary(hmHostFxrDll);
    }
    return hr;
}