unsigned int CRhoFile::deleteFile( const char* szFilePath ){
#if defined(WINDOWS_PLATFORM)
    return (unsigned int)_unlink(szFilePath);
#else
    return (unsigned int)remove(szFilePath);
#endif
}