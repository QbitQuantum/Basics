void CCheckListBox::MouseSelect(UINT nFlags, CPoint point)
{
	int nTopIndex = GetTopIndex();

	if (GetCapture() == this)
	{
		CRect crClient;
		GetClientRect(crClient);
		
		int nIndex = Index(point);
		
		if (nIndex >= 0)
		{
			if (nIndex != m_nCurrent)
			{
				int nItem = m_nCurrent;
				
				while (nItem != nIndex)
				{
					if (nItem < nIndex)
					{
						nItem++;
					}
					else
					{
						nItem--;
					}
					
					Select(nItem, m_fMark, TRUE);
				}

				UpdateWindow();
				
				SetCurSel(nIndex);
				m_nCurrent = nIndex;
				
#ifdef WIN32
				GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), LBN_SELCHANGE), (LPARAM)GetSafeHwnd());
#else
				GetParent()->SendMessage(WM_COMMAND, GetDlgCtrlID(), MAKELPARAM(GetSafeHwnd(), LBN_SELCHANGE));
#endif
			}
		}
	}
	m_fScrolling = (GetTopIndex() != nTopIndex);
}