bool DirMan::rmAbsPath(const std::string &dirPath)
{
    BOOL ret = TRUE;
    struct DirStackEntry
    {
        std::wstring path;
        HANDLE hFind;
        WIN32_FIND_DATAW data;
    };

    std::stack<DirStackEntry> dirStack;
    DirStackEntry ds;
    ds.hFind = NULL;
    memset(&ds.data, 0, sizeof(WIN32_FIND_DATAW));
    ds.path = Str2WStr(dirPath);
    dirStack.push(ds);

    while(!dirStack.empty())
    {
        DirStackEntry *e = &dirStack.top();
        e->hFind = FindFirstFileW((e->path + L"/*").c_str(), &e->data);
        bool walkUp = false;
        if(e->hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                if((wcscmp(e->data.cFileName, L"..") == 0) || (wcscmp(e->data.cFileName, L".") == 0))
                    continue;
                std::wstring path = e->path + L"/" + e->data.cFileName;

                if((e->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
                {
                    FindClose(e->hFind);
                    ds.path = path;
                    dirStack.push(ds);
                    walkUp = true;
                    break;
                }
                else
                {
                    if(DeleteFileW(path.c_str()) == FALSE)
                        ret = FALSE;
                }
            }
            while(FindNextFileW(e->hFind, &e->data));
        }

        if(!walkUp)
        {
            if(e->hFind) FindClose(e->hFind);
            if(RemoveDirectoryW(e->path.c_str()) == FALSE)
                ret = FALSE;
            e = NULL;
            dirStack.pop();
        }
    }
    return (ret == TRUE);
}