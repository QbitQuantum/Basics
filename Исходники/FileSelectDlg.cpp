BOOL CFileSelectDlg::OnSetActive()
{
    // TODO: Add your specialized code here and/or call the base class

    CPropertySheet *parent = (CPropertySheet*)GetParent();
    parent->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);

    CString csFinishStr;
    csFinishStr.LoadString(IDS_FINISH_STRING);

    CWnd* finishButton = parent->GetDlgItem(ID_WIZFINISH);
    finishButton->SetWindowText(csFinishStr);

    return CPropertyPage::OnSetActive();
}