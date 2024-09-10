 void draw_file_icon(HDC hdc, int x, int y, LPCWSTR filename)
 {
     SHFILEINFOW sfi;
     HIMAGELIST hlist = (HIMAGELIST) SHGetFileInfoW( filename, 0, &sfi, sizeof(SHFILEINFO), SHGFI_USEFILEATTRIBUTES | SHGFI_SYSICONINDEX | SHGFI_SMALLICON );
     if(hlist)
       ImageList_Draw(hlist, sfi.iIcon, hdc, x, y, ILD_TRANSPARENT); 
 }