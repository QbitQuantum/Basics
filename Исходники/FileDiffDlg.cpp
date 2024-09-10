void CFileDiffDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if ((pWnd==0)||(pWnd != &m_cFileList))
		return;
	if (m_cFileList.GetSelectedCount() == 0)
		return;
	// if the context menu is invoked through the keyboard, we have to use
	// a calculated position on where to anchor the menu on
	if ((point.x == -1) && (point.y == -1))
	{
		CRect rect;
		m_cFileList.GetItemRect(m_cFileList.GetSelectionMark(), &rect, LVIR_LABEL);
		m_cFileList.ClientToScreen(&rect);
		point = rect.CenterPoint();
	}
	CIconMenu popup;
	if (popup.CreatePopupMenu())
	{
		popup.AppendMenuIcon(ID_COMPARE, IDS_LOG_POPUP_COMPARETWO, IDI_DIFF);
		popup.AppendMenuIcon(ID_BLAME, IDS_FILEDIFF_POPBLAME, IDI_BLAME);
		popup.AppendMenuIcon(ID_LOG, IDS_FILEDIFF_LOG, IDI_LOG);
		popup.AppendMenu(MF_SEPARATOR, NULL);
		popup.AppendMenuIcon(ID_EXPORT, IDS_FILEDIFF_POPEXPORT, IDI_EXPORT);
		popup.AppendMenu(MF_SEPARATOR, NULL);
		popup.AppendMenuIcon(ID_SAVEAS, IDS_FILEDIFF_POPSAVELIST, IDI_SAVEAS);
		popup.AppendMenuIcon(ID_CLIPBOARD_PATH, IDS_STATUSLIST_CONTEXT_COPY, IDI_COPYCLIP);
		popup.AppendMenuIcon(ID_CLIPBOARD_ALL, IDS_STATUSLIST_CONTEXT_COPYEXT, IDI_COPYCLIP);

		int cmd = popup.TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN | TPM_NONOTIFY, point.x, point.y, this, 0);
		m_bCancelled = false;
		switch (cmd)
		{
		case ID_COMPARE:
			{
				POSITION pos = m_cFileList.GetFirstSelectedItemPosition();
				while (pos)
				{
					int index = m_cFileList.GetNextSelectedItem(pos);
					DoDiff(index, false);
				}
			}
			break;
		case ID_BLAME:
			{
				POSITION pos = m_cFileList.GetFirstSelectedItemPosition();
				while (pos)
				{
					int index = m_cFileList.GetNextSelectedItem(pos);
					CAppUtils::LaunchTortoiseBlame(m_arFilteredList[index]->GetWinPathString(), m_rev1.m_CommitHash.ToString());
				}
			}
			break;
		case ID_LOG:
			{
				POSITION pos = m_cFileList.GetFirstSelectedItemPosition();
				while (pos)
				{
					int index = m_cFileList.GetNextSelectedItem(pos);
					CString cmd = _T("/command:log");
					cmd += _T(" /path:\"")+m_arFilteredList[index]->GetWinPathString()+_T("\" ");
					cmd += _T(" /endrev:")+m_rev1.m_CommitHash.ToString();
					CAppUtils::RunTortoiseProc(cmd);
				}
			}
			break;
		case ID_SAVEAS:
			{
				if (m_cFileList.GetSelectedCount() > 0)
				{
					CString temp;
					CTGitPath savePath;
					CString pathSave;
					if (!CAppUtils::FileOpenSave(pathSave, NULL, IDS_REPOBROWSE_SAVEAS, IDS_COMMONFILEFILTER, false, m_hWnd))
					{
						break;
					}
					savePath = CTGitPath(pathSave);

					// now open the selected file for writing
					try
					{
						CStdioFile file(savePath.GetWinPathString(), CFile::typeBinary | CFile::modeReadWrite | CFile::modeCreate);
//						temp.Format(IDS_FILEDIFF_CHANGEDLISTINTRO, (LPCTSTR)m_path1.GetGitPathString(), (LPCTSTR)m_rev1.ToString(), (LPCTSTR)m_path2.GetGitPathString(), (LPCTSTR)m_rev2.ToString());
						file.WriteString(temp + _T("\n"));
						POSITION pos = m_cFileList.GetFirstSelectedItemPosition();
						while (pos)
						{
							int index = m_cFileList.GetNextSelectedItem(pos);
							CTGitPath* fd = m_arFilteredList[index];
							file.WriteString(fd->GetGitPathString());
							file.WriteString(_T("\n"));
						}
						file.Close();
					}
					catch (CFileException* pE)
					{
						pE->ReportError();
					}
				}
			}
			break;
		case ID_CLIPBOARD_PATH:
			{
				CopySelectionToClipboard();
			}
			break;

		case ID_CLIPBOARD_ALL:
			{
				CopySelectionToClipboard(TRUE);
			}
			break;
		case ID_EXPORT:
			{
				// export all changed files to a folder
				CBrowseFolder browseFolder;
				browseFolder.m_style = BIF_EDITBOX | BIF_NEWDIALOGSTYLE | BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
				if (browseFolder.Show(GetSafeHwnd(), m_strExportDir) == CBrowseFolder::OK)
				{
					POSITION pos = m_cFileList.GetFirstSelectedItemPosition();
					while (pos)
					{
						int index = m_cFileList.GetNextSelectedItem(pos);
						CTGitPath* fd = m_arFilteredList[index];
						// we cannot export directories or folders
						if (fd->m_Action == CTGitPath::LOGACTIONS_DELETED || fd->IsDirectory())
							continue;
						CAppUtils::CreateMultipleDirectory(m_strExportDir + _T("\\") + fd->GetDirectory().GetWinPathString());
						CString filename = m_strExportDir + _T("\\") + fd->GetWinPathString();
						if(m_rev1.m_CommitHash.ToString() == GIT_REV_ZERO)
						{
							if(!CopyFile(g_Git.m_CurrentDir + _T("\\") + fd->GetWinPath(), filename, false))
							{
								MessageBox(CFormatMessageWrapper(), _T("TortoiseGit"), MB_OK | MB_ICONERROR);
								return;
							}
						}
						else
						{
							if(g_Git.GetOneFile(m_rev1.m_CommitHash, *fd, filename))
							{
								CString out;
								out.Format(_T("Fail checkout one file %s;%s"), m_rev1.m_CommitHash.ToString(), fd->GetWinPath());
								CMessageBox::Show(NULL, out, _T("TortoiseGit"), MB_OK);
								return;
							}
						}
					}
				}
			}

			break;

		}
	}
}