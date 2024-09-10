BOOL CMyTreeView::GetChildItems(HTREEITEM hParentItem)
{
    TVITEM tvItem = {0};
    tvItem.mask = TVIF_PARAM;
    tvItem.hItem = hParentItem;

    if (!GetItem(tvItem))
        return FALSE;

    //change the cursor
    HCURSOR hCursor = ::SetCursor(LoadCursor(NULL, IDC_WAIT));
    //turn redawing off in the TreeView. This will speed things up as we add items
    SendMessage(WM_SETREDRAW, FALSE, 0);
    TreeItemData* pItem = (TreeItemData*)tvItem.lParam;
    CShellFolder cParentFolder;
    HRESULT        hr;

    //if the parent folder is NULL, then we are at the root of the namespace, so the parent of this item is the desktop folder
    if (!pItem->GetParentFolder().GetIShellFolder())
        hr = cParentFolder.SHGetDesktopFolder();
    //otherwise we need to get the IShellFolder for this item
    else
        hr = pItem->GetParentFolder().BindToObject(pItem->GetRelCpidl(), NULL, IID_IShellFolder, cParentFolder);

    if (FAILED(hr))
        return FALSE;

    EnumObjects(hParentItem, cParentFolder, pItem->GetFullCpidl());
    //sort the new items
    TV_SORTCB tvSort;
    tvSort.hParent = hParentItem;
    tvSort.lpfnCompare = CompareProc;
    tvSort.lParam = 0;
    SortChildrenCB(tvSort, 0);
    //turn redawing back on in the TreeView
    SendMessage(WM_SETREDRAW, TRUE, 0);
    UpdateWindow();
    ::SetCursor(hCursor);
    return TRUE;
}