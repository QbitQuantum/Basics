static void fixtarname(char *tptr, const char *fp, size_t l)
{
	/* add a '.' to start of file name, convert from ugly dos \'s in path
	 * to lovely unix /'s :-} */
	*tptr++='.';
	l--;

	StrnCpy(tptr, fp, l-1);
	string_replace(tptr, '\\', '/');
}