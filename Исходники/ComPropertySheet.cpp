void CComPropertySheet::OnActivated(CPropertyPage* pPage)
{
	if(!pPage) return;

	CRect bounds(30000,30000,-30000,-30000);

	CRect wr, cr;
	GetWindowRect(wr);
	GetClientRect(cr);
	CSize ws = wr.Size(), cs = cr.Size();

	CRect twr, tcr;
	CTabCtrl* pTC = (CTabCtrl*)GetDlgItem(AFX_IDC_TAB_CONTROL);
	pTC->GetWindowRect(twr);
	pTC->GetClientRect(tcr);
	CSize tws = twr.Size(), tcs = tcr.Size();

	if(CWnd* pChild = pPage->GetWindow(GW_CHILD))
	{
		pChild->ModifyStyle(WS_CAPTION|WS_THICKFRAME, 0);
		pChild->ModifyStyleEx(WS_EX_DLGMODALFRAME, WS_EX_CONTROLPARENT);

		for(CWnd* pGrandChild = pChild->GetWindow(GW_CHILD); pGrandChild; pGrandChild = pGrandChild->GetNextWindow())
		{
			if(!(pGrandChild->GetStyle()&WS_VISIBLE)) continue;

			CRect r;
			pGrandChild->GetWindowRect(&r);
			pChild->ScreenToClient(r);
			bounds |= r;
		}
	}

	bounds |= CRect(0,0,0,0);
	bounds.SetRect(0, 0, bounds.right + max(bounds.left, 4), bounds.bottom + max(bounds.top, 4));

	CRect r = CRect(CPoint(0,0), bounds.Size());
	pTC->AdjustRect(TRUE, r);
	r.SetRect(twr.TopLeft(), twr.TopLeft() + r.Size());
	ScreenToClient(r);
	pTC->MoveWindow(r);
	pTC->ModifyStyle(TCS_MULTILINE, TCS_SINGLELINE);

	CSize diff = r.Size() - tws;

	if(!bounds.IsRectEmpty())
	{
		if(CWnd* pChild = pPage->GetWindow(GW_CHILD))
			pChild->MoveWindow(bounds);
		CRect r = twr;
		pTC->AdjustRect(FALSE, r);
		ScreenToClient(r);
		pPage->MoveWindow(CRect(r.TopLeft(), bounds.Size()));
	}

	int _afxPropSheetButtons[] = { IDOK, IDCANCEL, ID_APPLY_NOW, IDHELP };
	for(int i = 0; i < countof(_afxPropSheetButtons); i++)
	{
		if(CWnd* pWnd = GetDlgItem(_afxPropSheetButtons[i]))
		{
			pWnd->GetWindowRect(r);
			ScreenToClient(r);
			pWnd->MoveWindow(CRect(r.TopLeft() + diff, r.Size()));
		}
	}

	MoveWindow(CRect(wr.TopLeft(), ws + diff));

	Invalidate();
}