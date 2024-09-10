BOOL DeleteDirectory(const char* sPath) {
    HANDLE hFind;  // file handle

    WIN32_FIND_DATAA FindFileData;
    
    char DirPath[MAX_PATH];
    char FileName[MAX_PATH];
    
    strcpy(DirPath,sPath);
    strcat(DirPath,"\\*");    // searching all files
    
    strcpy(FileName,sPath);
    strcat(FileName,"\\");
    
    hFind = FindFirstFileA(DirPath,&FindFileData); // find the first file
    if(hFind == INVALID_HANDLE_VALUE) return FALSE;
    strcpy(DirPath,FileName);
    
    bool bSearch = true;
    while(bSearch) { // until we finds an entry
        if(FindNextFileA(hFind,&FindFileData)) {
            if(IsDots(FindFileData.cFileName)) continue;
            strcat(FileName,FindFileData.cFileName);
            if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                
                // we have found a directory, recurse
                if(!DeleteDirectory(FileName)) { 
                    FindClose(hFind); 
                    return FALSE; // directory couldn't be deleted
                }
                RemoveDirectoryA(FileName); // remove the empty directory
                strcpy(FileName,DirPath);
            }
            else {

                if(!DeleteFileA(FileName)) {  // delete the file
                    FindClose(hFind); 
                    return FALSE; 
                }                 
                strcpy(FileName,DirPath);
            }
        }
        else {
            if(GetLastError() == ERROR_NO_MORE_FILES) // no more files there
                bSearch = false;
            else {
                // some error occured, close the handle and return FALSE
                FindClose(hFind); 
                return FALSE;
            }
            
        }
        
    }
    FindClose(hFind);  // closing file handle
    
    return RemoveDirectoryA(sPath); // remove the empty directory
    
}