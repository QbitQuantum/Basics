void COptionsDirectoriesPage::SelectDirectory(LanguageStringID Title, CModifiedEditBox & EditBox, CModifiedButton & Default, CModifiedButton & selected)
{
	wchar_t Buffer[MAX_PATH], Directory[MAX_PATH];
	LPITEMIDLIST pidl;
	BROWSEINFOW bi;

	stdstr InitialDir = EditBox.GetWindowText();

	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = Buffer;
	bi.lpszTitle = GS(Title);
	bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
	bi.lpfn = (BFFCALLBACK)SelectDirCallBack;
	bi.lParam = (DWORD)InitialDir.c_str();
	if ((pidl = SHBrowseForFolderW(&bi)) != NULL)
	{
		if (SHGetPathFromIDListW(pidl, Directory))
		{
			stdstr path;
			CPath SelectedDir(path.FromUTF16(Directory), "");
			EditBox.SetChanged(true);
			EditBox.SetWindowText(SelectedDir);
			Default.SetChanged(true);
			Default.SetCheck(BST_UNCHECKED);
			selected.SetCheck(BM_SETCHECK);
			SendMessage(GetParent(), PSM_CHANGED, (WPARAM)m_hWnd, 0);
		}
	}
}