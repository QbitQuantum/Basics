bool ShowOpenFileDialog(char* FileName, int FileNameLength, char* filter)
// Open a dialog for selecting a file and returns true if succeeded with the name of the file in the preallocated buffer <FileName>
{
    OPENFILENAMEA ofn ;

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = GetActiveWindow(); 
    ofn.lpstrDefExt = 0;
    FileName[0] = '\0';
	ofn.lpstrFile = FileName;
    ofn.nMaxFile = FileNameLength;
    ofn.lpstrFilter = filter; 
    ofn.nFilterIndex = 1;
    char strAux[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, strAux);
	ofn.lpstrInitialDir = strAux;
    ofn.lpstrTitle = LPSTR("Open File");
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_ENABLESIZING;

    GetOpenFileNameA(&ofn);

    if (strlen(ofn.lpstrFile) == 0) return false;
    return true;
} // ShowOpenFileDialog