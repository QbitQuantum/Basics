HRESULT STDMETHODCALLTYPE CShellDispatch::BrowseForFolder(LONG Hwnd, BSTR Title, LONG Options, VARIANT RootFolder, Folder **ppsdf)
{
    TRACE("(%p, %lu, %ls, %lu, %s, %p)\n", this, Hwnd, Title, Options, debugstr_variant(&RootFolder), ppsdf);

    *ppsdf = NULL;

    if (!is_optional_argument(&RootFolder))
        FIXME("root folder is ignored\n");

    BROWSEINFOW bi = { 0 };
    bi.hwndOwner = reinterpret_cast<HWND>(LongToHandle(Hwnd));
    bi.lpszTitle = Title;
    bi.ulFlags = Options;

    CComHeapPtr<ITEMIDLIST> selection;
    selection.Attach(SHBrowseForFolderW(&bi));
    if (!selection)
        return S_FALSE;

    return ShellObjectCreatorInit<CFolder>(static_cast<LPITEMIDLIST>(selection), IID_PPV_ARG(Folder, ppsdf));
}