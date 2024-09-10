// Main routine
CString XSHBrowseForFolder(HWND hwnd,char* title,char* _path) {
  char path[MAX_PATH]; path[0]='\0';

  // Remove the last slash bar
  if (strlen(_path)>0)
  if (_path[strlen(_path)-1]=='\\')
    _path[strlen(_path)-1]='\0';

  // Get IMalloc Interface
  LPMALLOC Mymal;
  if (SHGetMalloc(&Mymal)!=NOERROR)
    return path;
  
  // Build Root directory (My Computer)
  LPITEMIDLIST Mylist;
  if (SHGetSpecialFolderLocation(hwnd,CSIDL_DRIVES,&Mylist)==NOERROR) {

    // Convert _path into browse data
    LPITEMIDLIST MyItemlist=XSHBFF_PathConvert(hwnd,_path);
    
    // Parameter structure for callback
    char Thispath[MAX_PATH]; Thispath[0]='\0';
    LPARAM CParam[2];
    CParam[0]=(LPARAM) MyItemlist;
    CParam[1]=(LPARAM) Thispath;
    // Fill the BROWSEINFO structure
    BROWSEINFO br;
    br.hwndOwner=hwnd;       // hwnd
    br.pidlRoot=NULL;        // root
    br.pszDisplayName=path;  // buffer
    br.lpszTitle=title;      // title
    br.ulFlags=BIF_RETURNONLYFSDIRS;  // dir
    br.lpfn=XSHBFF_CallbackProc;      // callback
    br.lParam=(LPARAM) CParam;          // callback params
    br.iImage=0;             // image
    // And Call SHBrowseForFolder
    LPITEMIDLIST UserList;
    if ( (UserList = SHBrowseForFolder(&br)) != NULL) {
      if (strlen(Thispath)==0) {  // No value in path
        // Convert UserList to a string
        if (SHGetPathFromIDList(UserList,path)==FALSE)
          path[0]='\0';
      } else
        strcpy(path,Thispath);
      Mymal->Free(UserList);
    }
    if (MyItemlist) Mymal->Free(MyItemlist);
    Mymal->Free(Mylist);
  }
  return path;
}