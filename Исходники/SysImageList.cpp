CSysImageList::CSysImageList()
{
    SHFILEINFO ssfi;
    TCHAR windir[MAX_PATH] = { 0 };
    GetWindowsDirectory(windir, _countof(windir));  // MAX_PATH ok.
    hSystemImageList =
        (HIMAGELIST)SHGetFileInfo(windir,
                                  0,
                                  &ssfi, sizeof ssfi,
                                  SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

    int cx, cy;
    ImageList_GetIconSize(hSystemImageList, &cx, &cy);
    auto emptyImageList = ImageList_Create(cx, cy, ILC_COLOR32 | ILC_MASK, ImageList_GetImageCount(hSystemImageList), 10);
    Attach(emptyImageList);

    m_dirIconIndex = GetFileIcon(L"Doesn't matter", FILE_ATTRIBUTE_DIRECTORY, 0);
    m_dirOpenIconIndex = GetFileIcon(L"Doesn't matter", FILE_ATTRIBUTE_DIRECTORY, SHGFI_OPENICON);
    m_defaultIconIndex = GetFileIcon(L"", FILE_ATTRIBUTE_NORMAL, 0);
}