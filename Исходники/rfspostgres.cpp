static int createTempFile(RFS_ServerBase &base,char *&name)
{
    free(name);
#ifdef _WIN32
    name = _tempnam(tempdir,"rfspgtmp");
    int ret = _open(name, _O_RDWR | _O_CREAT | _O_BINARY, _S_IREAD|_S_IWRITE);
#else
    size_t ds = tempdir?strlen(tempdir):0;
    name = (char *)malloc(ds+32);
    if (ds) {
        memcpy(name,tempdir,ds);
        if (tempdir[ds-1]!='/')
            tempdir[ds++] = '/';
    }
    else
        *name = 0;
    strcat(name,"rfspg_XXXXXX");
    int ret = mkstemp(name);
#endif
    if (ret==-1) {
        free(name);
        name = NULL;
        base.throwError(errno,"Creating temp file");
    }
    return ret;
}