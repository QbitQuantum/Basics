int gmx_truncatefile(char *path, gmx_off_t length)
{
#ifdef _MSC_VER
    /* Microsoft visual studio does not have "truncate" */
    HANDLE fh;
    LARGE_INTEGER win_length;

    win_length.QuadPart = length;

    fh = CreateFile(path,GENERIC_READ | GENERIC_WRITE,0,NULL,
            OPEN_EXISTING,0,NULL);
    SetFilePointerEx(fh,win_length,NULL,FILE_BEGIN);
    SetEndOfFile(fh);
    CloseHandle(fh);

    return 0;
#else
    return truncate(path,length);
#endif
}