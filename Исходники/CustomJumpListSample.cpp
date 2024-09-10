// Creates a set of sample files in the current user's Documents directory to use as items in the
// custom category inserted into the Jump List.
HRESULT CreateSampleFiles()
{
    PWSTR pszPathDocuments;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_CREATE, NULL, &pszPathDocuments);
    if (SUCCEEDED(hr))
    {
        for (UINT i = 0; SUCCEEDED(hr) && i < ARRAYSIZE(c_rgpszFiles); i++)
        {
            WCHAR szPathSample[MAX_PATH];
            hr = PathCombine(szPathSample, pszPathDocuments, c_rgpszFiles[i]) ? S_OK : E_FAIL;
            if (SUCCEEDED(hr))
            {
                IStream *pstm;
                hr = SHCreateStreamOnFileEx(szPathSample, (STGM_WRITE | STGM_FAILIFTHERE), FILE_ATTRIBUTE_NORMAL, TRUE, NULL, &pstm);
                if (SUCCEEDED(hr))
                {
                    PCWSTR pszText = L"This is a sample file for the CustomJumpListSample.\r\n";
                    ULONG cb = (sizeof(pszText[0]) * (lstrlen(pszText) + 1));
                    hr = IStream_Write(pstm, pszText, cb);
                    pstm->Release();
                }
                else if (HRESULT_FROM_WIN32(ERROR_FILE_EXISTS) == hr)
                {
                    // If the file exists, we're ok, we'll just reuse it
                    hr = S_OK;
                }
            }
        }
        CoTaskMemFree(pszPathDocuments);
    }
    return hr;
}