static HRESULT GetTargetPath(
    __in eOBJECTTYPE eType,
    __in LPCWSTR pwzSecureObject,
    __out LPWSTR* ppwzTargetPath
    )
{
    HRESULT hr = S_OK;

    PMSIHANDLE hView = NULL;
    PMSIHANDLE hRecObject = NULL;
    PMSIHANDLE hRec = NULL;

    int iRoot = 0;
    int iAllUsers = 0;
    LPWSTR pwzKey = NULL;
    LPWSTR pwzFormattedString = NULL;

    if (OT_SERVICE == eType)
    {
        hr = WcaTableExists(L"ServiceInstall");
        if (S_FALSE == hr)
        {
            hr = E_UNEXPECTED;
        }
        ExitOnFailure(hr, "failed to open ServiceInstall table to secure object");

        hr = WcaOpenView(wzQUERY_SERVICEINSTALL, &hView);
        ExitOnFailure(hr, "failed to open view on ServiceInstall table");

        // create a record that stores the object to secure
        hRec = MsiCreateRecord(1);
        MsiRecordSetStringW(hRec, 1, pwzSecureObject);

        // execute a view looking for the object's ServiceInstall.ServiceInstall row.
        hr = WcaExecuteView(hView, hRec);
        ExitOnFailure(hr, "failed to execute view on ServiceInstall table");
        hr = WcaFetchSingleRecord(hView, &hRecObject);
        ExitOnFailure(hr, "failed to fetch ServiceInstall row for secure object");

        hr = WcaGetRecordFormattedString(hRecObject, QSSI_NAME, ppwzTargetPath);
        ExitOnFailure1(hr, "failed to get service name for secure object: %ls", pwzSecureObject);
    }
    else if (OT_FOLDER == eType)
    {
        hr = WcaGetTargetPath(pwzSecureObject, ppwzTargetPath);
        ExitOnFailure1(hr, "failed to get target path for directory id: %ls", pwzSecureObject);
    }
    else if (OT_FILE == eType)
    {
        hr = StrAllocFormatted(&pwzFormattedString, L"[#%s]", pwzSecureObject);
        ExitOnFailure1(hr, "failed to create formatted string for securing file object: %ls", pwzSecureObject);

        hr = WcaGetFormattedString(pwzFormattedString, ppwzTargetPath);
        ExitOnFailure2(hr, "failed to get file path from formatted string: %ls for secure object: %ls", pwzFormattedString, pwzSecureObject);
    }
    else if (OT_REGISTRY == eType)
    {
        hr = WcaTableExists(L"Registry");
        if (S_FALSE == hr)
        {
            hr = E_UNEXPECTED;
        }
        ExitOnFailure(hr, "failed to open Registry table to secure object");

        hr = WcaOpenView(wzQUERY_REGISTRY, &hView);
        ExitOnFailure(hr, "failed to open view on Registry table");

        // create a record that stores the object to secure
        hRec = MsiCreateRecord(1);
        MsiRecordSetStringW(hRec, 1, pwzSecureObject);

        // execute a view looking for the object's Registry row
        hr = WcaExecuteView(hView, hRec);
        ExitOnFailure(hr, "failed to execute view on Registry table");
        hr = WcaFetchSingleRecord(hView, &hRecObject);
        ExitOnFailure(hr, "failed to fetch Registry row for secure object");

        hr = WcaGetRecordInteger(hRecObject, QSOC_REGROOT, &iRoot);
        ExitOnFailure1(hr, "Failed to get reg key root for secure object: %ls", pwzSecureObject);

        hr = WcaGetRecordFormattedString(hRecObject, QSOC_REGKEY, &pwzKey);
        ExitOnFailure1(hr, "Failed to get reg key for secure object: %ls", pwzSecureObject);

        // Decode the root value
        if (-1 == iRoot)
        {
            // They didn't specify a root so that means it's either HKCU or HKLM depending on ALLUSERS property
            hr = WcaGetIntProperty(L"ALLUSERS", &iAllUsers);
            ExitOnFailure(hr, "failed to get value of ALLUSERS property");

            if (1 == iAllUsers)
            {
                hr = StrAllocString(ppwzTargetPath, L"MACHINE\\", 0);
                ExitOnFailure(hr, "failed to allocate target registry string with HKLM root");
            }
            else
            {
                hr = StrAllocString(ppwzTargetPath, L"CURRENT_USER\\", 0);
                ExitOnFailure(hr, "failed to allocate target registry string with HKCU root");
            }
        }
        else if (msidbRegistryRootClassesRoot == iRoot)
        {
            hr = StrAllocString(ppwzTargetPath, L"CLASSES_ROOT\\", 0);
            ExitOnFailure(hr, "failed to allocate target registry string with HKCR root");
        }
        else if (msidbRegistryRootCurrentUser == iRoot)
        {
            hr = StrAllocString(ppwzTargetPath, L"CURRENT_USER\\", 0);
            ExitOnFailure(hr, "failed to allocate target registry string with HKCU root");
        }
        else if (msidbRegistryRootLocalMachine == iRoot)
        {
            hr = StrAllocString(ppwzTargetPath, L"MACHINE\\", 0);
            ExitOnFailure(hr, "failed to allocate target registry string with HKLM root");
        }
        else if (msidbRegistryRootUsers == iRoot)
        {
            hr = StrAllocString(ppwzTargetPath, L"USERS\\", 0);
            ExitOnFailure(hr, "failed to allocate target registry string with HKU root");
        }
        else
        {
            ExitOnFailure2(hr = E_UNEXPECTED, "Unknown registry key root specified for secure object: '%ls' root: %d", pwzSecureObject, iRoot);
        }
        
        hr = StrAllocConcat(ppwzTargetPath, pwzKey, 0);
        ExitOnFailure2(hr, "Failed to concat key: %ls for secure object: %ls", pwzKey, pwzSecureObject);
    }
    else
    {
        AssertSz(FALSE, "How did you get here?");
        ExitOnFailure1(hr = E_UNEXPECTED, "Unknown secure object type: %d", eType);
    }

LExit:
    ReleaseStr(pwzFormattedString);
    ReleaseStr(pwzKey);

    return hr;
}