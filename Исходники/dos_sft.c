unsigned _RTL_FUNC _dos_setftime(int fd, unsigned date, unsigned time)
{
    FILETIME timex,timet ;
    DosDateTimeToFileTime(date,time,&timex) ;
    LocalFileTimeToFileTime(&timex,&timet);
    return (!SetFileTime((HANDLE)fd,0,0,&timet));
}