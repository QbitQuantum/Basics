bool BrowseFileOpen(HWND owner, const char* filter, const char* defext, char* filename, int filename_size, const char* init_dir)
{
    OPENFILENAME ofstruct;
    memset(&ofstruct, 0, sizeof(ofstruct));
    ofstruct.lStructSize=sizeof(ofstruct);
    ofstruct.hwndOwner=owner;
    ofstruct.hInstance=hInst;
    ofstruct.lpstrFilter=filter;
    ofstruct.lpstrFile=filename;
    ofstruct.nMaxFile=filename_size;
    ofstruct.lpstrInitialDir=init_dir;
    ofstruct.lpstrDefExt=defext;
    ofstruct.Flags=OFN_EXTENSIONDIFFERENT|OFN_HIDEREADONLY|OFN_NONETWORKBUTTON;
    return GetOpenFileNameA(&ofstruct);
}