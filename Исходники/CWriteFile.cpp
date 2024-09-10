//! opens the file
void CWriteFile::openFile(bool append)
{
	if (Filename.size() == 0)
	{
		File = 0;
		return;
	}

#if defined(_IRR_WCHAR_FILESYSTEM)
	File = _wfopen(Filename.c_str(), append ? L"ab" : L"wb");
#else
	File = fopen(Filename.c_str(), append ? "ab" : "wb");
#endif

	if (File)
	{
		// get FileSize

		fseek(File, 0, SEEK_END);
		FileSize = ftell(File);
		fseek(File, 0, SEEK_SET);
	}
}