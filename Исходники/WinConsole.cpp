void WinConsole::ShowInExplorer(const char* filename)
{
	BString<1024> fileName2 = filename;
	FileSystem::NormalizePathSeparators(fileName2);

	if (!FileSystem::FileExists(fileName2) && !FileSystem::DirectoryExists(fileName2))
	{
		BString<1024> message("Directory or file %s doesn't exist (yet).", *fileName2);
		MessageBox(m_trayWindow, message, "Information", MB_ICONINFORMATION);
		return;
	}

	WString wideFilename = FileSystem::UtfPathToWidePath(fileName2);

	CoInitialize(nullptr);
	LPITEMIDLIST pidl;
	HRESULT H = SHParseDisplayName(wideFilename, nullptr, &pidl, 0, nullptr);
	H = SHOpenFolderAndSelectItems(pidl, 0, 0, 0);
}