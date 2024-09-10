STDMETHODIMP CShellExt::IsMemberOf(LPCWSTR pwszPath, DWORD /*dwAttrib*/)
{
	PreserveChdir preserveChdir;
	git_wc_status_kind status = git_wc_status_none;
	bool readonlyoverlay = false;
	bool lockedoverlay = false;
	if (pwszPath == NULL)
		return S_FALSE;
	const TCHAR* pPath = pwszPath;

	// the shell sometimes asks overlays for invalid paths, e.g. for network
	// printers (in that case the path is "0", at least for me here).
	if (_tcslen(pPath)<2)
		return S_FALSE;
	// since the shell calls each and every overlay handler with the same filepath
	// we use a small 'fast' cache of just one path here.
	// To make sure that cache expires, clear it as soon as one handler is used.

	AutoLocker lock(g_csGlobalCOMGuard);
	if (_tcscmp(pPath, g_filepath.c_str())==0)
	{
		status = g_filestatus;
		readonlyoverlay = g_readonlyoverlay;
		lockedoverlay = g_lockedoverlay;
	}
	else
	{
		if (!g_ShellCache.IsPathAllowed(pPath))
		{
			int drivenumber = -1;
			if ((m_State == FileStateVersioned) && g_ShellCache.ShowExcludedAsNormal() &&
				((drivenumber=PathGetDriveNumber(pPath))!=0)&&(drivenumber!=1) &&
				PathIsDirectory(pPath) && g_ShellCache.HasSVNAdminDir(pPath, true))
			{
				return S_OK;
			}
			return S_FALSE;
		}

		switch (g_ShellCache.GetCacheType())
		{
		case ShellCache::exe:
			{
				CTGitPath tpath(pPath);
				if(!tpath.HasAdminDir())
				{
					status = git_wc_status_none;
					break;
				}
				if(tpath.IsAdminDir())
				{
					status = git_wc_status_none;
					break;
				}
				TSVNCacheResponse itemStatus;
				SecureZeroMemory(&itemStatus, sizeof(itemStatus));
				if (m_remoteCacheLink.GetStatusFromRemoteCache(tpath, &itemStatus, true))
				{
					status = GitStatus::GetMoreImportant(itemStatus.m_status.text_status, itemStatus.m_status.prop_status);
/*					if ((itemStatus.m_kind == git_node_file)&&(status == git_wc_status_normal)&&((itemStatus.m_needslock && itemStatus.m_owner[0]==0)||(itemStatus.m_readonly)))
						readonlyoverlay = true;
					if (itemStatus.m_owner[0]!=0)
						lockedoverlay = true;*/
				}
			}
			break;
		case ShellCache::dll:
		case ShellCache::dllFull:
			{
				// Look in our caches for this item
				const FileStatusCacheEntry * s = m_CachedStatus.GetCachedItem(CTGitPath(pPath));
				if (s)
				{
					status = s->status;
				}
				else
				{
					// No cached status available

					// since the dwAttrib param of the IsMemberOf() function does not
					// have the SFGAO_FOLDER flag set at all (it's 0 for files and folders!)
					// we have to check if the path is a folder ourselves :(
					if (PathIsDirectory(pPath))
					{
						if (g_ShellCache.HasSVNAdminDir(pPath, TRUE))
						{
							if ((!g_ShellCache.IsRecursive()) && (!g_ShellCache.IsFolderOverlay()))
							{
								status = git_wc_status_normal;
							}
							else
							{
								const FileStatusCacheEntry * s = m_CachedStatus.GetFullStatus(CTGitPath(pPath), TRUE);
								status = s->status;
								// GitFolderStatus does not list unversioned files/dir so they would always end up as normal below
								// so let's assume file/dir is unversioned if not found in cache
								/*// sub-dirs that are empty (or contain no versioned files) are reported as unversioned (and should be kept as such)
								if (status != git_wc_status_unversioned)
								{
									// if get status fails then display status as 'normal' on folder (since it contains .git)
									// TODO: works for svn since each folder has .svn, not sure if git needs additinoal processing
									status = GitStatus::GetMoreImportant(git_wc_status_normal, status);
								}*/
							}
						}
						else
						{
							status = git_wc_status_none;
						}
					}
					else
					{
						const FileStatusCacheEntry * s = m_CachedStatus.GetFullStatus(CTGitPath(pPath), FALSE);
						status = s->status;
					}
				}
#if 0
				if ((s)&&(status == git_wc_status_normal)&&(s->needslock)&&(s->owner[0]==0))
					readonlyoverlay = true;
				if ((s)&&(s->owner[0]!=0))
					lockedoverlay = true;
#endif
			}

			break;
		default:
		case ShellCache::none:
			{
				// no cache means we only show a 'versioned' overlay on folders
				// with an admin directory
				if (PathIsDirectory(pPath))
				{
					if (g_ShellCache.HasSVNAdminDir(pPath, TRUE))
					{
						status = git_wc_status_normal;
					}
					else
					{
						status = git_wc_status_none;
					}
				}
				else
				{
					status = git_wc_status_none;
				}
			}
			break;
		}
		ATLTRACE(_T("Status %d for file %s\n"), status, pwszPath);
	}
	g_filepath.clear();
	g_filepath = pPath;
	g_filestatus = status;
	g_readonlyoverlay = readonlyoverlay;
	g_lockedoverlay = lockedoverlay;

	//the priority system of the shell doesn't seem to work as expected (or as I expected):
	//as it seems that if one handler returns S_OK then that handler is used, no matter
	//if other handlers would return S_OK too (they're never called on my machine!)
	//So we return S_OK for ONLY ONE handler!

	switch (status)
	{
		// note: we can show other overlays if due to lack of enough free overlay
		// slots some of our overlays aren't loaded. But we assume that
		// at least the 'normal' and 'modified' overlay are available.
		case git_wc_status_none:
			return S_FALSE;
		case git_wc_status_unversioned:
			if (g_ShellCache.ShowUnversionedOverlay() && g_unversionedovlloaded && (m_State == FileStateUnversionedOverlay))
			{
				g_filepath.clear();
				return S_OK;
			}
			return S_FALSE;
		case git_wc_status_ignored:
			if (g_ShellCache.ShowIgnoredOverlay() && g_ignoredovlloaded && (m_State == FileStateIgnoredOverlay))
			{
				g_filepath.clear();
				return S_OK;
			}
			return S_FALSE;
		case git_wc_status_normal:
		case git_wc_status_external:
		case git_wc_status_incomplete:
			if ((readonlyoverlay)&&(g_readonlyovlloaded))
			{
				if (m_State == FileStateReadOnly)
				{
					g_filepath.clear();
					return S_OK;
				}
				else
					return S_FALSE;
			}
			else if ((lockedoverlay)&&(g_lockedovlloaded))
			{
				if (m_State == FileStateLockedOverlay)
				{
					g_filepath.clear();
					return S_OK;
				}
				else
					return S_FALSE;
			}
			else if (m_State == FileStateVersioned)
			{
				g_filepath.clear();
				return S_OK;
			}
			else
				return S_FALSE;
		case git_wc_status_missing:
		case git_wc_status_deleted:
			if (g_deletedovlloaded)
			{
				if (m_State == FileStateDeleted)
				{
					g_filepath.clear();
					return S_OK;
				}
				else
					return S_FALSE;
			}
			else
			{
				// the 'deleted' overlay isn't available (due to lack of enough
				// overlay slots). So just show the 'modified' overlay instead.
				if (m_State == FileStateModified)
				{
					g_filepath.clear();
					return S_OK;
				}
				else
					return S_FALSE;
			}
		case git_wc_status_replaced:
		case git_wc_status_modified:
			if (m_State == FileStateModified)
			{
				g_filepath.clear();
				return S_OK;
			}
			else
				return S_FALSE;
		case git_wc_status_merged:
			if (m_State == FileStateReadOnly)
			{
				g_filepath.clear();
				return S_OK;
			}
			else
				return S_FALSE;
		case git_wc_status_added:
			if (g_addedovlloaded)
			{
				if (m_State== FileStateAddedOverlay)
				{
					g_filepath.clear();
					return S_OK;
				}
				else
					return S_FALSE;
			}
			else
			{
				// the 'added' overlay isn't available (due to lack of enough
				// overlay slots). So just show the 'modified' overlay instead.
				if (m_State == FileStateModified)
				{
					g_filepath.clear();
					return S_OK;
				}
				else
					return S_FALSE;
			}
		case git_wc_status_conflicted:
		case git_wc_status_obstructed:
			if (g_conflictedovlloaded)
			{
				if (m_State == FileStateConflict)
				{
					g_filepath.clear();
					return S_OK;
				}
				else
					return S_FALSE;
			}
			else
			{
				// the 'conflicted' overlay isn't available (due to lack of enough
				// overlay slots). So just show the 'modified' overlay instead.
				if (m_State == FileStateModified)
				{
					g_filepath.clear();
					return S_OK;
				}
				else
					return S_FALSE;
			}
		default:
			return S_FALSE;
	} // switch (status)
	//return S_FALSE;
}