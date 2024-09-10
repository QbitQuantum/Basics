 /******************************************************************************
     TerEnableTracking:
     Enable or disable tracking of text changes.  This function returns the
     previous status.
 ******************************************************************************/
 BOOL WINAPI _export TerEnableTracking(HWND hWnd, bool enable, LPBYTE UName, BOOL UseDefaultClrStyle,
     DWORD InsStyle, COLORREF InsColor, DWORD DelStyle, COLORREF DelColor)
 {
     BYTE name[UNLEN+1];
     LPBYTE pName=null;
     int  i,len;
     SYSTEMTIME SysTime;
     FILETIME  FileTime;
     WORD DosDate,DosTime;
     bool NewUser=false;

     PTERWND w;

     if (NULL==(w=GetWindowPointer(hWnd))) return false;  // get the pointer to window data

     if (!TerArg.WordWrap) return false;

     if (TrackChanges == enable) return true;   // no status change requested

     TrackChanges=enable;

     if (enable) {
        if (UName && lstrlen(UName)>0) pName=UName;
        else {  // get system user name
          len=UNLEN;
          name[0]=0;
          GetUserName(name,&len);
          if (len>49) len=49;   // StrReviewer limit
          name[len]=0;
          pName=name;
        }

        // check if this reviewer exists
        for (i=1;i<TotalReviewers;i++) if (lstrcmpi(reviewer[i].name,pName)==0) break;

        if (i==TotalReviewers) {
           i=GetReviewerSlot(w);
           lstrncpy(reviewer[i].name,pName,49);  // copy name
           reviewer[i].name[49]=0;
           NewUser=true;

        }
        
        if (!UseDefaultClrStyle) {
           reviewer[i].InsStyle=InsStyle;
           reviewer[i].DelStyle=DelStyle;

           reviewer[i].InsColor=InsColor;
           reviewer[i].DelColor=DelColor;
           reviewer[i].FmtColor=InsColor;
        } 
        
        TrackRev=i;   // current reviewer id

        // get the current date/time as DWORD
        GetLocalTime(&SysTime);
        SystemTimeToFileTime(&SysTime,&FileTime);
        FileTimeToDosDateTime(&FileTime,&DosDate,&DosTime);
        TrackTime=(((DWORD)DosDate)<<16)+DosTime;

        InsertMode=true;              // insert mode always true when tracking

        if (!NewUser) {               // font/style might have changed, so recreate the fonts
           RecreateFonts(w,hTerDC);
           RequestPagination(w,true);
           PaintTer(w);
        }     
     } 
     else {
        TrackRev=0;
        TrackTime=0;
     } 
     return true;
 }