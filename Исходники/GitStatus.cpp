git_revnum_t GitStatus::GetStatus(const CTGitPath& path, bool update /* = false */, bool noignore /* = false */, bool /*noexternals*/ /* = false */)
{
	// NOTE: unlike the SVN version this one does not cache the enumerated files, because in practice no code in all of
	//       Tortoise uses this, all places that call GetStatus create a temp GitStatus object which gets destroyed right
	//       after the call again

//	apr_hash_t *				statushash;
//	apr_hash_t *				exthash;
//	apr_array_header_t *		statusarray;
//	const sort_item*			item;

//	git_error_clear(m_err);
//	statushash = apr_hash_make(m_pool);
//	exthash = apr_hash_make(m_pool);
	git_revnum_t youngest = GIT_INVALID_REVNUM;
//	git_opt_revision_t rev;
//	rev.kind = git_opt_revision_unspecified;

	CString sProjectRoot;
	if ( !path.HasAdminDir(&sProjectRoot) )
		return youngest;

	struct hashbaton_t hashbaton;
//	hashbaton.hash = statushash;
//	hashbaton.exthash = exthash;
	hashbaton.pThis = this;

	bool isfull = ((DWORD)CRegStdDWORD(_T("Software\\TortoiseGit\\CacheType"),
				GetSystemMetrics(SM_REMOTESESSION) ? ShellCache::dll : ShellCache::exe) == ShellCache::dllFull);

	{
		LPCTSTR lpszSubPath = NULL;
		CString sSubPath;
		CString s = path.GetWinPathString();
		if (s.GetLength() > sProjectRoot.GetLength())
		{
			sSubPath = s.Right(s.GetLength() - sProjectRoot.GetLength());
			lpszSubPath = sSubPath;
			// skip initial slash if necessary
			if (*lpszSubPath == _T('\\'))
				lpszSubPath++;
		}

		m_status.prop_status = m_status.text_status = git_wc_status_none;

		if(path.IsDirectory())
		{
			m_err = GetDirStatus(sProjectRoot,CString(lpszSubPath),&m_status.text_status , isfull, false,!noignore, NULL, NULL);

		}
		else
		{
			m_err = GetFileStatus(sProjectRoot,CString(lpszSubPath),&m_status.text_status ,isfull, false,!noignore, NULL,NULL);
		}
	}

	// Error present if function is not under version control
	if (m_err) /*|| (apr_hash_count(statushash) == 0)*/
	{
		status = NULL;
		return GIT_INVALID_REVNUM;
	}

	// Convert the unordered hash to an ordered, sorted array
	/*statusarray = sort_hash (statushash,
							  sort_compare_items_as_paths,
							  m_pool);*/

	// only the first entry is needed (no recurse)
//	item = &APR_ARRAY_IDX (statusarray, 0, const sort_item);

//	status = (git_wc_status2_t *) item->value;
	status = &m_status;

	if (update)
	{
		// done to match TSVN functionality of this function (not sure if any code uses the reutrn val)
		// if TGit does not need this, then change the return type of function
		youngest = g_Git.GetHash(_T("HEAD"));
	}

	return youngest;
}