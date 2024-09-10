void CRunMapExpertDlg::OnInsertparm(void)
{
	// two stages - name/description OR data itself
	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, id_InsertParmMapFileNoExt, "Map Filename (no extension)");
	menu.AppendMenu(MF_STRING, id_InsertParmMapFile, "Map Filename (with extension)");
	menu.AppendMenu(MF_STRING, id_InsertParmMapPath, "Map Path (no filename)");
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, id_InsertParmExeDir, "Game Executable Directory");
	menu.AppendMenu(MF_STRING, id_InsertParmBspDir, "BSP Directory");
	menu.AppendMenu(MF_STRING, id_InsertParmGameDir, "Game Directory");

	// track menu
	CWnd *pButton = GetDlgItem(IDC_INSERTPARM);
	CRect r;
	pButton->GetWindowRect(r);
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, r.left, r.bottom, this, NULL);
}