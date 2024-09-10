//
// ----------------------------------------------------------------------------
//
bool CMemoryIniFile::isPathExisting(void)
{
    std::string strIniFile = m_strIniFile;
    strIniFile.reserve ( 2*MAX_PATH );
    LPSTR   szPath = (LPSTR) strIniFile.c_str();
    if (!std::string( PathFindExtensionA( szPath )).empty())
    {
        PathRemoveFileSpecA( szPath );
    }    
    str::ResizeByZeroTermination( strIniFile );
    BOOL bRC = PathIsDirectoryA( (char*) strIniFile.c_str() ); 

    return (bRC != FALSE);
}