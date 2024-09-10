static int BuildTree(HWND hwndDlg)
{
	HWND hTree = GetDlgItem(hwndDlg, IDC_BUTTONORDERTREE);
	OrderData *dat = (OrderData*)GetWindowLongPtr(hTree, GWLP_USERDATA);

	dat->himlButtonIcons = ImageList_Create(GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), ILC_COLOR32 | ILC_MASK, 2, 2);
	TreeView_SetImageList(hTree, dat->himlButtonIcons, TVSIL_NORMAL);
	SetWindowLongPtr(hTree, GWL_STYLE, GetWindowLongPtr(hTree,GWL_STYLE)|TVS_NOHSCROLL);
	TreeView_DeleteAllItems(hTree);

	if (Buttons.getCount() == 0)
		return FALSE;

	for (int i = 0; i < Buttons.getCount(); i++)
		AddLine(hTree, Buttons[i], TVI_LAST, dat->himlButtonIcons);
	return TRUE;
}