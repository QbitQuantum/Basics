int wmain(int argc, WCHAR* argv[])
{
	if (argc != 2)
		return 0;

	WinFile File, OutFile;
	ULONG  InSize;
	PBYTE  InBuffer = nullptr;
	WCHAR  lpFileName[MAX_PATH] = { 0 };

	do
	{
		if (FAILED(File.Open(argv[1], WinFile::FileRead)))
			break;

		InSize = File.GetSize32();
		InBuffer = (PBYTE)GlobalAlloc(0, InSize);
		if (!InBuffer)
			break;

		File.Read(InBuffer, InSize);
		wsprintfW(lpFileName, L"%s.bmp", argv[1]);
		GetBMPData(InBuffer);

		if (FAILED(OutFile.Open(lpFileName, WinFile::FileWrite)))
			break;

		OutFile.Write(InBuffer, InSize);
		OutFile.Release();

	} while (0);

	if (InBuffer)
		GlobalFree(InBuffer);

	File.Release();
	return 0;
}