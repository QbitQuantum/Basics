void showFilesInExplorer(const std::vector<std::string>& files)
{
    size_t n = files.size();
    if (n == 0) return;

    std::string folder = fixPath(files[0]);
    size_t i = folder.find_last_of('\\');
    if (i != std::string::npos) folder = folder.substr(0, i);

    #ifdef _WIN32
        ITEMIDLIST* dir = ILCreateFromPathA(folder.c_str());
        LPITEMIDLIST* items = new LPITEMIDLIST[n];
        for (size_t i = 0; i < n; ++i) items[i] = ILCreateFromPathA(fixPath(files[i]).c_str());

        SHOpenFolderAndSelectItems(dir, (unsigned int)n, (LPCITEMIDLIST*)items, 0);

        for (size_t i = 0; i < n; ++i) ILFree(items[i]);
        ILFree(dir);
        delete[] items;
    #endif
}