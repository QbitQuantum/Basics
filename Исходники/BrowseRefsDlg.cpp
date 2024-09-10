void CBrowseRefsDlg::ShowContextMenu(CPoint point, HTREEITEM hTreePos, VectorPShadowTree& selectedLeafs)
{
	CIconMenu popupMenu;
	popupMenu.CreatePopupMenu();

	bool bAddSeparator = false;
	CString remoteName;

	if(selectedLeafs.size()==1)
	{
		bAddSeparator = true;

		bool bShowReflogOption				= false;
		bool bShowFetchOption				= false;
		bool bShowSwitchOption				= false;
		bool bShowRenameOption				= false;
		bool bShowCreateBranchOption		= false;
		bool bShowEditBranchDescriptionOption = false;

		CString fetchFromCmd;

		if(selectedLeafs[0]->IsFrom(L"refs/heads"))
		{
			bShowReflogOption = true;
			bShowSwitchOption = true;
			bShowRenameOption = true;
			bShowEditBranchDescriptionOption = true;
		}
		else if(selectedLeafs[0]->IsFrom(L"refs/remotes"))
		{
			bShowReflogOption = true;
			bShowFetchOption  = true;
			bShowCreateBranchOption = true;

			int dummy = 0;//Needed for tokenize
			remoteName = selectedLeafs[0]->GetRefName();
			remoteName = remoteName.Mid(13);
			remoteName = remoteName.Tokenize(L"/", dummy);
			fetchFromCmd.Format(IDS_PROC_BROWSEREFS_FETCHFROM, remoteName);
		}
		else if(selectedLeafs[0]->IsFrom(L"refs/tags"))
		{
		}

		CString temp;
		temp.LoadString(IDS_MENULOG);
		popupMenu.AppendMenuIcon(eCmd_ViewLog, temp, IDI_LOG);
		popupMenu.AppendMenuIcon(eCmd_RepoBrowser, IDS_LOG_BROWSEREPO, IDI_REPOBROWSE);
		if(bShowReflogOption)
		{
			temp.LoadString(IDS_MENUREFLOG);
			popupMenu.AppendMenuIcon(eCmd_ShowReflog, temp, IDI_LOG);
		}

		popupMenu.AppendMenu(MF_SEPARATOR);
		bAddSeparator = false;

		if(bShowFetchOption)
		{
			bAddSeparator = true;
			popupMenu.AppendMenuIcon(eCmd_Fetch, fetchFromCmd, IDI_PULL);
		}

		if(bAddSeparator)
			popupMenu.AppendMenu(MF_SEPARATOR);

		bAddSeparator = false;
		if (m_bHasWC)
		{
			popupMenu.AppendMenuIcon(eCmd_Switch, CString(MAKEINTRESOURCE(IDS_SWITCH_TO_THIS)), IDI_SWITCH);
			popupMenu.AppendMenu(MF_SEPARATOR);
		}

		if(bShowCreateBranchOption)
		{
			bAddSeparator = true;
			temp.LoadString(IDS_MENUBRANCH);
			popupMenu.AppendMenuIcon(eCmd_CreateBranch, temp, IDI_COPY);
		}

		if (bShowEditBranchDescriptionOption)
		{
			bAddSeparator = true;
			popupMenu.AppendMenuIcon(eCmd_EditBranchDescription, CString(MAKEINTRESOURCE(IDS_PROC_BROWSEREFS_EDITDESCRIPTION)), IDI_RENAME);
		}
		if(bShowRenameOption)
		{
			bAddSeparator = true;
			popupMenu.AppendMenuIcon(eCmd_Rename, CString(MAKEINTRESOURCE(IDS_PROC_BROWSEREFS_RENAME)), IDI_RENAME);
		}
	}
	else if(selectedLeafs.size() == 2)
	{
		bAddSeparator = true;
		popupMenu.AppendMenuIcon(eCmd_Diff, CString(MAKEINTRESOURCE(IDS_PROC_BROWSEREFS_COMPAREREFS)), IDI_DIFF);
	}

	if(!selectedLeafs.empty())
	{
		if(AreAllFrom(selectedLeafs, L"refs/remotes/"))
		{
			if(bAddSeparator)
				popupMenu.AppendMenu(MF_SEPARATOR);
			CString menuItemName;
			if(selectedLeafs.size() == 1)
				menuItemName.LoadString(IDS_PROC_BROWSEREFS_DELETEREMOTEBRANCH);
			else
				menuItemName.Format(IDS_PROC_BROWSEREFS_DELETEREMOTEBRANCHES, selectedLeafs.size());

			popupMenu.AppendMenuIcon(eCmd_DeleteRemoteBranch, menuItemName, IDI_DELETE);
			bAddSeparator = true;
		}
		else if(AreAllFrom(selectedLeafs, L"refs/heads/"))
		{
			if(bAddSeparator)
				popupMenu.AppendMenu(MF_SEPARATOR);
			CString menuItemName;
			if(selectedLeafs.size() == 1)
				menuItemName.LoadString(IDS_PROC_BROWSEREFS_DELETEBRANCH);
			else
				menuItemName.Format(IDS_PROC_BROWSEREFS_DELETEBRANCHES, selectedLeafs.size());

			popupMenu.AppendMenuIcon(eCmd_DeleteBranch, menuItemName, IDI_DELETE);
			bAddSeparator = true;
		}
		else if(AreAllFrom(selectedLeafs, L"refs/tags/"))
		{
			if(bAddSeparator)
				popupMenu.AppendMenu(MF_SEPARATOR);
			CString menuItemName;
			if(selectedLeafs.size() == 1)
				menuItemName.LoadString(IDS_PROC_BROWSEREFS_DELETETAG);
			else
				menuItemName.Format(IDS_PROC_BROWSEREFS_DELETETAGS, selectedLeafs.size());

			popupMenu.AppendMenuIcon(eCmd_DeleteTag, menuItemName, IDI_DELETE);
			bAddSeparator = true;
		}
	}


	if(hTreePos!=NULL && selectedLeafs.empty())
	{
		CShadowTree* pTree=(CShadowTree*)m_RefTreeCtrl.GetItemData(hTreePos);
		if(pTree->IsFrom(L"refs/remotes"))
		{
			if(bAddSeparator)
				popupMenu.AppendMenu(MF_SEPARATOR);
			popupMenu.AppendMenuIcon(eCmd_ManageRemotes, CString(MAKEINTRESOURCE(IDS_PROC_BROWSEREFS_MANAGEREMOTES)), IDI_SETTINGS);
			bAddSeparator = true;
			if(selectedLeafs.empty())
			{
				int dummy = 0;//Needed for tokenize
				remoteName = pTree->GetRefName();
				remoteName = remoteName.Mid(13);
				remoteName = remoteName.Tokenize(L"/", dummy);
				if(!remoteName.IsEmpty())
				{
					CString temp;
					temp.Format(IDS_PROC_BROWSEREFS_FETCHFROM, remoteName);
					popupMenu.AppendMenuIcon(eCmd_Fetch, temp, IDI_PULL);

					temp.LoadString(IDS_DELETEREMOTETAG);
					popupMenu.AppendMenuIcon(eCmd_DeleteRemoteTag, temp, IDI_DELETE);
				}
			}
		}
		if(pTree->IsFrom(L"refs/heads"))
		{
			if(bAddSeparator)
				popupMenu.AppendMenu(MF_SEPARATOR);
			CString temp;
			temp.LoadString(IDS_MENUBRANCH);
			popupMenu.AppendMenuIcon(eCmd_CreateBranch, temp, IDI_COPY);
		}
		if(pTree->IsFrom(L"refs/tags"))
		{
			if(bAddSeparator)
				popupMenu.AppendMenu(MF_SEPARATOR);
			CString temp;
			temp.LoadString(IDS_MENUTAG);
			popupMenu.AppendMenuIcon(eCmd_CreateTag, temp, IDI_TAG);
		}
	}


	eCmd cmd=(eCmd)popupMenu.TrackPopupMenuEx(TPM_LEFTALIGN|TPM_RETURNCMD, point.x, point.y, this, 0);
	switch(cmd)
	{
	case eCmd_ViewLog:
		{
			CLogDlg dlg;
			dlg.SetStartRef(selectedLeafs[0]->GetRefName());
			dlg.DoModal();
		}
		break;
	case eCmd_RepoBrowser:
		CAppUtils::RunTortoiseProc(_T("/command:repobrowser /path:\"") + g_Git.m_CurrentDir + _T("\" /rev:") + selectedLeafs[0]->GetRefName());
		break;
	case eCmd_DeleteBranch:
	case eCmd_DeleteRemoteBranch:
		{
			if(ConfirmDeleteRef(selectedLeafs))
				DoDeleteRefs(selectedLeafs, true);
			Refresh();
		}
		break;
	case eCmd_DeleteTag:
		{
			if(ConfirmDeleteRef(selectedLeafs))
				DoDeleteRefs(selectedLeafs, true);
			Refresh();
		}
		break;
	case eCmd_ShowReflog:
		{
			CRefLogDlg refLogDlg(this);
			refLogDlg.m_CurrentBranch = selectedLeafs[0]->GetRefName();
			refLogDlg.DoModal();
		}
		break;
	case eCmd_Fetch:
		{
			CAppUtils::Fetch(remoteName);
			Refresh();
		}
		break;
	case eCmd_DeleteRemoteTag:
		{
			CDeleteRemoteTagDlg deleteRemoteTagDlg;
			deleteRemoteTagDlg.m_sRemote = remoteName;
			deleteRemoteTagDlg.DoModal();
		}
		break;
	case eCmd_Switch:
		{
			CAppUtils::Switch(selectedLeafs[0]->GetRefName());
		}
		break;
	case eCmd_Rename:
		{
			POSITION pos = m_ListRefLeafs.GetFirstSelectedItemPosition();
			if(pos != NULL)
				m_ListRefLeafs.EditLabel(m_ListRefLeafs.GetNextSelectedItem(pos));
		}
		break;
	case eCmd_AddRemote:
		{
			CAddRemoteDlg(this).DoModal();
			Refresh();
		}
		break;
	case eCmd_ManageRemotes:
		{
			CSinglePropSheetDlg(CString(MAKEINTRESOURCE(IDS_PROCS_TITLE_GITREMOTESETTINGS)), new CSettingGitRemote(g_Git.m_CurrentDir), this).DoModal();
//			CSettingGitRemote W_Remotes(m_cmdPath);
//			W_Remotes.DoModal();
			Refresh();
		}
		break;
	case eCmd_CreateBranch:
		{
			CString *commitHash = NULL;
			if (selectedLeafs.size() == 1)
				commitHash = &(selectedLeafs[0]->m_csRefHash);
			CAppUtils::CreateBranchTag(false, commitHash);
			Refresh();
		}
		break;
	case eCmd_CreateTag:
		{
			CAppUtils::CreateBranchTag(true);
			Refresh();
		}
		break;
	case eCmd_Diff:
		{
			CFileDiffDlg dlg;
			dlg.SetDiff(
				NULL,
				selectedLeafs[0]->m_csRefHash,
				selectedLeafs[1]->m_csRefHash);
			dlg.DoModal();
		}
		break;
	case eCmd_EditBranchDescription:
		{
			CInputDlg dlg;
			dlg.m_sHintText = CString(MAKEINTRESOURCE(IDS_PROC_BROWSEREFS_EDITDESCRIPTION));
			dlg.m_sInputText = selectedLeafs[0]->m_csDescription;
			dlg.m_sTitle = CString(MAKEINTRESOURCE(IDS_PROC_BROWSEREFS_EDITDESCRIPTION));
			dlg.m_bUseLogWidth = true;
			if(dlg.DoModal() == IDOK)
			{
				CString key;
				key.Format(_T("branch.%s.description"), selectedLeafs[0]->m_csRefName);
				dlg.m_sInputText.Replace(_T("\r"), _T(""));
				dlg.m_sInputText.Trim();
				if (dlg.m_sInputText.IsEmpty())
					g_Git.UnsetConfigValue(key);
				else
					g_Git.SetConfigValue(key, dlg.m_sInputText);
				Refresh();
			}
		}
		break;
	}
}