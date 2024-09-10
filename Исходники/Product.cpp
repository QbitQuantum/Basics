HRESULT ProductValidateVersion(
    __in_z LPCWSTR wzVersion
    )
{
    HRESULT hr = S_OK;

    DWORD dw1 = 0;
    DWORD dw2 = 0;
    DWORD dw3 = 0;
    DWORD dw4 = 0;
    DWORD dwResult = 0;
    WCHAR wcExtra;

    dwResult = swscanf_s(wzVersion, L"%u.%u.%u.%u%lc", &dw1, &dw2, &dw3, &dw4, &wcExtra);

    // Must have 4 components to the version
    if (4 != dwResult)
    {
        hr = HRESULT_FROM_WIN32(ERROR_CLUSTER_INVALID_STRING_FORMAT);
        ExitOnFailure(hr, "Version \"%ls\" wasn't in a valid format - expected version like: 1.0.0.0", wzVersion);
    }

    // TODO: Any additional validation here? Is "0.*" accepted? What about a version component > 65535?

LExit:
    return hr;
}