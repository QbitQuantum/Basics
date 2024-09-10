static void kill_fsdb (a_inode *dir)
{
	if (!dir->nname)
		return;
  TCHAR *n = build_nname (dir->nname, FSDB_FILE);
  _wunlink (n);
  xfree (n);
}