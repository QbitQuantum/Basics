void CSubtitleDlDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW lpnmlv = (LPNMLISTVIEW)pNMHDR;

	if(lpnmlv->iItem >= 0)
	{
		CRect r;
		m_list.GetItemRect(lpnmlv->iItem, r, LVIR_ICON);
		if(r.PtInRect(lpnmlv->ptAction))
		{
			SetChecked(lpnmlv->iItem, (GetChecked(lpnmlv->iItem)&1) == 0 ? 1 : 0);
		}
	}

	*pResult = 0;
}