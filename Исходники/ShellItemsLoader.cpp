HRESULT ShellItemsLoader::EnumerateFolderItemsNonRecursive(IShellItem* currentBrowseLocation, ShellFileType fileType, std::vector<ComPtr<IShellItem> >& shellItems)
{
    std::vector<std::wstring> itemKinds;

    if ((fileType & FileTypeImage) == FileTypeImage)
    {
        itemKinds.push_back(L"picture");
    }

    if ((fileType & FileTypeImage) == FileTypeVideo)
    {
        itemKinds.push_back(L"video");
    }

    if ((fileType & FileTypeImage) == FileTypeAudio)
    {
        itemKinds.push_back(L"music");
    }

    // Enumerate all objects in the current search folder
    ComPtr<IShellFolder> searchFolder;
    HRESULT hr = currentBrowseLocation->BindToHandler(nullptr, BHID_SFObject, IID_PPV_ARGS(&searchFolder));
    if (SUCCEEDED(hr))
    {
        bool const isEnumFolders = (fileType & FileTypeFolder) == FileTypeFolder;
        SHCONTF const flags = isEnumFolders ? SHCONTF_FOLDERS : SHCONTF_NONFOLDERS;

        ComPtr<IEnumIDList> fileList;
        if (S_OK == searchFolder->EnumObjects(nullptr, flags, &fileList)) // EnumObjects has "empty success semantics", so it could also return S_FALSE. Thus, we only check for S_OK
        {
            ITEMID_CHILD* idList = nullptr;
            unsigned long fetched;
            while (S_OK == fileList->Next(1, &idList, &fetched))
            {
                ComPtr<IShellItem2> shellItem;
                hr = SHCreateItemWithParent(nullptr, searchFolder, idList, IID_PPV_ARGS(&shellItem));
                if (SUCCEEDED(hr))
                {
                    if (isEnumFolders)
                    {
                        shellItems.push_back(static_cast<IShellItem*>(shellItem));
                    }
                    else
                    {
                        // Check if we the item is correct
                        wchar_t *itemType = nullptr;
                        hr = shellItem->GetString(PKEY_Kind, &itemType);
                        if (SUCCEEDED(hr))
                        {
                            auto found = std::find(itemKinds.begin(), itemKinds.end(), itemType);
                            if (found != itemKinds.end())
                            {
                                shellItems.push_back(static_cast<IShellItem*>(shellItem));
                            }
                            ::CoTaskMemFree(itemType);
                        }
                    }
                }

                ILFree(idList);
            }
        }
    }
    return hr;
}