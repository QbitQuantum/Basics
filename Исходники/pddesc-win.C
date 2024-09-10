bool
PdFile::IsBad( void ) const
{
    DWORD dwflags = 0;
    return (GetHandleInformation( fd, &dwflags ) == FALSE);
}