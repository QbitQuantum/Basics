BOOL CLicenseDlg::OnSetActive()
{
    if (!CheckWindowsVersion()) {
        CPropertyPage::EndDialog(IDCANCEL);
    }

    CPropertySheet* pSheet = (CPropertySheet*)GetParent();
    ASSERT_KINDOF(CPropertySheet, pSheet);
    if (m_FirstTime) {
        m_FirstTime = FALSE;

        //  Disable everything until the user scrolls the license text
        CButton *radio_all = (CButton *) GetDlgItem(IDC_DISAGREE);
        radio_all->SetCheck(1);
        CButton *understand = (CButton *) GetDlgItem(IDC_UNDERSTAND);
        understand->SetCheck(BST_UNCHECKED);
        OnUnderstand();
        understand->EnableWindow(FALSE);
        pSheet->SetWizardButtons(0);
        UpdateData(FALSE); // write to screen
    } else {
        pSheet->SetWizardButtons(PSWIZB_NEXT);
    }
    return CPropertyPage::OnSetActive();
}