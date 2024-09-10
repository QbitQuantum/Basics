void CCustomHeadersDlg::OnAddHeader() 
{
	
	CEditHeadersDlg EditDlg( " ",this);
	if (IDOK == EditDlg.DoModal())
	{
		if ( !EditDlg.m_strHeader.IsEmpty())
		{
			m_lbHeaderList.AddString(EditDlg.m_strHeader);
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}

	CWnd *pWnd = (CWnd*) GetDlgItem(IDC_ADD_HEADER);

	if (pWnd)
	{
		pWnd->SetFocus();
	}
	UpdateData();	
}