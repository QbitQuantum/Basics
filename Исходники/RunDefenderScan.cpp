bstr_t GetProgramFilesPath()
{
	PWSTR path;

	SHGetKnownFolderPath(GetFolderId(), 0, nullptr, &path);

	bstr_t ret = path;
	CoTaskMemFree(path);

	return ret;
}