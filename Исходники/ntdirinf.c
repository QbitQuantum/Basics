void __FromDOSDT( unsigned short d, unsigned short t, FILETIME *NT_stamp )
{
    FILETIME local_ft;

    DosDateTimeToFileTime( d, t, &local_ft );
    LocalFileTimeToFileTime( &local_ft, NT_stamp );
}