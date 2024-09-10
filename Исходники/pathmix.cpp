bool TestCurrentDirectory(const wchar_t *TestDir)
{
	string strCurDir;

	if (apiGetCurrentDirectory(strCurDir) && !StrCmpI(strCurDir,TestDir))
		return true;

	return false;
}