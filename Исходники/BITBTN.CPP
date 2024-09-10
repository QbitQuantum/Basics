void CMlsSimpleBitmapButton::Initialize(UINT nID, CWnd* pParent)
{
	CString csText;
	TRY
	{
		CWnd* pControl = pParent->GetDlgItem(nID);
		if (pControl != NULL)
		{
			CRect crControl;
			pControl->GetWindowRect(crControl);
			pParent->ScreenToClient(crControl);
			pControl->GetWindowText(csText);
			Create(NULL, csText, pControl->GetStyle(), crControl, pParent, nID, NULL);
			SetWindowPos(pControl, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
			SetFont(pControl->GetFont());
			pControl->DestroyWindow();
		}
	}
	END_TRY
}