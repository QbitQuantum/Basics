HRESULT GetShellItemFromCommandLine(REFIID riid, void **ppv)
{
    *ppv = NULL;

    HRESULT hr = E_FAIL;
    int cArgs;
    PWSTR *ppszCmd = CommandLineToArgvW(GetCommandLineW(), &cArgs);
    if (ppszCmd && cArgs > 1)
    {
        WCHAR szSpec[MAX_PATH];
        szSpec[0] = 0;

        // skip all parameters that begin with "-" or "/" to try to find the
        // file name. this enables parameters to be present on the cmd line
        // and not get in the way of this function
        for (int i = 1; (szSpec[0] == 0) && (i < cArgs); i++)
        {
            if ((*ppszCmd[i] != L'-') && (*ppszCmd[i] != L'/'))
            {
                StringCchCopyW(szSpec, ARRAYSIZE(szSpec), ppszCmd[i]);
                PathUnquoteSpacesW(szSpec);
            }
        }

        hr = szSpec[0] ? S_OK : E_FAIL; // protect against empty
        if (SUCCEEDED(hr))
        {
            hr = SHCreateItemFromParsingName(szSpec, NULL, riid, ppv);
            if (FAILED(hr))
            {
                WCHAR szFolder[MAX_PATH];
                GetCurrentDirectoryW(ARRAYSIZE(szFolder), szFolder);
                hr = PathAppendW(szFolder, szSpec) ? S_OK : E_FAIL;
                if (SUCCEEDED(hr))
                {
                    hr = SHCreateItemFromParsingName(szFolder, NULL, riid, ppv);
                }
            }
        }
    }
    return hr;
}