// 
// initialization
//
STDMETHODIMP CSDShellExt::Initialize (LPCITEMIDLIST pidlFolder,	LPDATAOBJECT pDataObj, HKEY hProgID) {
    FORMATETC fmt = { CF_HDROP, NULL, DVASPECT_CONTENT,
                  -1, TYMED_HGLOBAL };
    STGMEDIUM stg = { TYMED_HGLOBAL };
    HDROP     hDrop;

    //
    // Look for CF_HDROP data in the data object. If there
    // is no such data, return an error back to Explorer.
    //
    if (FAILED(pDataObj->GetData(&fmt, &stg))) {
        return E_INVALIDARG;
    }

    //
    // check if extension is enabled
    //
    DWORD bufferSize = 4;
    DWORD keyType = REG_DWORD;
    SHGetValue(HKEY_CURRENT_USER, SecureDeleteKey, ShellNormalEnabled, &keyType, &normalEnabled, &bufferSize);
    SHGetValue(HKEY_CURRENT_USER, SecureDeleteKey, ShellMoveEnabled, &keyType, &moveEnabled, &bufferSize);
    SHGetValue(HKEY_CURRENT_USER, SecureDeleteKey, ShellRecycleEnabled, &keyType, &recycleEnabled, &bufferSize);

    if(!normalEnabled && !moveEnabled && !recycleEnabled) {
        // none of the features enabled
        return E_INVALIDARG;
    }

    //
    // reset data header
    //
    dataHeader.operationType = 0;
    dataHeader.objectCount = 0;

    //
    // get drop folder if drag-n-drop operation
    //
    if(pidlFolder != NULL && SHGetPathFromIDList(pidlFolder, dataHeader.data1)) {
        dataHeader.operationType = MOVE_OPERATION;
    }
 
    //
    // Get a pointer to the actual data.
    //
    hDrop = (HDROP)GlobalLock(stg.hGlobal);
    
    //
    // Make sure it worked.
    //
    if (hDrop == NULL) {
        return E_INVALIDARG;
    }

    //
    // get the files
    //
    unsigned int fileNumber = DragQueryFile (hDrop, 0xFFFFFFFF, NULL, 0);
    HRESULT hr = S_OK;

    if (fileNumber == 0) {
        GlobalUnlock (stg.hGlobal);
        ReleaseStgMedium (&stg);
        return E_INVALIDARG;
    }

    //
    // get the file names
    //
    wchar_t buffer[MAX_PATH];
    ClearFileList();

    for(unsigned int i = 0;i < fileNumber;i++) {
        if(DragQueryFile(hDrop, i, buffer, MAX_PATH) == 0) {
            //
            // error, abort
            //
            hr = E_INVALIDARG;
            break;
        }
            
        //
        // allocate string
        //
        int length = wcslen(buffer);
        wchar_t *name = new wchar_t[length + 1];
        wcscpy(name, buffer);

        //
        // insert into the list
        //
        fileList.insert(&name);
    }

    GlobalUnlock(stg.hGlobal);
    ReleaseStgMedium(&stg);
    return hr;
}