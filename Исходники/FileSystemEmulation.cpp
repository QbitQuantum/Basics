 BOOL WINAPI_DECL GetFileTime(
     _In_       HANDLE hFile,
     _Out_opt_  LPFILETIME lpCreationTime,
     _Out_opt_  LPFILETIME lpLastAccessTime,
     _Out_opt_  LPFILETIME lpLastWriteTime
     )
 {
     FILE_BASIC_INFO basicInfo;
     BOOL b = GetFileInformationByHandleEx(
         hFile, 
         FileBasicInfo, 
         &basicInfo, 
         sizeof(basicInfo));
     if (b == FALSE)
         return FALSE;
     if (lpCreationTime)
         *lpCreationTime = (FILETIME const &)basicInfo.CreationTime;
     if (lpLastAccessTime)
         *lpLastAccessTime = (FILETIME const &)basicInfo.LastAccessTime;
     if (lpLastWriteTime)
         *lpLastWriteTime = (FILETIME const &)basicInfo.LastWriteTime;
     return TRUE;
 }