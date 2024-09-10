/******************************************************************
 * my_rename
 ******************************************************************/
int my_rename (const TCHAR *oldname, const TCHAR *newname) {

  LONG res;
	char cmd[255];

  DebOut("oldname: %s newname %s\n", oldname, newname);

  res=Rename(oldname, newname);

  if(res==DOSTRUE) {
    return 0;
  }

  /* ugly hack, as windows rename can move over filesystem borders,
	 * but AROS rename can't. And there seems to be no simple
	 * API to move a file across filesystem borders...
	 * So we use the shell and hope for the best..
	 */
	DebOut("rename failed, try shell copy..\n");
	sprintf(cmd, "c:copy from %s to %s MOVE QUIET >NIL:", oldname, newname);

	DebOut("execute: %s\n", cmd);
	Execute(cmd, NULL, NULL);

	if(fsdb_exists(newname)) {
    /* there is a file, pray, it is the one we copied ;) */
		return 0;
  }

  SetLastError(IoErr());
  DebOut("return -1 (%d)\n", IoErr());
  return -1;
}