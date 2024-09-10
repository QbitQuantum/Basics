static BOOL file_exists( LPCWSTR path )
{
  if( _waccess_s( path, 0 ) == 0 )
  {
    struct _stat status;
    _wstat( path, &status );
    return (status.st_mode & S_IFREG) != 0;
  }

  return FALSE;
}