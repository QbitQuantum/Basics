int _rename(const char *oldname, const char *newname)
{
	wchar_t *wold, *wnew;
	BOOL rc;

	wold = wce_mbtowc(oldname);
	wnew = wce_mbtowc(newname);

	/* replace with MoveFile. */
	rc = MoveFileW(wold, wnew);

	free(wold);
	free(wnew);

	return rc==TRUE ? 0 : -1;
}