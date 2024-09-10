/**
 * g_mapped_file_new:
 * @filename: The path of the file to load, in the GLib filename encoding
 * @writable: whether the mapping should be writable
 * @error: return location for a #GError, or %NULL
 *
 * Maps a file into memory. On UNIX, this is using the mmap() function.
 *
 * If @writable is %TRUE, the mapped buffer may be modified, otherwise
 * it is an error to modify the mapped buffer. Modifications to the buffer 
 * are not visible to other processes mapping the same file, and are not 
 * written back to the file.
 *
 * Note that modifications of the underlying file might affect the contents
 * of the #GMappedFile. Therefore, mapping should only be used if the file 
 * will not be modified, or if all modifications of the file are done
 * atomically (e.g. using g_file_set_contents()). 
 *
 * Return value: a newly allocated #GMappedFile which must be unref'd
 *    with g_mapped_file_unref(), or %NULL if the mapping failed.
 *
 * Since: 2.8
 */
GMappedFile *
g_mapped_file_new (const gchar  *filename,
		   gboolean      writable,
		   GError      **error)
{
  GMappedFile *file;
  int fd;
  struct stat st;

  g_return_val_if_fail (filename != NULL, NULL);
  g_return_val_if_fail (!error || *error == NULL, NULL);

  fd = g_open (filename, (writable ? O_RDWR : O_RDONLY) | _O_BINARY, 0);
  if (fd == -1)
    {
      int save_errno = errno;
      gchar *display_filename = g_filename_display_name (filename);
      
      g_set_error (error,
                   G_FILE_ERROR,
                   g_file_error_from_errno (save_errno),
                   _("Failed to open file '%s': open() failed: %s"),
                   display_filename, 
		   g_strerror (save_errno));
      g_free (display_filename);
      return NULL;
    }

  file = g_slice_new0 (GMappedFile);
  file->ref_count = 1;
  file->free_func = g_mapped_file_destroy;

  if (fstat (fd, &st) == -1)
    {
      int save_errno = errno;
      gchar *display_filename = g_filename_display_name (filename);

      g_set_error (error,
                   G_FILE_ERROR,
                   g_file_error_from_errno (save_errno),
                   _("Failed to get attributes of file '%s': fstat() failed: %s"),
                   display_filename, 
		   g_strerror (save_errno));
      g_free (display_filename);
      goto out;
    }

  if (st.st_size == 0)
    {
      file->length = 0;
      file->contents = NULL;
      close (fd);
      return file;
    }

  file->contents = MAP_FAILED;

#ifdef HAVE_MMAP
  if (st.st_size > G_MAXSIZE)
    {
      errno = EINVAL;
    }
  else
    {      
      file->length = (gsize) st.st_size;
      file->contents = (gchar *) mmap (NULL,  file->length,
				       writable ? PROT_READ|PROT_WRITE : PROT_READ,
				       MAP_PRIVATE, fd, 0);
    }
#endif
#ifdef G_OS_WIN32
  file->length = st.st_size;
  file->mapping = CreateFileMapping ((HANDLE) _get_osfhandle (fd), NULL,
				     writable ? PAGE_WRITECOPY : PAGE_READONLY,
				     0, 0,
				     NULL);
  if (file->mapping != NULL)
    {
      file->contents = MapViewOfFile (file->mapping,
				      writable ? FILE_MAP_COPY : FILE_MAP_READ,
				      0, 0,
				      0);
      if (file->contents == NULL)
	{
	  file->contents = MAP_FAILED;
	  CloseHandle (file->mapping);
	  file->mapping = NULL;
	}
    }
#endif

  
  if (file->contents == MAP_FAILED)
    {
      int save_errno = errno;
      gchar *display_filename = g_filename_display_name (filename);
      
      g_set_error (error,
		   G_FILE_ERROR,
		   g_file_error_from_errno (save_errno),
		   _("Failed to map file '%s': mmap() failed: %s"),
		   display_filename,
		   g_strerror (save_errno));
      g_free (display_filename);
      goto out;
    }

  close (fd);
  return file;

 out:
  close (fd);
  g_slice_free (GMappedFile, file);

  return NULL;
}