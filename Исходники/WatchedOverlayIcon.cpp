// IShellExtInit::Initialize
// Initializes context menu for a file.
STDMETHODIMP
CWatchedOverlayIcon::Initialize(
    LPCITEMIDLIST pidlFolder,
    LPDATAOBJECT ptDataObject,
    HKEY hProgID
)
{
    try
    {
        // Validate arguments
        if (nullptr == ptDataObject)
        {
            return E_INVALIDARG;
        }

        FORMATETC tFormat = { CF_HDROP, nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
        STGMEDIUM tStg = { TYMED_HGLOBAL };

        // Look for CF_HDROP data in the data object. If there
        // is no such data, return an error back to Explorer.
        if (FAILED(ptDataObject->GetData(&tFormat, &tStg)))
        {
            return E_INVALIDARG;
        }

        AutoReleaseStg ptStg(&tStg, ReleaseStgMedium);
        
        // Get a pointer to the actual data.
        AutoGlobalUnlock phDrop((HDROP) GlobalLock(tStg.hGlobal), GlobalUnlock);
        if (nullptr == phDrop)
        {
            return E_INVALIDARG;
        }

        // Find count of selected files
        UINT nFiles = DragQueryFileW(phDrop.get(), 0xFFFFFFFF, nullptr, 0);
        if (0 == nFiles)
        {
            return E_INVALIDARG;
        }

        _tSelectedFiles.clear();

        // Add selected files to the list
        WCHAR wszFileName[MAX_PATH] = {0};
        for (UINT nFile = 0; nFile < nFiles; nFile++)
        {
            if (0 == DragQueryFileW(phDrop.get(), nFile, wszFileName, MAX_PATH))
            {
                return E_INVALIDARG;
            }

            _tSelectedFiles.push_back(std::wstring(wszFileName));
        }

        return S_OK;
    }
    catch (...)
    {
        return E_FAIL;
    }
}