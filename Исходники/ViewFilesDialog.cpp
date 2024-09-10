void ViewFilesDialog::ShiftControls(int deltaX, int deltaY)
{
    HDWP hdwp;

    /*
     * Use deferred reposn so that they don't end up drawing on top of each
     * other and getting all weird.
     *
     * IMPORTANT: the DeferWindowPos stuff changes the tab order of the
     * items in the window.  The controls must be added in the reverse
     * order in which they appear in the window.
     */
    hdwp = BeginDeferWindowPos(15);
    hdwp = MoveControl(hdwp, this, AFX_IDW_SIZE_BOX, deltaX, deltaY);
    hdwp = MoveControl(hdwp, this, IDHELP, deltaX, deltaY);
    hdwp = MoveControl(hdwp, this, IDC_FVIEW_FONT, deltaX, deltaY);
    hdwp = MoveControl(hdwp, this, IDC_FVIEW_PRINT, deltaX, deltaY);
    hdwp = MoveControl(hdwp, this, IDC_FVIEW_FIND, deltaX, deltaY);
    hdwp = MoveControl(hdwp, this, IDC_FVIEW_FMT_RAW, 0, deltaY);
    hdwp = MoveControl(hdwp, this, IDC_FVIEW_FMT_HEX, 0, deltaY);
    hdwp = MoveControl(hdwp, this, IDC_FVIEW_FMT_BEST, 0, deltaY);
    hdwp = MoveControl(hdwp, this, IDC_FVIEW_PREV, 0, deltaY);
    hdwp = MoveControl(hdwp, this, IDC_FVIEW_NEXT, 0, deltaY);
    hdwp = MoveControl(hdwp, this, IDC_FVIEW_CMMT, 0, deltaY);
    hdwp = MoveControl(hdwp, this, IDC_FVIEW_RSRC, 0, deltaY);
    hdwp = MoveControl(hdwp, this, IDC_FVIEW_DATA, 0, deltaY);
    hdwp = MoveStretchControl(hdwp, this, IDC_FVIEW_FORMATSEL, 0, deltaY, deltaX, 0);
    hdwp = StretchControl(hdwp, this, IDC_FVIEW_EDITBOX, deltaX, deltaY);
    hdwp = MoveControl(hdwp, this, IDOK, deltaX, deltaY);
    if (!EndDeferWindowPos(hdwp)) {
        LOGI("EndDeferWindowPos failed");
    }

    /*
     * Work around buggy CRichEdit controls.  The inner edit area is only
     * resized when the box is shrunk, not when it's expanded, and the
     * results are inconsistent between Win98 and Win2K.
     *
     * Set the internal size equal to the size of the entire edit box.
     * This should be large enough to make everything work right, but small
     * enough to avoid funky scrolling behavior.  (If you want to set this
     * more precisely, don't forget that scroll bars are not part of the
     * edit control client area, and their sizes must be factored in.)
     */
    CRect rect;
    CRichEditCtrl* pEdit = (CRichEditCtrl*) GetDlgItem(IDC_FVIEW_EDITBOX);
    ASSERT(pEdit != NULL);
    //pEdit->GetClientRect(&rect);
    pEdit->GetWindowRect(&rect);
    //GetClientRect(&rect);
    rect.left = 2;
    rect.top = 2;
    pEdit->SetRect(&rect);
}