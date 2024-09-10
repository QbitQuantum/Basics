BOOL CCalendarSettings::OnInitDialog(){
    CString s1;
    s1.LoadString(IDS_CALENDAR_DETAILS); SetWindowText(s1);
    CDialog::OnInitDialog();

    WindowsSyncSourceConfig* ssconf = ((OutlookConfig*)getConfig())->getSyncSourceConfig(APPOINTMENT_);
    
    editFolder.SetLimitText(EDIT_TEXT_MAXLENGTH);
    editRemote.SetLimitText(EDIT_TEXT_MAXLENGTH);
    
    // Load the syncmodes in the editbox/dropdown
    loadSyncModesBox(APPOINTMENT_);

    // load string resources
    s1.LoadString(IDS_SYNC_DIRECTION);      SetDlgItemText(IDC_CALENDAR_GROUP_DIRECTION, s1);
    s1.LoadString(IDS_CURRENT);             SetDlgItemText(IDC_CALENDAR_STATIC_FOLDER, s1);
    s1.LoadString(IDS_INCLUDE_SUBFOLDERS);  SetDlgItemText(IDC_CALENDAR_CHECK_INCLUDE, s1);
    s1.LoadString(IDS_SELECT_FOLDER);       SetDlgItemText(IDC_CALENDAR_BUT_SELECT, s1);
    s1.LoadString(IDS_REMOTE_NAME);         SetDlgItemText(IDC_CALENDAR_STATIC_REMOTE, s1);
    s1.LoadString(IDS_ADVANCED);            SetDlgItemText(IDC_CALENDAR_GROUP_ADVANCED, s1);
    s1.LoadString(IDS_CALENDAR_FOLDER);     SetDlgItemText(IDC_CALENDAR_GROUP_FOLDER, s1);
    s1.LoadString(IDS_EVENT_FILTER);        SetDlgItemText(IDC_CALENDAR_GROUP_FILTER, s1);
    s1.LoadString(IDS_SYNC_PAST_EVENTS);    SetDlgItemText(IDC_CALENDAR_STATIC_FILTER, s1);
    s1.LoadString(IDS_OK);                  SetDlgItemText(IDC_CALENDAR_BUTOK, s1);
    s1.LoadString(IDS_CANCEL);              SetDlgItemText(IDC_CALENDAR_BUTCANCEL, s1);
    s1.LoadString(IDS_DATA_FORMAT);         SetDlgItemText(IDC_CALENDAR_STATIC_DATAFORMAT, s1);
    s1.LoadString(IDS_USE_VCAL);            SetDlgItemText(IDC_CALENDAR_DATA_FORMAT, s1);
    s1.LoadString(IDS_SHARED);              SetDlgItemText(IDC_CALENDAR_CHECK_SHARED, s1);

    s1.LoadString(IDS_DATE_FILTER_NONE);            lstFilter.AddString(s1);
    s1.LoadString(IDS_DATE_FILTER_LAST_WEEK);       lstFilter.AddString(s1);
    s1.LoadString(IDS_DATE_FILTER_LAST_2_WEEKS);    lstFilter.AddString(s1);
    s1.LoadString(IDS_DATE_FILTER_LAST_MONTH);      lstFilter.AddString(s1);
    s1.LoadString(IDS_DATE_FILTER_LAST_3_MONTHS);   lstFilter.AddString(s1);
    s1.LoadString(IDS_DATE_FILTER_LAST_6_MONTHS);   lstFilter.AddString(s1);
    s1.LoadString(IDS_DATE_FILTER_ALL);             lstFilter.AddString(s1);

    // Set dropdown-lists initial position
    lstSyncType.SetCurSel(getSyncTypeIndex(ssconf->getSync()));
    lstFilter.SetCurSel(getDateFilterIndex(ssconf->getDateFilter().getRelativeLowerDate()));

    
    // Get folder path.
    // Note: use 'toWideChar' because we need UTF-8 conversion.
    WCHAR* olFolder = toWideChar(ssconf->getFolderPath());
    s1 = olFolder;
    delete [] olFolder;

    try {
        if(s1 == ""){
            s1 = getDefaultFolderPath(APPOINTMENT).data();
        }
    }
    catch (...){
        // an exception occured while trying to get the default folder
        EndDialog(-1);
    }

    SetDlgItemText(IDC_CALENDAR_EDIT_FOLDER, s1);

    if(ssconf->getUseSubfolders()) {
        checkInclude.SetCheck(BST_CHECKED);
    }

    // Note: use 'toWideChar' because we need UTF-8 conversion.
    WCHAR* remName = toWideChar(ssconf->getURI());
    s1 = remName;
    delete [] remName;
    SetDlgItemText(IDC_CALENDAR_EDIT_REMOTE, s1);

    if (s1.Right(wcslen(SHARED_SUFFIX)).Compare(SHARED_SUFFIX) == 0) {
        checkShared.SetCheck(BST_CHECKED);
    }


    // Apply customizations
    bool shared             = UICustomization::shared;
    bool lockFilter         = UICustomization::lockCalendarFilter;
    bool forceUseSubfolders = UICustomization::forceUseSubfolders;
    bool hideDataFormats    = UICustomization::hideDataFormats;
    bool hideAllAdvanced    = !SHOW_ADVANCED_SETTINGS;

    if (lockFilter) {
        int lockFilterIndex = UICustomization::lockCalendarFilterValue;
        CComboBox * item = (CComboBox*)GetDlgItem(IDC_CALENDAR_COMBO_FILTER);
        item->EnableWindow(false);
        item->SetCurSel(lockFilterIndex);
    }

    if (forceUseSubfolders) {
        checkInclude.SetCheck(BST_CHECKED);
        checkInclude.ShowWindow(SW_HIDE);

        // Resize things
        CRect rect;
        checkInclude.GetClientRect(&rect);
        int dy = -1 * (rect.Height() + 5);

        resizeItem(GetDlgItem(IDC_CALENDAR_GROUP_FOLDER), 0, dy);

        moveItem(this, &groupAdvanced, 0, dy);
        moveItem(this, &editRemote,    0, dy);
        moveItem(this, &checkShared,   0, dy);
        moveItem(this, GetDlgItem(IDC_CALENDAR_DATA_FORMAT),       0, dy);
        moveItem(this, GetDlgItem(IDC_CALENDAR_GROUP_FILTER),      0, dy);
        moveItem(this, GetDlgItem(IDC_CALENDAR_STATIC_FILTER),     0, dy);
        moveItem(this, GetDlgItem(IDC_CALENDAR_COMBO_FILTER),      0, dy);
        moveItem(this, GetDlgItem(IDC_CALENDAR_STATIC_REMOTE),     0, dy);
        moveItem(this, GetDlgItem(IDC_CALENDAR_STATIC_DATAFORMAT), 0, dy);
        moveItem(this, GetDlgItem(IDC_CALENDAR_BUTOK),             0, dy);
        moveItem(this, GetDlgItem(IDC_CALENDAR_BUTCANCEL),         0, dy);

        setWindowHeight(this, GetDlgItem(IDC_CALENDAR_BUTOK));
    }

    if (hideAllAdvanced) {
        groupAdvanced.ShowWindow(SW_HIDE);
        editRemote.ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CALENDAR_STATIC_REMOTE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CALENDAR_STATIC_DATAFORMAT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CALENDAR_DATA_FORMAT)->ShowWindow(SW_HIDE);

        CRect rect;
        groupAdvanced.GetClientRect(&rect);
        int dy = -1 * (rect.Height() + 10);

        moveItem(this, GetDlgItem(IDC_CALENDAR_BUTOK),     0, dy);
        moveItem(this, GetDlgItem(IDC_CALENDAR_BUTCANCEL), 0, dy);

        setWindowHeight(this, GetDlgItem(IDC_CALENDAR_BUTOK));
    } 
    else if (hideDataFormats) {
        GetDlgItem(IDC_CALENDAR_STATIC_DATAFORMAT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CALENDAR_DATA_FORMAT)->ShowWindow(SW_HIDE);

        // Resize things
        CRect rect;
        GetDlgItem(IDC_CALENDAR_STATIC_DATAFORMAT)->GetClientRect(&rect);
        int dy = -1 * (rect.Height() + 5);

        resizeItem(&groupAdvanced, 0, dy);

        moveItem(this, GetDlgItem(IDC_CALENDAR_BUTOK),     0, dy);
        moveItem(this, GetDlgItem(IDC_CALENDAR_BUTCANCEL), 0, dy);

        setWindowHeight(this, GetDlgItem(IDC_CALENDAR_BUTOK));
    }

    // Shared folders
    if (shared) {
        editRemote.EnableWindow(false);
    } else {
        GetDlgItem(IDC_CALENDAR_CHECK_SHARED)->ShowWindow(SW_HIDE);
    } 


    // disable windows xp theme, otherwise any color setting for groupbox
    // will be overriden by the theme settings
    if(((COutlookPluginApp*)AfxGetApp())->hLib){
        PFNSETWINDOWTHEME pfnSetWindowTheme =
            (PFNSETWINDOWTHEME)GetProcAddress(((COutlookPluginApp*)AfxGetApp())->hLib, "SetWindowTheme");
        pfnSetWindowTheme (groupDirection.m_hWnd,L" ",L" ");
        pfnSetWindowTheme (groupFolder.m_hWnd,L" ",L" ");
        pfnSetWindowTheme (groupAdvanced.m_hWnd,L" ",L" ");
        pfnSetWindowTheme (groupFilter.m_hWnd,L" ",L" ");
    };

    // Accessing Outlook, could be no more in foreground
    SetForegroundWindow();

    wndCalendar = this;
    return FALSE;
}