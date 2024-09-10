CString GitAdminDir::ReadGitLink(const CString& topDir, const CString& dotGitPath)
{
	CAutoFILE pFile = _wfsopen(dotGitPath, L"r", SH_DENYWR);

	if (!pFile)
		return L"";

	int size = 65536;
	auto buffer = std::make_unique<char[]>(size);
	int length = (int)fread(buffer.get(), sizeof(char), size, pFile);
	CStringA gitPathA(buffer.get(), length);
	if (length < 8 || !CStringUtils::StartsWith(gitPathA, "gitdir: "))
		return L"";
	CString gitPath = CUnicodeUtils::GetUnicode(gitPathA);
	// trim after converting to UTF-16, because CStringA trim does not work when having UTF-8 chars
	gitPath = gitPath.Trim().Mid((int)wcslen(L"gitdir: "));
	gitPath.Replace('/', '\\');
	if (!gitPath.IsEmpty() && gitPath[0] == L'.')
	{
		gitPath = CPathUtils::BuildPathWithPathDelimiter(topDir) + gitPath;
		CString adminDir;
		PathCanonicalize(CStrBuf(adminDir, MAX_PATH), gitPath);
		return adminDir;
	}
	CPathUtils::TrimTrailingPathDelimiter(gitPath);
	return gitPath;
}