HRESULT ScaWebAppExtensionsWrite(IMSAdminBase* piMetabase, LPCWSTR wzRootOfWeb,
                                 SCA_WEB_APPLICATION_EXTENSION* pswappextList
                                )
{
    HRESULT hr = S_OK;

    LPWSTR wzAppExt = NULL;
    DWORD cchAppExt;
    WCHAR wzAppExtension[1024];
    WCHAR wzAppExtensions[65536];
    SCA_WEB_APPLICATION_EXTENSION* pswappext = NULL;

    if (!pswappextList)
        ExitFunction();

    ::ZeroMemory(wzAppExtensions, sizeof(wzAppExtensions));
    wzAppExt = wzAppExtensions;
    cchAppExt = countof(wzAppExtensions);
    pswappext = pswappextList;

    while (pswappext)
    {
        if (0 == lstrcmpW(wzAppExtension, L"*"))
            StringCchPrintfW(wzAppExtension, countof(wzAppExtension), L"*,%s,%d", pswappext->wzExecutable, pswappext->iAttributes);
        else if (*pswappext->wzExtension)
            StringCchPrintfW(wzAppExtension, countof(wzAppExtension), L".%s,%s,%d", pswappext->wzExtension, pswappext->wzExecutable, pswappext->iAttributes);
        else   // blank means "*" (all)
            StringCchPrintfW(wzAppExtension, countof(wzAppExtension), L"*,%s,%d", pswappext->wzExecutable, pswappext->iAttributes);

        // if verbs were specified and not the keyword "all"
        if (pswappext->wzVerbs[0] && CSTR_EQUAL != CompareStringW(LOCALE_INVARIANT, NORM_IGNORECASE, pswappext->wzVerbs, -1, L"all", -1))
        {
            StringCchCatW(wzAppExtension, countof(wzAppExtension), L",");
            StringCchCatW(wzAppExtension, countof(wzAppExtension), pswappext->wzVerbs);
        }

        StringCchCopyW(wzAppExt, cchAppExt, wzAppExtension);
        wzAppExt += lstrlenW(wzAppExtension) + 1;
        cchAppExt -= lstrlenW(wzAppExtension) + 1;
        pswappext = pswappext->pswappextNext;
    }

    if (*wzAppExtensions)
    {
        hr = ScaWriteMetabaseValue(piMetabase, wzRootOfWeb, NULL, MD_SCRIPT_MAPS, METADATA_INHERIT, IIS_MD_UT_FILE, MULTISZ_METADATA, wzAppExtensions);
        ExitOnFailure1(hr, "Failed to write AppExtension: '%S'", wzAppExtension);
    }

LExit:
    return hr;
}