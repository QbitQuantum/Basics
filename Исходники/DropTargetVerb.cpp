HRESULT CreateShellItemFromHIDA(CIDA *pida, UINT iItem, IShellItem **ppsi)
{
    *ppsi = NULL;

    HRESULT hr = E_FAIL;
    if (iItem < pida->cidl)
    {
        PIDLIST_ABSOLUTE pidlFolder; // needed for alignment
        hr = SHILCloneFull(IDA_GetFolderIDList(pida), &pidlFolder);
        if (SUCCEEDED(hr))
        {
            PIDLIST_ABSOLUTE pidl;
            hr = SHILCombine(pidlFolder, IDA_GetItemIDList(pida, iItem), &pidl);
            if (SUCCEEDED(hr))
            {
                // cast needed due to overload of the type of the 3rd param, when the first
                // 2 params are NULL this is an absolute IDList
                hr = SHCreateShellItem(NULL, NULL, reinterpret_cast<PCUITEMID_CHILD>(pidl), ppsi);
                CoTaskMemFree(pidl);
            }
            CoTaskMemFree(pidlFolder);
        }
    }
    return hr;
}