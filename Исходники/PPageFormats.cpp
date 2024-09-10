BOOL CPPageFormats::OnInitDialog()
{
    __super::OnInitDialog();

    m_bFileExtChanged = false;
    m_bHaveRegisteredCategory = false;

    m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

    m_list.InsertColumn(COL_CATEGORY, _T("Category"), LVCFMT_LEFT, 300);
    m_list.InsertColumn(COL_ENGINE, _T("Engine"), LVCFMT_RIGHT, 60);

    // We don't use m_onoff.Create(IDB_CHECKBOX, 12, 3, 0xffffff) since
    // we want to load the bitmap directly from the main executable.
    CImage onoff;
    onoff.LoadFromResource(AfxGetInstanceHandle(), IDB_CHECKBOX);
    m_onoff.Create(12, 12, ILC_COLOR4 | ILC_MASK, 0, 3);
    m_onoff.Add(CBitmap::FromHandle(onoff), 0xffffff);
    m_list.SetImageList(&m_onoff, LVSIL_SMALL);

    int fSetContextFiles = FALSE;

    const CAppSettings& s = AfxGetAppSettings();
    m_mf = s.m_Formats;

    for (int i = 0, cnt = (int)m_mf.GetCount(); i < cnt; i++) {
        if (!m_mf[i].IsAssociable()) {
            continue;
        }

        CString label;
        label.Format(_T("%s (%s)"), m_mf[i].GetDescription(), m_mf[i].GetExts());

        int iItem = m_list.InsertItem(i, label);
        m_list.SetItemData(iItem, i);
        engine_t e = m_mf[i].GetEngineType();
        m_list.SetItemText(iItem, COL_ENGINE,
                           e == DirectShow ? _T("DirectShow") :
                           e == RealMedia ? _T("RealMedia") :
                           e == QuickTime ? _T("QuickTime") :
                           e == ShockWave ? _T("ShockWave") : _T("-"));

        CFileAssoc::reg_state_t state = CFileAssoc::IsRegistered(m_mf[i]);
        if (!m_bHaveRegisteredCategory && state != CFileAssoc::NOT_REGISTERED) {
            m_bHaveRegisteredCategory = true;
        }
        SetCheckedMediaCategory(iItem, (state == CFileAssoc::SOME_REGISTERED) ? 2 : (state == CFileAssoc::ALL_REGISTERED));

        if (!fSetContextFiles && CFileAssoc::AreRegisteredFileContextMenuEntries(m_mf[i]) != CFileAssoc::NOT_REGISTERED) {
            fSetContextFiles = TRUE;
        }
    }

    m_list.SetColumnWidth(COL_ENGINE, LVSCW_AUTOSIZE_USEHEADER);

    m_list.SetSelectionMark(0);
    m_list.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
    m_exts = m_mf[m_list.GetItemData(0)].GetExtsWithPeriod();

    bool fRtspFileExtFirst;
    engine_t e = m_mf.GetRtspHandler(fRtspFileExtFirst);
    m_iRtspHandler = (e == RealMedia ? 0 : e == QuickTime ? 1 : 2);
    m_fRtspFileExtFirst = fRtspFileExtFirst;

    m_fContextFiles.SetCheck(fSetContextFiles);

    m_apvideo.SetCheck(CFileAssoc::IsAutoPlayRegistered(CFileAssoc::AP_VIDEO));
    m_apmusic.SetCheck(CFileAssoc::IsAutoPlayRegistered(CFileAssoc::AP_MUSIC));
    m_apaudiocd.SetCheck(CFileAssoc::IsAutoPlayRegistered(CFileAssoc::AP_AUDIOCD));
    m_apdvd.SetCheck(CFileAssoc::IsAutoPlayRegistered(CFileAssoc::AP_DVDMOVIE));

    CreateToolTip();

    if (SysVersion::IsVistaOrLater() && !IsUserAnAdmin()) {
        GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);

        GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK6)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK7)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK8)->EnableWindow(FALSE);

        GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);

        GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON5)->SendMessage(BCM_SETSHIELD, 0, 1);

        m_bInsufficientPrivileges = true;
    } else {
        GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);
    }

    if (SysVersion::Is8()) {
        CRect r;
        GetDlgItem(IDC_STATIC2)->GetWindowRect(r);
        ScreenToClient(r);
        r.BottomRight().Offset(0, -50);
        GetDlgItem(IDC_STATIC2)->MoveWindow(r);
        GetDlgItem(IDC_LIST1)->GetWindowRect(r);
        ScreenToClient(r);
        r.BottomRight().Offset(0, -50);
        GetDlgItem(IDC_LIST1)->MoveWindow(r);
        GetDlgItem(IDC_EDIT1)->GetWindowRect(r);
        ScreenToClient(r);
        r.OffsetRect(0, -50);
        GetDlgItem(IDC_EDIT1)->MoveWindow(r);
        GetDlgItem(IDC_BUTTON2)->GetWindowRect(r);
        ScreenToClient(r);
        r.OffsetRect(0, -50);
        GetDlgItem(IDC_BUTTON2)->MoveWindow(r);
        GetDlgItem(IDC_BUTTON_EXT_SET)->GetWindowRect(r);
        ScreenToClient(r);
        r.OffsetRect(0, -50);
        GetDlgItem(IDC_BUTTON_EXT_SET)->MoveWindow(r);
    } else {
        GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_HIDE);
    }

    m_fContextDir.SetCheck(CFileAssoc::AreRegisteredFolderContextMenuEntries());
    m_fAssociatedWithIcons.SetCheck(s.fAssociatedWithIcons);

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}