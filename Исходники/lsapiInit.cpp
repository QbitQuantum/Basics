void LSAPIInit::setLitestepVars()
{
    wchar_t wzTemp[MAX_PATH];
    DWORD dwLength = MAX_PATH;

    // just using a shorter name, no real reason to re-assign.
    SettingsManager *pSM = m_smSettingsManager;

    // Set the variable "litestepdir" since it was never set
    if (SUCCEEDED(StringCchCopyW(wzTemp, MAX_PATH, m_wzLitestepPath)))
    {
        PathAddBackslashEx(wzTemp, MAX_PATH);
        PathQuoteSpacesW(wzTemp);
        pSM->SetVariable(L"litestepdir", wzTemp);
    }

    if (GetWindowsDirectoryW(wzTemp, MAX_PATH))
    {
        PathAddBackslashEx(wzTemp, MAX_PATH);
        pSM->SetVariable(L"windir", wzTemp);
    }

    if (GetUserNameW(wzTemp, &dwLength))
    {
        PathQuoteSpacesW(wzTemp);
        pSM->SetVariable(L"username", wzTemp);
    }

    pSM->SetVariable(L"nl", L"\n", true);
    pSM->SetVariable(L"cr", L"\r", true);
    pSM->SetVariable(L"dollar", L"$", true);
    pSM->SetVariable(L"at", L"@", true);

    pSM->SetVariable(L"bitbucket", L"::{645FF040-5081-101B-9F08-00AA002F954E}");
    pSM->SetVariable(L"documents", L"::{450D8FBA-AD25-11D0-98A8-0800361B1103}");
    pSM->SetVariable(L"drives", L"::{20D04FE0-3AEA-1069-A2D8-08002B30309D}");
    pSM->SetVariable(L"network", L"::{208D2C60-3AEA-1069-A2D7-08002B30309D}");
    pSM->SetVariable(L"controls", L"::{20D04FE0-3AEA-1069-A2D8-08002B30309D}\\::{21EC2020-3AEA-1069-A2DD-08002B30309D}");
    pSM->SetVariable(L"dialup", L"::{20D04FE0-3AEA-1069-A2D8-08002B30309D}\\::{992CFFA0-F557-101A-88EC-00DD010CCC48}");
    pSM->SetVariable(L"networkanddialup", L"::{20D04FE0-3AEA-1069-A2D8-08002B30309D}\\::{7007ACC7-3202-11D1-AAD2-00805FC1270E}");
    pSM->SetVariable(L"printers", L"::{20D04FE0-3AEA-1069-A2D8-08002B30309D}\\::{2227A280-3AEA-1069-A2DE-08002B30309D}");
    pSM->SetVariable(L"scheduled", L"::{20D04FE0-3AEA-1069-A2D8-08002B30309D}\\::{D6277990-4C6A-11CF-8D87-00AA0060F5BF}");
    pSM->SetVariable(L"admintools", L"::{20D04FE0-3AEA-1069-A2D8-08002B30309D}\\::{21EC2020-3AEA-1069-A2DD-08002B30309D}\\::{D20EA4E1-3957-11d2-A40B-0C5020524153}");

    setShellFolderVariable(L"quicklaunch", LS_CSIDL_QUICKLAUNCH);
    setShellFolderVariable(L"commondesktopdir", CSIDL_COMMON_DESKTOPDIRECTORY);
    setShellFolderVariable(L"commonfavorites", CSIDL_COMMON_FAVORITES);
    setShellFolderVariable(L"commonprograms", CSIDL_COMMON_PROGRAMS);
    setShellFolderVariable(L"commonstartmenu", CSIDL_COMMON_STARTMENU);
    setShellFolderVariable(L"commonstartup", CSIDL_COMMON_STARTUP);
    setShellFolderVariable(L"cookies", CSIDL_COOKIES);
    setShellFolderVariable(L"desktop", CSIDL_DESKTOP);
    setShellFolderVariable(L"desktopdir", CSIDL_DESKTOPDIRECTORY);
    setShellFolderVariable(L"favorites", CSIDL_FAVORITES);
    setShellFolderVariable(L"fonts", CSIDL_FONTS);
    setShellFolderVariable(L"history", CSIDL_HISTORY);
    setShellFolderVariable(L"internet", CSIDL_INTERNET);
    setShellFolderVariable(L"internetcache", CSIDL_INTERNET_CACHE);
    setShellFolderVariable(L"nethood", CSIDL_NETHOOD);
    setShellFolderVariable(L"documentsdir", CSIDL_PERSONAL);
    setShellFolderVariable(L"printhood", CSIDL_PRINTHOOD);
    setShellFolderVariable(L"programs", CSIDL_PROGRAMS);
    setShellFolderVariable(L"recent", CSIDL_RECENT);
    setShellFolderVariable(L"sendto", CSIDL_SENDTO);
    setShellFolderVariable(L"startmenu", CSIDL_STARTMENU);
    setShellFolderVariable(L"startup", CSIDL_STARTUP);
    setShellFolderVariable(L"templates", CSIDL_TEMPLATES);
    setShellFolderVariable(L"commonadmintoolsdir", CSIDL_COMMON_ADMINTOOLS);
    setShellFolderVariable(L"admintoolsdir", CSIDL_ADMINTOOLS);

    //
    // Set version identification variables
    //
    struct VersionToVariable
    {
        UINT uVersion;
        LPCWSTR pszVariable;
    }
    versions[] = \
    {
        { WINVER_WIN95,     L"Win95"      },
        { WINVER_WIN98,     L"Win98"      },
        { WINVER_WINME,     L"WinME"      },

        { WINVER_WINNT4,    L"WinNT4"     },
        { WINVER_WIN2000,   L"Win2000"    },
        { WINVER_WINXP,     L"WinXP"      },
        { WINVER_VISTA,     L"WinVista"   },
        { WINVER_WIN7,      L"Win7"       },
        { WINVER_WIN8,      L"Win8"       },
        { WINVER_WIN81,     L"Win81"      },

        { WINVER_WIN2003,   L"Win2003"    },
        { WINVER_WHS,       L"Win2003"    },  // WHS is Win2003 in disguise
        { WINVER_WIN2008,   L"Win2008"    },
        { WINVER_WIN2008R2, L"Win2008R2"  },
        { WINVER_WIN2012,   L"Win2012"    },
        { WINVER_WIN2012R2, L"Win2012R2"  }
    };

    UINT uVersion = GetWindowsVersion();

    for (size_t idx = 0; idx < COUNTOF(versions); ++idx)
    {
        if (versions[idx].uVersion == uVersion)
        {
            pSM->SetVariable(versions[idx].pszVariable, L"true");
        }
        else
        {
            pSM->SetVariable(versions[idx].pszVariable, L"false");
        }
    }

    if (IsOS(OS_NT))
    {
        pSM->SetVariable(L"Win9x", L"false");
        pSM->SetVariable(L"WinNT", L"true");
    }
    else
    {
        pSM->SetVariable(L"Win9x", L"true");
        pSM->SetVariable(L"WinNT", L"false");
    }

#if defined(_WIN64)
    pSM->SetVariable(L"Win64", L"true");
#else
    if (IsOS(OS_WOW6432))
    {
        pSM->SetVariable(L"Win64", L"true");
    }
    else
    {
        pSM->SetVariable(L"Win64", L"false");
    }
#endif

    // screen resolution
    StringCchPrintfW(wzTemp, MAX_PATH, L"%d", GetSystemMetrics(SM_CXSCREEN));
    pSM->SetVariable(L"ResolutionX", wzTemp);

    StringCchPrintfW(wzTemp, MAX_PATH, L"%d", GetSystemMetrics(SM_CYSCREEN));
    pSM->SetVariable(L"ResolutionY", wzTemp);

    // build date/time from PE headers
    getCompileTime(wzTemp, MAX_PATH);
    pSM->SetVariable(L"CompileDate", wzTemp);

#if defined(LS_CUSTOM_INCLUDEFOLDER)
    pSM->SetVariable(L"IncludeFolder", L"1");
#endif // LS_CUSTOM_INCLUDEFOLDER
}