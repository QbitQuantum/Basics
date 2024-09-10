bool WDL_ChooseDirectory(HWND parent, const char *text, const char *initialdir, char *fn, int fnsize, bool preservecwd)
{
  char olddir[2048];
  GetCurrentDirectory(sizeof(olddir),olddir);
#ifdef _WIN32
  char name[4096];
  lstrcpyn(name,initialdir?initialdir:"",sizeof(name));
  BROWSEINFO bi={parent,NULL, name, text, BIF_RETURNONLYFSDIRS|BIF_NEWDIALOGSTYLE, WDL_BrowseCallbackProc, (LPARAM)name,};
  LPITEMIDLIST idlist = SHBrowseForFolder( &bi );
  if (idlist) 
  {
    SHGetPathFromIDList( idlist, name );        
    IMalloc *m;
    SHGetMalloc(&m);
    m->Free(idlist);
    lstrcpyn(fn,name,fnsize);
    return true;
  }
  return false;

#else
  bool r = BrowseForDirectory(text,initialdir,fn,fnsize);
  if (preservecwd) SetCurrentDirectory(olddir);
  return r;
#endif
}