BOOL CFormatConverterWnd::OnInitDialog()
{
    BOOL bResult = CPropertySheet::OnInitDialog();
    // TODO:  Add your specialized code here
    ModifyStyle(0, WS_MINIMIZEBOX);
    CButton* omBtn;
    WINDOWPLACEMENT omWndPlace;
    omBtn = reinterpret_cast<CButton*>(GetDlgItem(ID_APPLY_NOW));
    omBtn->ShowWindow(SW_HIDE);
    omBtn->GetWindowPlacement(&omWndPlace);
    omBtn = reinterpret_cast<CButton*>(GetDlgItem(IDOK));
    omBtn->ShowWindow(SW_HIDE);
    omBtn = reinterpret_cast<CButton*>(GetDlgItem(IDCANCEL));
    omBtn->SetWindowText("Close");
    omBtn->SetWindowPlacement(&omWndPlace);
    return bResult;
}