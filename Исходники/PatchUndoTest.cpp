bool CPatchUndoTest::DoPageEdit(CWnd *pParent, CString& PageName, CString& CtrlCaption)
{
    CHWNDArray	Ctrl;
    CTabbedDlg	*pTabDlg = GetPageControls(pParent, PageName, Ctrl);
    ASSERT(pTabDlg != NULL);
    ASSERT(Ctrl.GetSize());
    int	iCtrl = Random(Ctrl.GetSize());
    CWnd	*pWnd = CWnd::FromHandle(Ctrl[iCtrl]);
    if (pWnd == NULL || !pWnd->IsWindowEnabled())	// skip disabled controls
        return(FALSE);
    UINT	nID = pWnd->GetDlgCtrlID();
    CtrlCaption = pTabDlg->GetControlCaption(nID);
    CNumEdit	*pNumEdit = DYNAMIC_DOWNCAST(CNumEdit, pWnd);
    if (pNumEdit != NULL) {
        double	val = pNumEdit->GetVal();
        pNumEdit->AddSpin(1);
        if (pNumEdit->GetVal() == val)
            pNumEdit->AddSpin(-1);
        return(TRUE);
    }
    CComboBox	*pCombo = DYNAMIC_DOWNCAST(CComboBox, pWnd);
    if (pCombo != NULL) {
        int	nItems = pCombo->GetCount();
        if (nID == IDC_PATCH_GEN_PPQ)	// if PPQ combo
            nItems /= 4;	// limit range to avoid zero timer period
        int	iItem = RandomExcluding(nItems, pCombo->GetCurSel());
        if (iItem < 0)
            return(FALSE);
        pCombo->SetCurSel(iItem);
        pCombo->GetParent()->SendMessage(WM_COMMAND,
                                         MAKELONG(pCombo->GetDlgCtrlID(), CBN_SELCHANGE));
        return(TRUE);
    }
    CButton	*pBtn = DYNAMIC_DOWNCAST(CButton, pWnd);
    if (pBtn != NULL) {
        pBtn->SetCheck(!pBtn->GetCheck());
        pBtn->GetParent()->SendMessage(WM_COMMAND,
                                       MAKELONG(pBtn->GetDlgCtrlID(), BN_CLICKED));
        return(TRUE);
    }
    return(FALSE);
}