//------------------------------------------------------------------------------
void CTreeCtrlBase::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	CString str = GetItemText(pNMTreeView->itemOld.hItem);

	if (TREE_WINDOW == m_Type)
	{
		CDialog *pOldDlg = (CDialog*)pNMTreeView->itemOld.lParam;
		if (pOldDlg)
			pOldDlg->ShowWindow(SW_HIDE);
	}

	*pResult = 0;
}