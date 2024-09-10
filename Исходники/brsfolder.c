/******************************************************************************
 * InitializeTreeView [Internal]
 *
 * Called from WM_INITDIALOG handler.
 *
 * PARAMS
 *  hwndParent [I] The BrowseForFolder dialog
 *  root       [I] ITEMIDLIST of the root shell folder
 */
static void InitializeTreeView( browse_info *info )
{
    LPITEMIDLIST pidlParent, pidlChild;
    HIMAGELIST hImageList;
    HRESULT hr;
    IShellFolder *lpsfParent, *lpsfRoot;
    IEnumIDList * pEnumChildren = NULL;
    HTREEITEM item;
    DWORD flags;
    LPCITEMIDLIST root = info->lpBrowseInfo->pidlRoot;

    TRACE("%p\n", info );

    Shell_GetImageLists(NULL, &hImageList);

    if (hImageList)
        SendMessageW( info->hwndTreeView, TVM_SETIMAGELIST, 0, (LPARAM)hImageList );

    /* We want to call InsertTreeViewItem down the code, in order to insert
     * the root item of the treeview. Due to InsertTreeViewItem's signature,
     * we need the following to do this:
     *
     * + An ITEMIDLIST corresponding to _the parent_ of root.
     * + An ITEMIDLIST, which is a relative path from root's parent to root
     *   (containing a single SHITEMID).
     * + An IShellFolder interface pointer of root's parent folder.
     *
     * If root is 'Desktop', then root's parent is also 'Desktop'.
     */

    pidlParent = ILClone(root);
    ILRemoveLastID(pidlParent);
    pidlChild = ILClone(ILFindLastID(root));

    if (_ILIsDesktop(pidlParent)) {
        hr = SHGetDesktopFolder(&lpsfParent);
    } else {
        IShellFolder *lpsfDesktop;
        hr = SHGetDesktopFolder(&lpsfDesktop);
        if (!SUCCEEDED(hr)) {
            WARN("SHGetDesktopFolder failed! hr = %08x\n", hr);
            return;
        }
        hr = IShellFolder_BindToObject(lpsfDesktop, pidlParent, 0, &IID_IShellFolder, (LPVOID*)&lpsfParent);
        IShellFolder_Release(lpsfDesktop);
    }

    if (!SUCCEEDED(hr)) {
        WARN("Could not bind to parent shell folder! hr = %08x\n", hr);
        return;
    }

    if (pidlChild && pidlChild->mkid.cb) {
        hr = IShellFolder_BindToObject(lpsfParent, pidlChild, 0, &IID_IShellFolder, (LPVOID*)&lpsfRoot);
    } else {
        lpsfRoot = lpsfParent;
        hr = IShellFolder_AddRef(lpsfParent);
    }

    if (!SUCCEEDED(hr)) {
        WARN("Could not bind to root shell folder! hr = %08x\n", hr);
        IShellFolder_Release(lpsfParent);
        return;
    }

    flags = BrowseFlagsToSHCONTF( info->lpBrowseInfo->ulFlags );
    hr = IShellFolder_EnumObjects( lpsfRoot, info->hWnd, flags, &pEnumChildren );
    if (!SUCCEEDED(hr)) {
        WARN("Could not get child iterator! hr = %08x\n", hr);
        IShellFolder_Release(lpsfParent);
        IShellFolder_Release(lpsfRoot);
        return;
    }

    SendMessageW( info->hwndTreeView, TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT );
    item = InsertTreeViewItem( info, lpsfParent, pidlChild,
                               pidlParent, pEnumChildren, TVI_ROOT );
    SendMessageW( info->hwndTreeView, TVM_EXPAND, TVE_EXPAND, (LPARAM)item );

    IShellFolder_Release(lpsfRoot);
    IShellFolder_Release(lpsfParent);
}