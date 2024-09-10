void CSheetExchMain::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if( nChar == VK_RETURN )
	{
		CWnd* pWnd = GetDlgItem(ID_WIZNEXT);
		if( pWnd )
		{
			if( pWnd->IsWindowEnabled() )
				OnBnClickedWiznext();
			else
				OnBnClickedWizfinish();
			return;
		}
	}

	CHSNewWizDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}