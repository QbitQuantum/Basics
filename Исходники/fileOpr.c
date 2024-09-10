int
allocAndFillFileDesc (rodsServerHost_t *rodsServerHost, char *fileName,
fileDriverType_t fileType, int fd, int mode)
{
    int fileInx;

    fileInx = allocFileDesc ();
    if (fileInx < 0) {
	return (fileInx);
    }

    FileDesc[fileInx].rodsServerHost = rodsServerHost;
    FileDesc[fileInx].fileName = strdup (fileName);
    FileDesc[fileInx].fileType = fileType;
    FileDesc[fileInx].mode = mode;
    FileDesc[fileInx].fd = fd;

    return (fileInx);
}