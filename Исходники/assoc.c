BOOL win_association_exists(const struct win_association_info *assoc)
{
	BOOL rc = FALSE;
	TCHAR buf[1024];
	TCHAR expected[1024];
	HKEY key1 = NULL;
	HKEY key2 = NULL;

	// first check to see if the extension is there at all
	if (RegOpenKey(HKEY_CLASSES_ROOT, A2T(assoc->file_class), &key1))
		goto done;

	if (RegOpenKey(key1, TEXT("shell\\open\\command"), &key2))
		goto done;

	if (reg_query_string(key2, buf, sizeof(buf) / sizeof(buf[0])))
		goto done;

	get_open_command(assoc, expected, sizeof(expected) / sizeof(expected[0]));
	rc = !_tcscmp(expected, buf);

done:
	if (key2)
		RegCloseKey(key2);
	if (key1)
		RegCloseKey(key1);
	return rc;
}