void FName::SetFileTime(long t)
{
#ifdef WIN32
    HANDLE f=CreateFile(Str,GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if (f==INVALID_HANDLE_VALUE) return;
    FILETIME ft;
    DosDateTimeToFileTime(HIWORD(t),LOWORD(t),&ft);
    ::SetFileTime(f,NULL,NULL,&ft);
    CloseHandle(f);
#else
    int hand;
    union Time {
        ftime ft;
        DWORD dw;
    } ft;
    ft.dw=t;
    if ((hand=open(Str,O_RDONLY))<0) return;
    setftime(hand,&ft.ft);
    close(hand);
#endif
}