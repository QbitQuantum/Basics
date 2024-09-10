_declspec(dllexport) BOOL BrowseToFile(const wchar_t* filename)
{
	ITEMIDLIST *pidl = ILCreateFromPath(filename);
    if(pidl) {
        SHOpenFolderAndSelectItems(pidl,0,0,0);
        ILFree(pidl);
		return TRUE;
    }
	return FALSE;
}