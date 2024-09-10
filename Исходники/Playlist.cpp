void Playlist::AddDir(Bool do_recurse)
{
	BROWSEINFO brw;
	LPMALLOC pMalloc;
	LPITEMIDLIST ret;
	char dir[MAX_PATH];

	Bool res = GF_FALSE;
	if (NOERROR == ::SHGetMalloc(&pMalloc) ) {
		memset(&brw, 0, sizeof(BROWSEINFO));
		brw.hwndOwner = this->GetSafeHwnd();
		brw.pszDisplayName = dir;
		brw.lpszTitle = "Select Directory...";
		brw.ulFlags = 0L;
		brw.lpfn = LocCbck;

		ret = SHBrowseForFolder(&brw);
		if (ret != NULL) {
			if (::SHGetPathFromIDList(ret, dir)) res = GF_TRUE;
			pMalloc->Free(ret);
		}
		pMalloc->Release();
	}
	if (!res) return;
	strcpy(szCacheDir, dir);

	gf_enum_directory(dir, GF_FALSE, pl_enum_dir_item, this, NULL);
	if (do_recurse) gf_enum_directory(dir, GF_FALSE, pl_enum_dir_dirs, this, NULL);
	m_all_dead_entries=-1;
	RefreshList();
}