//
// OpenWadfile
//
// Provides a common dialog box
// for selecting the desired wad file.
//
static inline VOID OpenWadfile(HWND hDlg)
{
	OPENFILENAMEA ofn;
	CHAR FileBuffer[256] = "";

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.hwndOwner = hDlg;
	ofn.lpstrFilter = "WAD Files\0*.wad\0All Files\0*.*\0\0";
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFile = FileBuffer;
	ofn.lStructSize = sizeof(ofn);
	ofn.nMaxFile = sizeof(FileBuffer);
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	if (GetOpenFileNameA(&ofn))
		ReadWADLumps(FileBuffer, hDlg);
}