void CChangedDlg::OnBnClickedStash()
{
	CIconMenu popup;

	if (popup.CreatePopupMenu())
	{
		popup.AppendMenuIcon(ID_STASH_SAVE, IDS_MENUSTASHSAVE, IDI_COMMIT);

		CTGitPath root = g_Git.m_CurrentDir;
		if (root.HasStashDir())
		{
			popup.AppendMenuIcon(ID_STASH_POP, IDS_MENUSTASHPOP, IDI_RELOCATE);
			popup.AppendMenuIcon(ID_STASH_APPLY, IDS_MENUSTASHAPPLY, IDI_RELOCATE);
			popup.AppendMenuIcon(ID_STASH_LIST, IDS_MENUSTASHLIST, IDI_LOG);
		}

		POINT cursorPos;
		GetCursorPos(&cursorPos);
		int cmd = popup.TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN | TPM_NONOTIFY, cursorPos.x, cursorPos.y, this, 0);

		switch (cmd & 0xFFFF)
		{
		case ID_STASH_SAVE:
			CAppUtils::StashSave();
			break;
		case ID_STASH_POP:
			CAppUtils::StashPop(2);
			break;
		case ID_STASH_APPLY:
			CAppUtils::StashApply(_T(""), false);
			break;
		case ID_STASH_LIST:
			{
				CRefLogDlg dlg;
				dlg.m_CurrentBranch = _T("refs/stash");
				dlg.DoModal();
			}
			break;
		default:
			return;
		}
		OnBnClickedRefresh();
	}
}