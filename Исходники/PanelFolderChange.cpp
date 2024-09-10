void CPanel::OpenParentFolder()
{
    printf("CPanel::OpenParentFolder\n");
    LoadFullPath(); // Maybe we don't need it ??
    UString focucedName;
    if (!_currentFolderPrefix.IsEmpty())
    {
        UString string = _currentFolderPrefix;
        string.Delete(string.Length() - 1);
        int pos = string.ReverseFind(WCHAR_PATH_SEPARATOR);
        if (pos < 0)
            pos = 0;
        else
            pos++;
        focucedName = string.Mid(pos);
    }

    printf("CPanel::OpenParentFolder focucedName=%ls\n",(const wchar_t *)focucedName);

    CDisableTimerProcessing disableTimerProcessing1(*this);
    CMyComPtr<IFolderFolder> newFolder;
    _folder->BindToParentFolder(&newFolder);
    if (newFolder)
        _folder = newFolder;
    else
    {
        if (_parentFolders.IsEmpty())
        {
            SetToRootFolder();
            if (focucedName.IsEmpty())
                focucedName = GetItemName(0);
        }
        else
        {
            _folder.Release();
            _library.Free();
            CFolderLink &link = _parentFolders.Back();
            _folder = link.ParentFolder;
            _library.Attach(link.Library.Detach());
            focucedName = link.ItemName;
            if (_parentFolders.Size () > 1)
                OpenParentArchiveFolder();
            _parentFolders.DeleteBack();
        }
    }

    UStringVector selectedItems;
    /*
    if (!focucedName.IsEmpty())
      selectedItems.Add(focucedName);
    */
    LoadFullPath();
    // ::SetCurrentDirectory(::_currentFolderPrefix);
    RefreshListCtrl(focucedName, -1, true, selectedItems);
    _listView.EnsureVisible(_listView.GetFocusedItem(), false);
    RefreshStatusBar();

    printf("CPanel::OpenParentFolder-end\n");
}