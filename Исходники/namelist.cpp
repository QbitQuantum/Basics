void NamesList::SetCurDir(const wchar_t *Dir)
{
	if (StrCmpI(strCurrentDir,Dir) || !TestCurrentDirectory(Dir))
	{
		strCurrentDir = Dir;
		PrepareDiskPath(strCurrentDir);
	}
}