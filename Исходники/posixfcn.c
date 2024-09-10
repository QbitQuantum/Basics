/* A replacement for tmpfile, since the MSVCRT implementation creates
   the file in the root directory of the current drive, which might
   not be writable by our user.  Most of the code borrowed from
   create_batch_file, see job.c.  */
FILE *
tmpfile (void)
{
  char temp_path[MAXPATHLEN];
  unsigned path_size = GetTempPath (sizeof temp_path, temp_path);
  int path_is_dot = 0;
  /* The following variable is static so we won't try to reuse a name
     that was generated a little while ago, because that file might
     not be on disk yet, since we use FILE_ATTRIBUTE_TEMPORARY below,
     which tells the OS it doesn't need to flush the cache to disk.
     If the file is not yet on disk, we might think the name is
     available, while it really isn't.  This happens in parallel
     builds, where Make doesn't wait for one job to finish before it
     launches the next one.  */
  static unsigned uniq = 0;
  static int second_loop = 0;
  const char base[] = "gmake_tmpf";
  const unsigned sizemax = sizeof base - 1 + 4 + 10 + 10;
  unsigned pid = GetCurrentProcessId ();

  if (path_size == 0)
    {
      path_size = GetCurrentDirectory (sizeof temp_path, temp_path);
      path_is_dot = 1;
    }

  ++uniq;
  if (uniq >= 0x10000 && !second_loop)
    {
      /* If we already had 64K batch files in this
         process, make a second loop through the numbers,
         looking for free slots, i.e. files that were
         deleted in the meantime.  */
      second_loop = 1;
      uniq = 1;
    }
  while (path_size > 0 &&
         path_size + sizemax < sizeof temp_path &&
         !(uniq >= 0x10000 && second_loop))
    {
      HANDLE h;

      sprintf (temp_path + path_size,
               "%s%s%u-%x.tmp",
               temp_path[path_size - 1] == '\\' ? "" : "\\",
               base, pid, uniq);
      h = CreateFile (temp_path,  /* file name */
                      GENERIC_READ | GENERIC_WRITE | DELETE, /* desired access */
                      FILE_SHARE_READ | FILE_SHARE_WRITE,    /* share mode */
                      NULL,                                  /* default security attributes */
                      CREATE_NEW,                            /* creation disposition */
                      FILE_ATTRIBUTE_NORMAL |                /* flags and attributes */
                      FILE_ATTRIBUTE_TEMPORARY |
                      FILE_FLAG_DELETE_ON_CLOSE,
                      NULL);                                 /* no template file */

      if (h == INVALID_HANDLE_VALUE)
        {
          const DWORD er = GetLastError ();

          if (er == ERROR_FILE_EXISTS || er == ERROR_ALREADY_EXISTS)
            {
              ++uniq;
              if (uniq == 0x10000 && !second_loop)
                {
                  second_loop = 1;
                  uniq = 1;
                }
            }

          /* The temporary path is not guaranteed to exist, or might
             not be writable by user.  Use the current directory as
             fallback.  */
          else if (path_is_dot == 0)
            {
              path_size = GetCurrentDirectory (sizeof temp_path, temp_path);
              path_is_dot = 1;
            }

          else
            {
              errno = EACCES;
              break;
            }
        }
      else
        {
          int fd = _open_osfhandle ((intptr_t)h, 0);

          return _fdopen (fd, "w+b");
        }
    }

  if (uniq >= 0x10000)
    errno = EEXIST;
  return NULL;
}