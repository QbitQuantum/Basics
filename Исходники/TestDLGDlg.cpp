void CTestDLGDlg::OnBnClickedButton2()
{
	CString strClassName = L"#32770";
	CString strWndName = L"TestDLG";

	int iEdtUserNameID = 0x000003E9;
	int iEdtPasswordID = 0x00003EA;
	int iBtnLogin = 0x000003E8;
	int iCheckBlueID = 0x000003ED;

	CWnd *pWnd = CWnd::FindWindow(strClassName, strWndName);
	if (pWnd != NULL) {


		CEdit * pEdit = (CEdit*)pWnd->GetDlgItem(iEdtUserNameID);
		if (NULL != pEdit) {
			pEdit->SendMessage(WM_SETTEXT, NULL, (LPARAM)L"AnLNT");
		}

		pEdit = (CEdit *)pWnd->GetDlgItem(iEdtPasswordID);
		if (NULL != pEdit) {
			pEdit->SendMessage(WM_SETTEXT, NULL, (LPARAM)L"123456");
		}

		CButton *pButton = (CButton*)GetDlgItem(iCheckBlueID);
		if (pButton != NULL) {
	
			//::SendMessage(pButton->m_hWnd, BM_SETCHECK,  BST_CHECKED, 0);
			::SendMessage(pButton->m_hWnd, 241,  0, 0);
		}

		/*
		CButton *pButton = (CButton*)GetDlgItem(iBtnLogin);
		if (NULL != pButton) {

			WORD lParam  = (WORD)pButton->m_hWnd;
			WORD wParam = MAKEWPARAM(iBtnLogin, BN_CLICKED);

			pWnd->SendMessage(WM_COMMAND, wParam, lParam);
			//pButton->SendMessage(WM_LBUTTONDOWN);
			//pButton->SendMessage(WM_LBUTTONUP);
			//pButton->PostMessage(BM_CLICK);
		}
		*/
	}
}