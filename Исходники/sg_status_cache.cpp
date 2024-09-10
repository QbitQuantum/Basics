void sg_treediff_cache::NotifyExplorerToRefreshPath(SG_context * pCtx, wxFileName path, bool bSpecific)
{
	SG_string * pstrFullPath = NULL;
	wxString fullName = path.GetFullName();

	SG_ERR_CHECK(  SG_STRING__ALLOC__SZ(pCtx, &pstrFullPath, path.GetFullPath().ToUTF8())  );

	//Use %s to handle getting a path that has a %s in it.
	//SG_ERR_CHECK(  SG_UTF8__INTERN_FROM_OS_BUFFER(pCtx, pstrFullPath, path.GetFullPath().ToStdWstring())  );
	//SG_log__report_verbose(pCtx, "FS_CHANGE(%s):	%s", (const char *)ExplainAction(dwAction), SG_string__sz(pstrFullPath)); 

	{
		clearCache(pCtx); 
		if (!m_bIsWin7) //if we're running on XP or Vista
		{
			wxCriticalSectionLocker lock(m_notify_critical_section);
			m_bHaveGottenNewFileChanges = true;
			//For some reason, on XP and Vista, we need to notify for every folder up to the root.
			if (path.FileExists() || path.DirExists())
			{
				if (m_aPathsToNotify.Index(path.GetFullPath()) == wxNOT_FOUND)
					m_aPathsToNotify.Add(path.GetFullPath());
			}

			wxFileName currentDir = wxFileName::DirName(path.GetPath(wxPATH_GET_VOLUME));
			wxFileName topDir = GetTopDir();
			//currentDir = topDir;
			
			while (topDir.GetDirCount() < currentDir.GetDirCount())
			{
				if (m_aPathsToNotify.Index(currentDir.GetFullPath()) == wxNOT_FOUND)
					m_aPathsToNotify.Add(currentDir.GetFullPath());
				currentDir.RemoveLastDir();
			}
		}
		else
		{
			wxCriticalSectionLocker lock(m_notify_critical_section);
			m_bHaveGottenNewFileChanges = true;
			//On Win 7, just notifying for the top of the working folder 
			//will cause a recursive refresh down the tree.
			if (m_aPathsToNotify.Index(GetTopDir().GetFullPath()) == wxNOT_FOUND)
				m_aPathsToNotify.Add(GetTopDir().GetFullPath());
			if (bSpecific)
				m_aPathsToNotify.Add(path.GetFullPath());
		}
	}
fail:
	return;
}