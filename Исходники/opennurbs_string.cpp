bool ON::IsDirectory( const char* utf8pathname )
{
  bool rc = false;

  if ( 0 != utf8pathname && 0 != utf8pathname[0] )
  {
    ON_String buffer;
    const char* stail = utf8pathname;
    while ( 0 != *stail )
      stail++;
    stail--;
    if ( '\\' == *stail || '/' == *stail ) 
    {
      const char trim[2] = {*stail,0};
      buffer = utf8pathname;
      buffer.TrimRight(trim);
      if ( buffer.Length() > 0 )
        utf8pathname = buffer;
    }
#if defined(ON_COMPILER_MSC)
    // this works on Windows
    struct _stat64 buf;
    memset(&buf,0,sizeof(buf));
    int stat_errno = _stat64( utf8pathname, &buf );
    if ( 0 == stat_errno && 0 != (_S_IFDIR & buf.st_mode) )
    {
      rc = true;
    }
#else
    // this works on Apple and gcc implentations.
    struct stat buf;
    memset(&buf,0,sizeof(buf));
    int stat_errno = stat( utf8pathname, &buf );
    if ( 0 == stat_errno && S_ISDIR(buf.st_mode) )
    {
      rc = true;
    }
#endif
  }

  return rc;
}