static int unlink_config_file( const char *filename)
{
   char buff[255];
   int err_code;
   extern int use_config_directory;          /* miscell.c */

   get_file_name( buff, filename);
   if( use_config_directory)
      {
      char cpath[255];

      make_config_dir_name( cpath, buff);
#ifdef _WIN32                /* MS is different. */
      err_code = _unlink( cpath);
#else
      err_code = unlink( cpath);
#endif
      }
   else
#ifdef _WIN32
      err_code = _unlink( buff);
#else
      err_code = unlink( buff);
#endif
   return( err_code);
}