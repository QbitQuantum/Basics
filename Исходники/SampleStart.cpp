std::string GetFilename()
{
#ifdef CPUT_OS_WINDOWS
    OPENFILENAMEA filename;
    CHAR file[MAX_PATH];
    ZeroMemory(file, sizeof(file));
    ZeroMemory(&filename, sizeof(OPENFILENAME));
    filename.lStructSize = sizeof(OPENFILENAME);
    filename.lpstrFile = file;
    filename.nMaxFile = MAX_PATH;
    filename.lpstrFilter = "*.scene\0\0";
    filename.nFilterIndex = 1;
    filename.lpstrInitialDir = NULL;
    filename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    GetOpenFileNameA(&filename);
    return std::string(filename.lpstrFile);
#else
    return std::string("");
#endif
}