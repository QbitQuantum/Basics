bool openlist(HWND hwnd)
{
    OPENFILENAMEW fn;

    memset(&fn,0,sizeof(fn));
    fn.lStructSize=sizeof(fn);
    fn.lpstrFilter=WTB_FILE_FILTER_TDL;
    fn.nMaxFile=MAX_PATH;
    fn.nFilterIndex=0;
    fn.lpstrFileTitle=NULL;
    fn.nMaxFileTitle=0;
    fn.lpstrInitialDir=EWIN_TXT_CDIR;
    fn.lpstrFile=(wchar_t *)malloc((MAX_PATH+1)*sizeof(wchar_t));
    fn.lpstrFile[0]=0;
    fn.lpstrDefExt=L"";
    fn.Flags=OFN_EXPLORER | OFN_ENABLESIZING | OFN_HIDEREADONLY;
    fn.lpstrTitle=WTB_FILE_TEXT_STD_OPEN;
    if(GetOpenFileNameW(&fn))
    {
        if(DOC_FILENAME==0)
        {
            DOC_FILENAME=(wchar_t *)malloc((wcslen(fn.lpstrFile)+1)*sizeof(wchar_t));
        }
        else
        {
            DOC_FILENAME=(wchar_t *)realloc(DOC_FILENAME,(wcslen(fn.lpstrFile)+1)*sizeof(wchar_t));
        }
        wcscpy(DOC_FILENAME,fn.lpstrFile);

        //Laden
        //loadlist(DOC_FILENAME);
        return true;
    }
    return false;
}