bool PromptFileLocation(std::wstring& resultPath, std::wstring title=L"Open", fileType filterType=ft_exe)
{
    HRESULT hr;
    
    hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (!SUCCEEDED(hr))
    {
        CoUninitialize();
        return false;
    }

    IFileOpenDialog *pFileOpen;
    // Create the FileOpenDialog object.
    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
    if (!SUCCEEDED(hr))
    {
        pFileOpen->Release();
        CoUninitialize();
        return false;
    }

    // Set the filter type
    switch (filterType)
    {
    case ft_exe:
            {
                COMDLG_FILTERSPEC filter;
                filter.pszName = L"Windows Executable";
                filter.pszSpec = L"*.exe";
                hr = pFileOpen->SetFileTypes(1, &filter);
                break;
            }
    default:
        {
            break;
        }
    }
    if (!SUCCEEDED(hr))
    {
        pFileOpen->Release();
        CoUninitialize();
        return false;
    }

    // Set the title
    hr = pFileOpen->SetTitle(L"Please locate your Blender executable.");
    if (!SUCCEEDED(hr))
    {
        pFileOpen->Release();
        CoUninitialize();
        return false;
    }

    // Show the Open dialog box.
    hr = pFileOpen->Show(NULL);
    if (!SUCCEEDED(hr))
    {
        pFileOpen->Release();
        CoUninitialize();
        return false;
    }

    // Get the file name from the open dialog box.
    IShellItem *pItem;
    hr = pFileOpen->GetResult(&pItem);
    if (!SUCCEEDED(hr))
    {
        pItem->Release();
        pFileOpen->Release();
        CoUninitialize();
        return false;
    }

    PWSTR pszFilePath;
    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

    if (!SUCCEEDED(hr))
    {
        pItem->Release();
        pFileOpen->Release();
        CoUninitialize();
        CoTaskMemFree(pszFilePath);
        return false;
    }

    resultPath = pszFilePath;
    CoTaskMemFree(pszFilePath);
    pItem->Release();
    pFileOpen->Release();
    CoUninitialize();
    return true;
}