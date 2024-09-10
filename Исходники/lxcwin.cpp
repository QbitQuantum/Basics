extern "C" LXCWIN_API HRESULT fileOpenDialog(HWND hWnd, DWORD *count, LPWSTR **result) {
    *result = NULL;
    HRESULT hr = S_OK;
    CoInitialize(nullptr);
    IFileOpenDialog *pfd = NULL;
    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
    if (SUCCEEDED(hr)) {
        // set default folder to "My Documents"
        IShellItem *psiDocuments = NULL;
        hr = SHCreateItemInKnownFolder(FOLDERID_Documents, 0, NULL,
                                       IID_PPV_ARGS(&psiDocuments));
        if (SUCCEEDED(hr)) {
            hr = pfd->SetDefaultFolder(psiDocuments);
            psiDocuments->Release();
        }

        // dialog title
        pfd->SetTitle(L"Select files to share");

        // allow multiselect, restrict to real files
        DWORD dwOptions;
        hr = pfd->GetOptions(&dwOptions);
        if (SUCCEEDED(hr)) {
            // ideally, allow selecting folders as well as files, but IFileDialog does not support this :(
            pfd->SetOptions(dwOptions | FOS_ALLOWMULTISELECT | FOS_FORCEFILESYSTEM); // | FOS_PICKFOLDERS
        }

        // do not limit to certain file types

        // show the open file dialog
        hr = pfd->Show(hWnd);
        if (SUCCEEDED(hr)) {
            IShellItemArray *psiaResults;
            hr = pfd->GetResults(&psiaResults);
            if (SUCCEEDED(hr)) {
                hr = psiaResults->GetCount(count);
                if (SUCCEEDED(hr)) {
                    *result = (LPWSTR*)calloc(*count, sizeof(LPWSTR));
                    if (*result != NULL) {
                        for (DWORD i = 0; i < *count; i++) {
                            IShellItem *resultItem = NULL;
                            hr = psiaResults->GetItemAt(i, &resultItem);
                            if (SUCCEEDED(hr)) {
                                resultItem->GetDisplayName(SIGDN_FILESYSPATH, &((*result)[i]));
                                resultItem->Release();
                            }
                        }
                        // paths now contains selected files
                    }
                }
                psiaResults->Release();
            }
        }
        pfd->Release();
    }
    return hr;
}