void CPopupEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);

	CString Text;
	GetWindowText(Text);

	if (Text != "INFINITY") {
		if (!atoi(Text)) {
			SetWindowText(m_sInitText);
			GetWindowText(Text);
		}

		Text.Format("%d", atoi(Text));

		CString Temp;
		GetWindowText(Temp);
		Temp = Temp.Right(1);
				
		if (!Temp.SpanIncluding("kKmMgG").IsEmpty())
			Text.Format("%s%s", LPCTSTR(Text), LPCTSTR(Temp));

		CString OldText;
		GetWindowText(OldText) ;
		if (GetModify() || OldText != Text)
			SetWindowText(Text);
	}

	if (m_bIsEmbeddedIntoListCtrl) {
		CWnd *Parent = GetParent();
		ASSERT_VALID(Parent);

		CString str;
		GetWindowText(str);

		LV_DISPINFO dispinfo;
		dispinfo.hdr.hwndFrom  = Parent->m_hWnd;
		dispinfo.hdr.idFrom    = GetDlgCtrlID();
		dispinfo.hdr.code      = LVN_ENDLABELEDIT;

		dispinfo.item.mask     = LVIF_TEXT;
		dispinfo.item.iItem    = m_iItem;
		dispinfo.item.iSubItem = m_iSubItem;

		if (m_bESC) {
			dispinfo.item.pszText    = NULL;
			dispinfo.item.cchTextMax = 0;
		}
		else {
			dispinfo.item.pszText    = const_cast<LPTSTR>((LPCTSTR) str);
			dispinfo.item.cchTextMax = str.GetLength();
		}

		CWnd *ParentParent = Parent->GetParent();
		ASSERT_VALID(ParentParent);
		ParentParent->SendMessage(WM_NOTIFY, Parent->GetDlgCtrlID(), LPARAM(&dispinfo));
		DestroyWindow();
	}
}