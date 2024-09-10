    // Loads the IShellLibrary interface for the specified item, calls the derived class to perform an operation on
    // the library, and commits/saves any changes as needed.
    HRESULT v_ExecuteCommand()
    {
        HRESULT hr;
        if (_fCreate)
        {
            // If we're in 'create' mode, instantiate a new IShellLibrary in memory.
            hr = SHCreateLibrary(IID_PPV_ARGS(&_plib));
        }
        else
        {
            // Otherwise, load it from the specified IShellItem.
            const DWORD grfMode = _fReadOnly ? (STGM_READ | STGM_SHARE_DENY_WRITE) : (STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
            hr = SHLoadLibraryFromItem(_psiLibrary, grfMode, IID_PPV_ARGS(&_plib));
        }

        if (SUCCEEDED(hr))
        {
            // Call the derived class to execute the operation on the library.
            hr = v_ExecuteLibCommand();
            if (SUCCEEDED(hr) && !_fReadOnly)
            {
                if (_fCreate)
                {
                    // We created a new library in memory; now save it to disk.
                    // The IShellLibrary::Save API takes the destination in the form of the parent folder, and the name
                    // of the library (without any file extension).  However, the argument is in the form of a full file
                    // system path, possibly including the extension.  So, we need to parse it into that form.  For example:
                    //   "C:\some\folder\stuff.library-ms" => "C:\some\folder", "stuff"
                    PWSTR pszName = PathFindFileNameW(_pszSavePath);
                    if (StrCmpICW(PathFindExtensionW(pszName), L".library-ms") == 0)
                    {
                        PathRemoveExtensionW(pszName);
                    }
                    PathRemoveFileSpec(_pszSavePath);

                    // Save the library with the specified name in the specified folder.
                    PWSTR pszSavedToPath;
                    hr = SHSaveLibraryInFolderPath(_plib, _pszSavePath, pszName, _lsfSaveOptions, &pszSavedToPath);
                    if (SUCCEEDED(hr))
                    {
                        // The API returns the full file system path that the library was saved to.
                        // (This may or may not match the original argument, depending on whether LSF_MAKEUNIQUENAME was specified.)
                        Output(L"Library saved to path: %s\n", pszSavedToPath);
                        CoTaskMemFree(pszSavedToPath);
                    }
                    else
                    {
                        RuntimeError(L"Error %#08x saving library to path: %s\\%s.library-ms\n", hr, _pszSavePath, pszName);
                    }
                }
                else
                {
                    // We're operating on an existing library; commit the changes to disk.
                    hr = _plib->Commit();
                    if (SUCCEEDED(hr))
                    {
                        Output(L"Changes successfully committed.\n");
                    }
                }
            }
        }
        else
        {
            RuntimeError(L"Error %#08x loading library from path: %s\n", hr, _pszSavePath);
        }
        return hr;
    }