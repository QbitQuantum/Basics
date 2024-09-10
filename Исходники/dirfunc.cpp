int fullsplit( const char* path )
{
#ifdef _WIN32
// FIXME: 2008 Upgrades needed here?
#if defined( _MSC_VER ) && ( _MSC_VER <= 1310 )  // up to VS2003
  _splitpath( path, temp_drive, temp_dir, temp_fname, temp_ext );
#else  // VS2005 using MS STL, boooooo
  _splitpath_s( path, temp_drive, MAXDRIVE, temp_dir, MAXDIR, temp_fname, MAXFILE, temp_ext,
                MAXEXT );
#endif
  return 0;
#else
  return fnsplit( path, temp_drive, temp_dir, temp_fname, temp_ext );
#endif
}