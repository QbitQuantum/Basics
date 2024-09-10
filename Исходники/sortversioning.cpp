    ////////////////////////////////////////////////////////////////////////////
    //
    //  GetSortGetHandle()
    //
    //  Get the SortGetHandle() function for the proper dll version.
    //
    ////////////////////////////////////////////////////////////////////////////
    SORTGETHANDLE GetSortGetHandle(__in DWORD dwVersion)
    {
        if(dwVersion == SORT_VERSION_DEFAULT)
        {
            // If we haven't tried to load the module/proc before do so now
            if (g_hSortDefault == (HMODULE)-1)
            {
                LoadSortDllAndPublish(SORT_DEFAULT_DLL_NAME, SORT_VERSION_DEFAULT, &g_pDefaultGetHandle, &g_pDefaultCloseHandle, &g_hSortDefault);
            }

            // This check is necessary because the LoadSortDllAndPublish call may have failed since some platforms
            // won't have nlssorting.dll (e.g. Windows 8 and above).
            if (g_hSortDefault != (HMODULE)-1) 
            {
                return (SORTGETHANDLE)DecodePointer(g_pDefaultGetHandle);
            }
        }

        HMODULE* pHSortModule; 
        SORTGETHANDLE*   ppGetHandle;
        SORTCLOSEHANDLE* ppCloseHandle;

        if(dwVersion == SORT_VERSION_V4)
        {
            ppGetHandle = &g_pV4GetHandle;
            ppCloseHandle = &g_pV4CloseHandle;
            pHSortModule = &g_hSortCompatV4;
        } 
        else if(dwVersion == SORT_VERSION_WHIDBEY) 
        {
            ppGetHandle = &g_pV2GetHandle;
            ppCloseHandle = &g_pV2CloseHandle;
            pHSortModule = &g_hSortCompatV2;
        }
        else
        {
            // Unsupported sorting version.
            return NULL;
        }

        if(*pHSortModule == (HMODULE) -1)
        {
            // get module name - the module name should be "Sort"+dwVersion.ToString("x8")+".dll"
            WCHAR moduleName[] = W("Sort00000000.dll");
            // replace the "00000000" with the hexadecimal of dwVersion
            LPCWSTR hex = W("0123456789abcdef");
            WCHAR* p = &moduleName[4+8]; // position at end of number part of dll name

            unsigned int value = dwVersion;

            while (value != 0 && p != moduleName) {
                int digit = value & 0xF;
                *--p = hex[digit];
                value >>= 4;
            }

            if(!LoadSortDllAndPublish(&moduleName[0], dwVersion, ppGetHandle, ppCloseHandle, pHSortModule)) 
            {
                // We failed to load a versioned sort dll, try to fall back to the current version.
                // If we haven't tried to load the module/proc before do so now
                if (g_hSortDefault == (HMODULE)-1)
                {
                    LoadSortDllAndPublish(SORT_DEFAULT_DLL_NAME, SORT_VERSION_DEFAULT, &g_pDefaultGetHandle, &g_pDefaultCloseHandle, &g_hSortDefault);
                }

                *pHSortModule = g_hSortDefault;
                *ppCloseHandle = g_pDefaultCloseHandle;
                *ppGetHandle = g_pDefaultGetHandle;
            }           
        }