std::vector<std::string> *listFilesDir(const char* dir) {
    WIN32_FIND_DATAA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	char szDir[MAX_PATH];
    int arg_length;
	std::vector<std::string> *files_dir = new std::vector<std::string>();
    
    arg_length= (int)strlen(dir);

    if (arg_length > (MAX_PATH - 3))
        return files_dir;

    StringCchCopyA(szDir, MAX_PATH, dir);
    StringCchCatA(szDir, MAX_PATH, "\\*");

    hFind = FindFirstFileA(szDir, &ffd);

    if (INVALID_HANDLE_VALUE == hFind)
        return files_dir;
        
    do {
         files_dir->push_back(ffd.cFileName);
    } while (FindNextFileA(hFind, &ffd) != 0);
    
    FindClose(hFind);
    return files_dir;
}