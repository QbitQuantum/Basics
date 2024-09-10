void CSignInDlg::OnNMRClickListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos),HIWORD(dwPos));

	CMenu menu;

	menu.LoadMenu(IDR_MENU_USER);

	CMenu *popue = menu.GetSubMenu(0);

	if (pNMItemActivate->iItem == -1)
	{
		popue->DeleteMenu(ID_USER_DELETE,MF_BYCOMMAND);
	}

	popue->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,this);
	*pResult = 0;
}