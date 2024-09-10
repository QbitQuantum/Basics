std::string getFileName(HWND hWnd, PCHAR lpstrFilter, PCHAR lpstrTitle)
{
	EnableWindow(hWnd, false);
	CHAR szFileName[1000] = { 0 };
	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hInstance = hInst;
	ofn.lpstrFilter = lpstrFilter;
	ofn.lpstrTitle = lpstrTitle;
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = sizeof(szFileName);
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	std::string fileName;
	if (GetOpenFileNameA(&ofn))
		fileName.append(szFileName);
	EnableWindow(hWnd, true);
	SetFocus(hWnd);
	return fileName;
}