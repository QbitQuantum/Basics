/**
 * Loads a string from the EXE/DLL/etc.'s string table. If that fails, copies
 * the default string.
 * @param res The ID of the string resource to read.
 * @param def The default string.
 * @param buf Buffer into which to store the string.
 * @param bufsize Size of buf (in units of wchar_t).
 */
static void xlate(unsigned int res, const wchar_t *def, wchar_t *buf, size_t bufsize)
{
	HMODULE inst;
	GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL, &inst);

	if (LoadStringW(inst, res, buf, bufsize) == 0)
	{
		wcsncpy(buf, def, bufsize);
		buf[bufsize-1] = '\0';
	}
}