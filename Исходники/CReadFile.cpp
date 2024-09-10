//! opens the file
void CReadFile::openFile()
{
	if (Filename.size() == 0) // bugfix posted by rt
	{
		File = 0;
		return;
	}

#if defined ( _IRR_WCHAR_FILESYSTEM )
	File = _wfopen(Filename.c_str(), L"rb");
#else
	File = fopen(Filename.c_str(), "rb");
#endif

	if (File)
	{
		// get FileSize

		fseek(File, 0, SEEK_END);
		FileSize = getPos();
		fseek(File, 0, SEEK_SET);
	}
}