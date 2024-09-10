int
allocAndFillFileDesc( rodsServerHost_t *rodsServerHost,
                      const std::string&  objPath,
                      const std::string&  fileName,
                      const std::string&  rescHier,
                      int                 fd,
                      int                 mode ) {
    int fileInx;

    fileInx = allocFileDesc();
    if ( fileInx < 0 ) {
        return fileInx;
    }

    FileDesc[fileInx].rodsServerHost = rodsServerHost;
    FileDesc[fileInx].objPath  = strdup( objPath.c_str() );
    FileDesc[fileInx].fileName = strdup( fileName.c_str() );
    FileDesc[fileInx].rescHier = strdup( rescHier.c_str() );
    FileDesc[fileInx].mode = mode;
    FileDesc[fileInx].fd = fd;

    return fileInx;
}