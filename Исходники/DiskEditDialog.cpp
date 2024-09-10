BOOL NibbleEditDialog::OnInitDialog(void)
{
    /*
     * Get rid of the "sector" input item.
     */
    CWnd* pWnd;

    pWnd = GetDlgItem(IDC_STEXT_SECTOR);
    pWnd->DestroyWindow();
    pWnd = GetDlgItem(IDC_DISKEDIT_SECTOR);
    pWnd->DestroyWindow();
    pWnd = GetDlgItem(IDC_DISKEDIT_SECTORSPIN);
    pWnd->DestroyWindow();

    CString trackStr;
    trackStr.Format(L"Track (%d):", fpDiskFS->GetDiskImg()->GetNumTracks());
    pWnd = GetDlgItem(IDC_STEXT_TRACK);
    ASSERT(pWnd != NULL);
    pWnd->SetWindowText(trackStr);

    /*
     * Increase the size of the window so it's the same height as blocks.
     *
     * NOTE: using a pixel constant is probably bad.  We want to use something
     * like GetTextMetrics, but I'm not sure how to get that without a
     * device context.
     */
    CRichEditCtrl* pEdit = (CRichEditCtrl*)GetDlgItem(IDC_DISKEDIT_EDIT);
    ASSERT(pEdit != NULL);
    const int kStretchHeight = 249;
    CRect rect;

    GetWindowRect(&rect);
    rect.bottom += kStretchHeight;
    MoveWindow(&rect);

    /*
     * Must postpone resize of edit ctrl until after data has been loaded, or
     * scroll bars fail to appear under Win98.  Makes no sense whatsoever, but
     * that's Windows for you.
     */
#if 0
    CRect inner;
    pEdit->GetRect(&inner);
    inner.bottom += kStretchHeight;
    pEdit->GetWindowRect(&rect);
    ScreenToClient(&rect);
    rect.bottom += kStretchHeight;
    pEdit->MoveWindow(&rect);
    pEdit->SetRect(&inner);
#endif

    /* show the scroll bar */
    pEdit->ShowScrollBar(SB_VERT);

    MoveControl(this, IDC_DISKEDIT_DONE, 0, kStretchHeight);
    MoveControl(this, IDC_DISKEDIT_OPENFILE, 0, kStretchHeight);
    MoveControl(this, IDC_DISKEDIT_SUBVOLUME, 0, kStretchHeight);
    MoveControl(this, IDHELP, 0, kStretchHeight);
    MoveControl(this, IDC_DISKEDIT_NIBBLE_PARMS, 0, kStretchHeight);

    /* disable opening of files and sub-volumes */
    pWnd = GetDlgItem(IDC_DISKEDIT_OPENFILE);
    pWnd->EnableWindow(FALSE);
    pWnd = GetDlgItem(IDC_DISKEDIT_SUBVOLUME);
    pWnd->EnableWindow(FALSE);

    /*
     * Do base-class construction.
     */
    DiskEditDialog::OnInitDialog();

    /*
     * This currently has no effect on the nibble editor.  Someday we may
     * want to highlight and/or decode address fields.
     */
    pWnd = GetDlgItem(IDC_DISKEDIT_NIBBLE_PARMS);
    pWnd->EnableWindow(FALSE);

    /*
     * Configure the track spin button.
     */
    MySpinCtrl* pSpin;
    pSpin = (MySpinCtrl*)GetDlgItem(IDC_DISKEDIT_TRACKSPIN);
    ASSERT(pSpin != NULL);
    pSpin->SetRange32(0, fpDiskFS->GetDiskImg()->GetNumTracks()-1);
    pSpin->SetPos(0);

    /* give us something to look at */
    LoadData();

    return TRUE;
}