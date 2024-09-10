static HRESULT DeleteEmptyRegistryKeys(
    __in LEGACY_SYNC_PRODUCT_SESSION *pSyncProductSession
    )
{
    HRESULT hr = S_OK;
    const LEGACY_REGISTRY_KEY *rgRegKeys = pSyncProductSession->product.rgRegKeys;
    const DWORD cRegKeys = pSyncProductSession->product.cRegKeys;
    DWORD dwIndex = 0;
    LPWSTR pwcLastBackslash = NULL;
    LPWSTR sczParentKey = NULL;

    for (DWORD i = 0; i < cRegKeys; ++i)
    {
        hr = DeleteEmptyRegistryKeyChildren(rgRegKeys[i].dwRoot, rgRegKeys[i].sczKey);
        // This code is just an FYI that the key was not empty and so wasn't deleted. It's not an error, so ignore it.
        if (HRESULT_FROM_WIN32(ERROR_DIR_NOT_EMPTY) == hr)
        {
            hr = S_OK;
            continue;
        }
        ExitOnFailure(hr, "Failed to check for empty keys and delete them at root: %u, subkey: %ls", rgRegKeys[i].dwRoot, rgRegKeys[i].sczKey);

        hr = StrAllocString(&sczParentKey, rgRegKeys[i].sczKey, 0);
        ExitOnFailure(hr, "Failed to allocate copy of subkey");

        // Eliminate any trailing backslashes from the key first, if there are any
        dwIndex = lstrlenW(sczParentKey);
        if (0 == dwIndex)
        {
            hr = E_INVALIDARG;
            ExitOnFailure(hr, "Unexpected empty parent key encountered while deleting empty registry keys");
        }

        --dwIndex; // Start at the last character of the string
        while (dwIndex > 0 && sczParentKey[dwIndex] == L'\\')
        {
            sczParentKey[dwIndex] = L'\0';
            --dwIndex;
        }

        if (0 == dwIndex)
        {
            hr = E_INVALIDARG;
            ExitOnFailure(hr, "Parent key was entirely composed of backslashes!");
        }

        // Now delete any empty parent keys we see as well
        while (NULL != (pwcLastBackslash = wcsrchr(sczParentKey, L'\\')))
        {
            hr = RegDelete(ManifestConvertToRootKey(rgRegKeys[i].dwRoot), sczParentKey, REG_KEY_DEFAULT, FALSE);
            // This code is just an FYI that the key was not empty and so wasn't deleted. It's not an error, so ignore it.
            if (FAILED(hr))
            {
                LogErrorString(hr, "Failed to check for empty parent keys and delete them at root: %u, subkey: %ls", rgRegKeys[i].dwRoot, sczParentKey);
                hr = S_OK;
                break;
            }

            *pwcLastBackslash = L'\0';
        }
    }

LExit:
    ReleaseStr(sczParentKey);

    return hr;
}