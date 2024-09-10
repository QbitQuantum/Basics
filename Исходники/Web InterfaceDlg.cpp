void CWebInterfaceDlg::ShowTrayMenu()
{
	CMenu menu;
	menu.LoadMenu (IDM_TRAY);
	CMenu *pPopup = menu.GetSubMenu (0);

	SetForegroundWindow ();

	pPopup->SetDefaultItem (ID_CONFIGURE);

	CPoint pt;
	GetCursorPos (&pt);

	pPopup->TrackPopupMenu (TPM_RIGHTBUTTON | TPM_BOTTOMALIGN | TPM_RIGHTALIGN,	pt.x, pt.y, this);

	menu.DestroyMenu ();
}