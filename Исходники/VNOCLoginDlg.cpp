void CVNOCLoginDlg::_SetVerifyState( BOOL bVerifying )
{
	m_bVerifying = bVerifying;
	CEdit* pEditun = (CEdit*)GetDlgItem(IDC_LoginDlg_EDIT_USERNAME);	ATLASSERT(pEditun);
	CEdit* pEditpw = (CEdit*)GetDlgItem(IDC_LoginDlg_EDIT_PWD);			ATLASSERT(pEditpw);
	CButton* pBtnrp = (CButton*)GetDlgItem(IDC_LoginDlg_CHECKBOX_R);		ATLASSERT(pBtnrp);
	CButton* pBtnLogin = (CButton*)GetDlgItem(IDOK);						ATLASSERT(pBtnLogin);

	pEditun->EnableWindow(!bVerifying);
	pEditpw->EnableWindow(!bVerifying);
	pBtnrp->EnableWindow(!bVerifying);
	pBtnLogin->EnableWindow(!bVerifying);
}