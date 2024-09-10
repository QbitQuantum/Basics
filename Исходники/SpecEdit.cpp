void CSpecEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	// TODO: Add your message handler code here
	if (this->m_ComboID==cmb3)
	{
		CString str;
		LOGFONT lf;
		CFont* pFont = ((CMyFontDlg*)m_pDlg)->GetSelectedFont();
		pFont->GetLogFont(&lf);
		pFont->DeleteObject();
		
		GetWindowText(str);
		if (str.GetLength()==0)
		{
			::SendMessage(m_pDlg->GetDlgItem(cmb3)->m_hWnd, CB_SETCURSEL, 0, 0);
			GetWindowText(str);
		}

		int k = _wtoi(str);
		lf.lfHeight = -MulDiv(k, GetDeviceCaps(GetParent()->GetDC()->m_hDC, LOGPIXELSY), 72);
		pFont->CreateFontIndirectW(&lf);
		m_pDlg->InvalidateRect(&((CMyFontDlg*)m_pDlg)->TextRect);		
	}

	if (this->m_ComboID==cmb2)
	{
		CString str;
		GetWindowText(str);
		CComboBox* pComboBox = (CComboBox*)(m_pDlg->GetDlgItem(cmb2));
		if (str.GetLength()==0 || pComboBox->GetCurSel()==-1)
		{
			::SendMessageW(m_pDlg->GetDlgItem(cmb2)->m_hWnd, CB_SETCURSEL, 0, 0);
		}
	}
}