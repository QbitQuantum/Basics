/**
 * g_remove:
 * @filename: a pathname in the GLib file name encoding (UTF-8 on Windows)
 *
 * A wrapper for the POSIX remove() function. The remove() function
 * deletes a name from the filesystem.
 *
 * See your C library manual for more details about how remove() works
 * on your system. On Unix, remove() removes also directories, as it
 * calls unlink() for files and rmdir() for directories. On Windows,
 * although remove() in the C library only works for files, this
 * function tries first remove() and then if that fails rmdir(), and
 * thus works for both files and directories. Note however, that on
 * Windows, it is in general not possible to remove a file that is
 * open to some process, or mapped into memory.
 *
 * If this function fails on Windows you can't infer too much from the
 * errno value. rmdir() is tried regardless of what caused remove() to
 * fail. Any errno value set by remove() will be overwritten by that
 * set by rmdir().
 *
 * Returns: 0 if the file was successfully removed, -1 if an error
 *    occurred
 *
 * Since: 2.6
 */
int
ws_stdio_remove (const gchar *filename)
{
      wchar_t *wfilename = g_utf8_to_utf16 (filename, -1, NULL, NULL, NULL);
      int retval;
      int save_errno;

      if (wfilename == NULL)
	{
	  errno = EINVAL;
	  return -1;
	}

      retval = _wremove (wfilename);
      if (retval == -1)
	retval = _wrmdir (wfilename);
      save_errno = errno;

      g_free (wfilename);

      errno = save_errno;
      return retval;
}