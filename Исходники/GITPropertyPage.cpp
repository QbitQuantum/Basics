void CGitPropertyPage::InitWorkfileView()
{
	if (filenames.empty())
		return;

	CTGitPath path(filenames.front().c_str());

	CString ProjectTopDir;
	if(!path.HasAdminDir(&ProjectTopDir))
		return;

	CAutoRepository repository(CUnicodeUtils::GetUTF8(ProjectTopDir));
	if (!repository)
		return;

	CString username;
	CString useremail;
	CString autocrlf;
	CString safecrlf;

	CAutoConfig config(repository);
	if (config)
	{
		config.GetString(L"user.name", username);
		config.GetString(L"user.email", useremail);
		config.GetString(L"core.autocrlf", autocrlf);
		config.GetString(L"core.safecrlf", safecrlf);
	}

	CString branch;
	CString remotebranch;
	if (!git_repository_head_detached(repository))
	{
		CAutoReference head;
		if (git_repository_head_unborn(repository))
		{
			git_reference_lookup(head.GetPointer(), repository, "HEAD");
			branch = CUnicodeUtils::GetUnicode(git_reference_symbolic_target(head));
			if (branch.Find(_T("refs/heads/")) == 0)
				branch = branch.Mid(11); // 11 = len("refs/heads/")
		}
		else if (!git_repository_head(head.GetPointer(), repository))
		{
			const char * branchChar = git_reference_shorthand(head);
			branch = CUnicodeUtils::GetUnicode(branchChar);

			const char * branchFullChar = git_reference_name(head);
			CAutoBuf upstreambranchname;
			if (!git_branch_upstream_name(upstreambranchname, repository, branchFullChar))
			{
				remotebranch = CUnicodeUtils::GetUnicode(CStringA(upstreambranchname->ptr, (int)upstreambranchname->size));
				remotebranch = remotebranch.Mid(13); // 13=len("refs/remotes/")
			}
		}
	}
	else
		branch = _T("detached HEAD");

	if (autocrlf.Trim().IsEmpty())
		autocrlf = _T("false");
	if (safecrlf.Trim().IsEmpty())
		safecrlf = _T("false");

	SetDlgItemText(m_hwnd,IDC_CONFIG_USERNAME,username.Trim());
	SetDlgItemText(m_hwnd,IDC_CONFIG_USEREMAIL,useremail.Trim());
	SetDlgItemText(m_hwnd,IDC_CONFIG_AUTOCRLF,autocrlf.Trim());
	SetDlgItemText(m_hwnd,IDC_CONFIG_SAFECRLF,safecrlf.Trim());

	SetDlgItemText(m_hwnd,IDC_SHELL_CURRENT_BRANCH,branch.Trim());
	SetDlgItemText(m_hwnd,IDC_SHELL_REMOTE_BRANCH, remotebranch);

	git_oid oid;
	CAutoCommit HEADcommit;
	if (!git_reference_name_to_id(&oid, repository, "HEAD") && !git_commit_lookup(HEADcommit.GetPointer(), repository, &oid) && HEADcommit)
		DisplayCommit(HEADcommit, IDC_HEAD_HASH, IDC_HEAD_SUBJECT, IDC_HEAD_AUTHOR, IDC_HEAD_DATE);

	{
		int stripLength = ProjectTopDir.GetLength();
		if (ProjectTopDir[stripLength - 1] != _T('\\'))
			++stripLength;

		bool allAreFiles = true;
		for (auto it = filenames.cbegin(); it < filenames.cend(); ++it)
		{
			if (PathIsDirectory(it->c_str()))
			{
				allAreFiles = false;
				break;
			}
		}
		if (allAreFiles)
		{
			size_t assumevalid = 0;
			size_t skipworktree = 0;
			size_t executable = 0;
			size_t symlink = 0;
			do
			{
				CAutoIndex index;
				if (git_repository_index(index.GetPointer(), repository))
					break;

				for (auto it = filenames.cbegin(); it < filenames.cend(); ++it)
				{
					CTGitPath file;
					file.SetFromWin(CString(it->c_str()).Mid(stripLength));
					CStringA pathA = CUnicodeUtils::GetMulti(file.GetGitPathString(), CP_UTF8);
					size_t idx;
					if (!git_index_find(&idx, index, pathA))
					{
						const git_index_entry *e = git_index_get_byindex(index, idx);

						if (e->flags & GIT_IDXENTRY_VALID)
							++assumevalid;

						if (e->flags_extended & GIT_IDXENTRY_SKIP_WORKTREE)
							++skipworktree;

						if (e->mode & 0111)
							++executable;

						if ((e->mode & GIT_FILEMODE_LINK) == GIT_FILEMODE_LINK)
							++symlink;
					}
					else
					{
						// do not show checkboxes for unversioned files
						ShowWindow(GetDlgItem(m_hwnd, IDC_ASSUMEVALID), SW_HIDE);
						ShowWindow(GetDlgItem(m_hwnd, IDC_SKIPWORKTREE), SW_HIDE);
						ShowWindow(GetDlgItem(m_hwnd, IDC_EXECUTABLE), SW_HIDE);
						ShowWindow(GetDlgItem(m_hwnd, IDC_SYMLINK), SW_HIDE);
						break;
					}
				}
			} while (0);

			if (assumevalid != 0 && assumevalid != filenames.size())
			{
				SendMessage(GetDlgItem(m_hwnd, IDC_ASSUMEVALID), BM_SETSTYLE, (DWORD)GetWindowLong(GetDlgItem(m_hwnd, IDC_ASSUMEVALID), GWL_STYLE) & ~BS_AUTOCHECKBOX | BS_AUTO3STATE, 0);
				SendMessage(GetDlgItem(m_hwnd, IDC_ASSUMEVALID), BM_SETCHECK, BST_INDETERMINATE, 0);
			}
			else
				SendMessage(GetDlgItem(m_hwnd, IDC_ASSUMEVALID), BM_SETCHECK, (assumevalid == 0) ? BST_UNCHECKED : BST_CHECKED, 0);

			if (skipworktree != 0 && skipworktree != filenames.size())
			{
				SendMessage(GetDlgItem(m_hwnd, IDC_SKIPWORKTREE), BM_SETSTYLE, (DWORD)GetWindowLong(GetDlgItem(m_hwnd, IDC_SKIPWORKTREE), GWL_STYLE) & ~BS_AUTOCHECKBOX | BS_AUTO3STATE, 0);
				SendMessage(GetDlgItem(m_hwnd, IDC_SKIPWORKTREE), BM_SETCHECK, BST_INDETERMINATE, 0);
			}
			else
				SendMessage(GetDlgItem(m_hwnd, IDC_SKIPWORKTREE), BM_SETCHECK, (skipworktree == 0) ? BST_UNCHECKED : BST_CHECKED, 0);

			if (executable != 0 && executable != filenames.size())
			{
				SendMessage(GetDlgItem(m_hwnd, IDC_EXECUTABLE), BM_SETSTYLE, (DWORD)GetWindowLong(GetDlgItem(m_hwnd, IDC_EXECUTABLE), GWL_STYLE) & ~BS_AUTOCHECKBOX | BS_AUTO3STATE, 0);
				SendMessage(GetDlgItem(m_hwnd, IDC_EXECUTABLE), BM_SETCHECK, BST_INDETERMINATE, 0);
				EnableWindow(GetDlgItem(m_hwnd, IDC_SYMLINK), TRUE);
			}
			else
			{
				SendMessage(GetDlgItem(m_hwnd, IDC_EXECUTABLE), BM_SETCHECK, (executable == 0) ? BST_UNCHECKED : BST_CHECKED, 0);
				EnableWindow(GetDlgItem(m_hwnd, IDC_SYMLINK), (executable == 0) ? TRUE : FALSE);
			}

			if (symlink != 0 && symlink != filenames.size())
			{
				SendMessage(GetDlgItem(m_hwnd, IDC_SYMLINK), BM_SETSTYLE, (DWORD)GetWindowLong(GetDlgItem(m_hwnd, IDC_SYMLINK), GWL_STYLE) & ~BS_AUTOCHECKBOX | BS_AUTO3STATE, 0);
				SendMessage(GetDlgItem(m_hwnd, IDC_SYMLINK), BM_SETCHECK, BST_INDETERMINATE, 0);
				EnableWindow(GetDlgItem(m_hwnd, IDC_EXECUTABLE), TRUE);
			}
			else
			{
				SendMessage(GetDlgItem(m_hwnd, IDC_SYMLINK), BM_SETCHECK, (symlink == 0) ? BST_UNCHECKED : BST_CHECKED, 0);
				EnableWindow(GetDlgItem(m_hwnd, IDC_EXECUTABLE), (symlink == 0) ? TRUE : FALSE);
			}
		}
		else
		{
			ShowWindow(GetDlgItem(m_hwnd, IDC_ASSUMEVALID), SW_HIDE);
			ShowWindow(GetDlgItem(m_hwnd, IDC_SKIPWORKTREE), SW_HIDE);
			ShowWindow(GetDlgItem(m_hwnd, IDC_EXECUTABLE), SW_HIDE);
			ShowWindow(GetDlgItem(m_hwnd, IDC_SYMLINK), SW_HIDE);
		}
	}

	if (filenames.size() == 1 && !PathIsDirectory(filenames[0].c_str()))
	{
		SetDlgItemText(m_hwnd, IDC_LAST_SUBJECT, CString(MAKEINTRESOURCE(IDS_LOADING)));
		_beginthread(LogThreadEntry, 0, this);
	}
	else
		ShowWindow(GetDlgItem(m_hwnd, IDC_STATIC_LASTMODIFIED), SW_HIDE);
}