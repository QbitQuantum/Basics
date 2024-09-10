BOOL CleanUp()
{
    DWORD dwAtt;
    BOOL result = TRUE;

    dwAtt = GetFileAttributesA(szFindName);
    if( dwAtt != INVALID_FILE_ATTRIBUTES )
    {
        if(!SetFileAttributesA (szFindName, FILE_ATTRIBUTE_NORMAL))
        {
            result = FALSE;
            Trace("ERROR:%d: Error setting attributes [%s][%d]\n", szFindName, FILE_ATTRIBUTE_NORMAL); 
        } 
        if(!DeleteFileA (szFindName))
        {
            result = FALSE;
            Trace("ERROR:%d: Error deleting file [%s][%d]\n", GetLastError(), szFindName, dwAtt);   
        }
    }

    dwAtt = GetFileAttributesA(szDirName);
    if( dwAtt != INVALID_FILE_ATTRIBUTES )
    {
        if(!RemoveDirectoryA (szDirName))
        {
            result = FALSE;
            Trace("ERROR:%d: Error deleting file [%s][%d]\n", GetLastError(), szDirName, dwAtt);   
        }
    }

    return result;
}