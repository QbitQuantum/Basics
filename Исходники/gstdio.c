static int
_g_win32_stat_utf16_no_trailing_slashes (const gunichar2    *filename,
                                         int                 fd,
                                         GWin32PrivateStat  *buf,
                                         gboolean            for_symlink)
{
  HANDLE file_handle;
  gboolean succeeded_so_far;
  DWORD error_code;
  struct __stat64 statbuf;
  BY_HANDLE_FILE_INFORMATION handle_info;
  FILE_STANDARD_INFO std_info;
  WIN32_FIND_DATAW finddata;
  DWORD immediate_attributes;
  gboolean is_symlink = FALSE;
  gboolean is_directory;
  DWORD open_flags;
  wchar_t *filename_target = NULL;
  int result;

  if (fd < 0)
    {
      immediate_attributes = GetFileAttributesW (filename);

      if (immediate_attributes == INVALID_FILE_ATTRIBUTES)
        {
          error_code = GetLastError ();
          errno = w32_error_to_errno (error_code);

          return -1;
        }

      is_symlink = (immediate_attributes & FILE_ATTRIBUTE_REPARSE_POINT) == FILE_ATTRIBUTE_REPARSE_POINT;
      is_directory = (immediate_attributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY;

      open_flags = FILE_ATTRIBUTE_NORMAL;

      if (for_symlink && is_symlink)
        open_flags |= FILE_FLAG_OPEN_REPARSE_POINT;

      if (is_directory)
        open_flags |= FILE_FLAG_BACKUP_SEMANTICS;

      file_handle = CreateFileW (filename, FILE_READ_ATTRIBUTES,
                                 FILE_SHARE_READ, NULL, OPEN_EXISTING,
                                 open_flags,
                                 NULL);

      if (file_handle == INVALID_HANDLE_VALUE)
        {
          error_code = GetLastError ();
          errno = w32_error_to_errno (error_code);
          return -1;
        }
    }
  else
    {
      file_handle = (HANDLE) _get_osfhandle (fd);

      if (file_handle == INVALID_HANDLE_VALUE)
        return -1;
    }

  succeeded_so_far = GetFileInformationByHandle (file_handle,
                                                 &handle_info);
  error_code = GetLastError ();

  if (succeeded_so_far)
    {
      succeeded_so_far = GetFileInformationByHandleEx (file_handle,
                                                       FileStandardInfo,
                                                       &std_info,
                                                       sizeof (std_info));
      error_code = GetLastError ();
    }

  if (!succeeded_so_far)
    {
      if (fd < 0)
        CloseHandle (file_handle);
      errno = w32_error_to_errno (error_code);
      return -1;
    }

  /* It's tempting to use GetFileInformationByHandleEx(FileAttributeTagInfo),
   * but it always reports that the ReparseTag is 0.
   */
  if (fd < 0)
    {
      memset (&finddata, 0, sizeof (finddata));

      if (handle_info.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
        {
          HANDLE tmp = FindFirstFileW (filename,
                                       &finddata);

          if (tmp == INVALID_HANDLE_VALUE)
            {
              error_code = GetLastError ();
              errno = w32_error_to_errno (error_code);
              CloseHandle (file_handle);
              return -1;
            }

          FindClose (tmp);
        }

      if (is_symlink && !for_symlink)
        {
          /* If filename is a symlink, but we need the target.
           * To get information about the target we need to resolve
           * the symlink first.
           */
          DWORD filename_target_len;
          DWORD new_len;

          /* Just in case, give it a real memory location instead of NULL */
          new_len = GetFinalPathNameByHandleW (file_handle,
                                               (wchar_t *) &filename_target_len,
                                               0,
                                               FILE_NAME_NORMALIZED);

#define SANE_LIMIT 1024 * 10
          if (new_len >= SANE_LIMIT)
#undef SANE_LIMIT
            {
              new_len = 0;
              error_code = ERROR_BUFFER_OVERFLOW;
            }
          else if (new_len == 0)
            {
              error_code = GetLastError ();
            }

          if (new_len > 0)
            {
              /* Pretend that new_len doesn't count the terminating NUL char,
               * and ask for a bit more space than is needed, and allocate even more.
               */
              filename_target_len = new_len + 3;
              filename_target = g_malloc ((filename_target_len + 1) * sizeof (wchar_t));

              new_len = GetFinalPathNameByHandleW (file_handle,
                                                   filename_target,
                                                   filename_target_len,
                                                   FILE_NAME_NORMALIZED);

              /* filename_target_len is already larger than needed,
               * new_len should be smaller than that, even if the size
               * is off by 1 for some reason.
               */
              if (new_len >= filename_target_len - 1)
                {
                  new_len = 0;
                  error_code = ERROR_BUFFER_OVERFLOW;
                  g_clear_pointer (&filename_target, g_free);
                }
              else if (new_len == 0)
                {
                  g_clear_pointer (&filename_target, g_free);
                }
              /* GetFinalPathNameByHandle() is documented to return extended paths,
               * strip the extended prefix, if it is followed by a drive letter
               * and a colon. Otherwise keep it (the path could be
               * \\\\?\\Volume{GUID}\\ - it's only usable in extended form).
               */
              else if (new_len > 0)
                {
                  gsize len = new_len;

                  /* Account for NUL-terminator maybe not being counted.
                   * This is why we overallocated earlier.
                   */
                  if (filename_target[len] != L'\0')
                    {
                      len++;
                      filename_target[len] = L'\0';
                    }

                  _g_win32_strip_extended_ntobjm_prefix (filename_target, &len);
                  new_len = len;
                }

            }

          if (new_len == 0)
            succeeded_so_far = FALSE;
        }

      CloseHandle (file_handle);
    }
  /* else if fd >= 0 the file_handle was obtained via _get_osfhandle()
   * and must not be closed, it is owned by fd.
   */

  if (!succeeded_so_far)
    {
      errno = w32_error_to_errno (error_code);
      return -1;
    }

  /*
   * We can't use _wstat64() here, because with UCRT it now gives
   * information about the target, even if we want information about
   * the link itself (unlike MSVCRT, which gave information about
   * the link, and if we needed information about the target we were
   * able to resolve it by ourselves prior to calling _wstat64()).
   */
  if (fd < 0)
    result = _g_win32_fill_statbuf_from_handle_info (filename,
                                                     filename_target,
                                                     &handle_info,
                                                     &statbuf);
  else
    result = _fstat64 (fd, &statbuf);

  if (result != 0)
    {
      int errsv = errno;

      g_free (filename_target);
      errno = errsv;

      return -1;
    }

  g_free (filename_target);

  buf->st_dev = statbuf.st_dev;
  buf->st_mode = statbuf.st_mode;
  buf->volume_serial = handle_info.dwVolumeSerialNumber;
  buf->file_index = (((guint64) handle_info.nFileIndexHigh) << 32) | handle_info.nFileIndexLow;
  /* Note that immediate_attributes is for the symlink
   * (if it's a symlink), while handle_info contains info
   * about the symlink or the target, depending on the flags
   * we used earlier.
   */
  buf->attributes = handle_info.dwFileAttributes;
  buf->st_nlink = handle_info.nNumberOfLinks;
  buf->st_size = (((guint64) handle_info.nFileSizeHigh) << 32) | handle_info.nFileSizeLow;
  buf->allocated_size = std_info.AllocationSize.QuadPart;

  if (fd < 0 && buf->attributes & FILE_ATTRIBUTE_REPARSE_POINT)
    buf->reparse_tag = finddata.dwReserved0;
  else
    buf->reparse_tag = 0;

  buf->st_ctime = statbuf.st_ctime;
  buf->st_atime = statbuf.st_atime;
  buf->st_mtime = statbuf.st_mtime;

  return 0;
}