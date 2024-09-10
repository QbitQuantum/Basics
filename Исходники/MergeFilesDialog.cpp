INT_PTR CMergeFilesDialog::OnInitDialog()
{
    m_hDialogIcon = LoadIcon(GetModuleHandle(0),MAKEINTRESOURCE(IDI_MAIN_SMALL));
    SetClassLongPtr(m_hDlg,GCLP_HICONSM,reinterpret_cast<LONG_PTR>(m_hDialogIcon));

    std::wregex rxPattern;
    bool bAllMatchPattern = true;

    rxPattern.assign(_T(".*[\\.]?part[0-9]+"),std::regex_constants::icase);

    /* If the files all match the pattern .*[\\.]?part[0-9]+
    (e.g. document.txt.part1), order them alphabetically. */
    for each(auto strFullFilename in m_FullFilenameList)
    {
        if(!std::tr1::regex_match(strFullFilename,rxPattern))
        {
            bAllMatchPattern = false;
            break;
        }
    }

    std::wstring strOutputFilename;

    if(bAllMatchPattern)
    {
        m_FullFilenameList.sort(CompareFilenames);

        /* Since the filenames all match the
        pattern, construct the output filename
        from the first files name. */
        rxPattern.assign(_T("[\\.]?part[0-9]+"),std::regex_constants::icase);
        strOutputFilename = std::tr1::regex_replace(m_FullFilenameList.front(),
                            rxPattern,std::wstring(_T("")));
    }
    else
    {
        /* TODO: Improve output name. */
        strOutputFilename = _T("output");
    }

    TCHAR szOutputFile[MAX_PATH];
    PathCombine(szOutputFile,m_strOutputDirectory.c_str(),strOutputFilename.c_str());
    SetDlgItemText(m_hDlg,IDC_MERGE_EDIT_FILENAME,szOutputFile);

    HWND hListView = GetDlgItem(m_hDlg,IDC_MERGE_LISTVIEW);

    HIMAGELIST himlSmall;
    Shell_GetImageLists(NULL,&himlSmall);
    ListView_SetImageList(hListView,himlSmall,LVSIL_SMALL);

    SetWindowTheme(hListView,L"Explorer",NULL);

    ListView_SetExtendedListViewStyleEx(hListView,
                                        LVS_EX_DOUBLEBUFFER|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES,
                                        LVS_EX_DOUBLEBUFFER|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

    LVCOLUMN lvColumn;
    TCHAR szTemp[32];

    LoadString(GetInstance(),IDS_MERGE_FILES_COLUMN_FILE,
               szTemp,SIZEOF_ARRAY(szTemp));
    lvColumn.mask		= LVCF_TEXT;
    lvColumn.pszText	= szTemp;
    ListView_InsertColumn(hListView,0,&lvColumn);

    LoadString(GetInstance(),IDS_MERGE_FILES_COLUMN_TYPE,
               szTemp,SIZEOF_ARRAY(szTemp));
    lvColumn.mask		= LVCF_TEXT;
    lvColumn.pszText	= szTemp;
    ListView_InsertColumn(hListView,1,&lvColumn);

    LoadString(GetInstance(),IDS_MERGE_FILES_COLUMN_SIZE,
               szTemp,SIZEOF_ARRAY(szTemp));
    lvColumn.mask		= LVCF_TEXT;
    lvColumn.pszText	= szTemp;
    ListView_InsertColumn(hListView,2,&lvColumn);

    LoadString(GetInstance(),IDS_MERGE_FILES_COLUMN_DATE_MODIFIED,
               szTemp,SIZEOF_ARRAY(szTemp));
    lvColumn.mask		= LVCF_TEXT;
    lvColumn.pszText	= szTemp;
    ListView_InsertColumn(hListView,3,&lvColumn);

    int iItem = 0;

    for each(auto strFullFilename in m_FullFilenameList)
    {
        TCHAR szFullFilename[MAX_PATH];

        StringCchCopy(szFullFilename,SIZEOF_ARRAY(szFullFilename),
                      strFullFilename.c_str());

        /* TODO: Perform in background thread. */
        SHFILEINFO shfi;
        SHGetFileInfo(szFullFilename,0,&shfi,sizeof(SHFILEINFO),
                      SHGFI_SYSICONINDEX|SHGFI_TYPENAME);

        LVITEM lvItem;
        lvItem.mask		= LVIF_TEXT|LVIF_IMAGE;
        lvItem.iItem	= iItem;
        lvItem.iSubItem	= 0;
        lvItem.pszText	= szFullFilename;
        lvItem.iImage	= shfi.iIcon;
        ListView_InsertItem(hListView,&lvItem);

        ListView_SetItemText(hListView,iItem,1,shfi.szTypeName);

        WIN32_FILE_ATTRIBUTE_DATA wfad;
        GetFileAttributesEx(szFullFilename,GetFileExInfoStandard,&wfad);

        TCHAR szFileSize[32];
        ULARGE_INTEGER lFileSize = {wfad.nFileSizeLow,wfad.nFileSizeHigh};
        FormatSizeString(lFileSize,szFileSize,SIZEOF_ARRAY(szFileSize));
        ListView_SetItemText(hListView,iItem,2,szFileSize);

        TCHAR szDateModified[32];
        CreateFileTimeString(&wfad.ftLastWriteTime,szDateModified,
                             SIZEOF_ARRAY(szDateModified),m_bShowFriendlyDates);
        ListView_SetItemText(hListView,iItem,3,szDateModified);

        iItem++;
    }