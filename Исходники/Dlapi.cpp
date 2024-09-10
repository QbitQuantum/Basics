//  Snapshots a directory and displays the items in the listview control
int DirList_Fill(HWND hwnd, const WCHAR* lpszDir, DWORD grfFlags, const WCHAR* lpszFileSpec,
                 BOOL bExcludeFilter, BOOL bNoFadeHidden, int iSortFlags, BOOL fSortRev) {

    WCHAR wszDir[MAX_PATH];

    LPSHELLFOLDER lpsfDesktop = NULL;
    LPSHELLFOLDER lpsf = NULL;

    LPITEMIDLIST pidl = NULL;
    LPITEMIDLIST pidlEntry = NULL;

    LPENUMIDLIST lpe = NULL;

    LV_ITEM lvi;
    LPLV_ITEMDATA lplvid;

    ULONG chParsed = 0;
    ULONG dwAttributes = 0;

    DL_FILTER dlf;
    SHFILEINFO shfi = { 0 };

    DLDATA* lpdl = (DLDATA*)GetProp(hwnd, pDirListProp);

    // Initialize default icons
    SHGetFileInfo(L"Icon", FILE_ATTRIBUTE_DIRECTORY, &shfi, sizeof(SHFILEINFO),
                  SHGFI_USEFILEATTRIBUTES | SHGFI_SMALLICON | SHGFI_SYSICONINDEX);
    lpdl->iDefIconFolder = shfi.iIcon;

    SHGetFileInfo(L"Icon", FILE_ATTRIBUTE_NORMAL, &shfi, sizeof(SHFILEINFO),
                  SHGFI_USEFILEATTRIBUTES | SHGFI_SMALLICON | SHGFI_SYSICONINDEX);
    lpdl->iDefIconFile = shfi.iIcon;

    // First of all terminate running icon thread
    DirList_TerminateIconThread(hwnd);

    // A Directory is strongly required
    if (!lpszDir || !*lpszDir)
        return (-1);

    lstrcpy(lpdl->szPath, lpszDir);

    // Init ListView
    SendMessage(hwnd, WM_SETREDRAW, 0, 0);
    ListView_DeleteAllItems(hwnd);

    // Init Filter
    DirList_CreateFilter(&dlf, lpszFileSpec, bExcludeFilter);

    // Init lvi
    lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
    lvi.iItem = 0;
    lvi.iSubItem = 0;
    lvi.pszText = LPSTR_TEXTCALLBACK;
    lvi.cchTextMax = MAX_PATH;
    lvi.iImage = I_IMAGECALLBACK;

    // Convert Directory to a UNICODE string
    /*MultiByteToWideChar(CP_ACP,
                        MB_PRECOMPOSED,
                        lpszDir,
                        -1,
                        wszDir,
                        MAX_PATH);*/
    lstrcpy(wszDir, lpszDir);

    // Get Desktop Folder
    if (NOERROR == SHGetDesktopFolder(&lpsfDesktop)) {

        // Convert wszDir into a pidl
        if (NOERROR ==
            lpsfDesktop->ParseDisplayName(hwnd, NULL, wszDir, &chParsed, &pidl, &dwAttributes)) {

            // Bind pidl to IShellFolder
            if (NOERROR == lpsfDesktop->BindToObject(pidl, NULL, IID_IShellFolder, (void**)&lpsf)) {

                // Create an Enumeration object for lpsf
                if (NOERROR == lpsf->EnumObjects(hwnd, grfFlags, &lpe)) {

                    // Enumerate the contents of lpsf
                    while (NOERROR == lpe->Next(1, &pidlEntry, NULL)) {

                        // Add found item to the List
                        // Check if it's part of the Filesystem
                        dwAttributes = SFGAO_FILESYSTEM | SFGAO_FOLDER;

                        lpsf->GetAttributesOf(1, (LPCITEMIDLIST*)pidlEntry, &dwAttributes);

                        if (dwAttributes & SFGAO_FILESYSTEM) {

                            // Check if item matches specified filter
                            if (DirList_MatchFilter(lpsf, pidlEntry, &dlf)) {

                                lplvid = (LV_ITEMDATA*)CoTaskMemAlloc(sizeof(LV_ITEMDATA));

                                lplvid->pidl = pidlEntry;
                                lplvid->lpsf = lpsf;

                                lpsf->AddRef();

                                lvi.lParam = (LPARAM)lplvid;

                                // Setup default Icon - Folder or File
                                lvi.iImage = (dwAttributes & SFGAO_FOLDER) ? lpdl->iDefIconFolder
                                                                           : lpdl->iDefIconFile;

                                ListView_InsertItem(hwnd, &lvi);

                                lvi.iItem++;
                            }
                        }

                    } // IEnumIDList::Next()

                    lpe->Release();

                } // IShellFolder::EnumObjects()

            } // IShellFolder::BindToObject()

        } // IShellFolder::ParseDisplayName()

        lpsfDesktop->Release();

    } // SHGetDesktopFolder()

    if (lpdl->pidl)
        CoTaskMemFree(lpdl->pidl);

    if (lpdl->lpsf)
        lpdl->lpsf->Release();

    // Set lpdl
    lpdl->cbidl = IL_GetSize(pidl);
    lpdl->pidl = pidl;
    lpdl->lpsf = lpsf;
    lpdl->bNoFadeHidden = bNoFadeHidden;

    // Set column width to fit window
    ListView_SetColumnWidth(hwnd, 0, LVSCW_AUTOSIZE_USEHEADER);

    // Sort before display is updated
    DirList_Sort(hwnd, iSortFlags, fSortRev);

    // Redraw Listview
    SendMessage(hwnd, WM_SETREDRAW, 1, 0);

    // Return number of items in the control
    return (ListView_GetItemCount(hwnd));
}