/**
 * Writes a string out to a file. If the file exists,
 * it will be atomically overwritten by the new data.
 *
 * @param str the string to write out
 * @param filename the file to save string to
 * @param world_readable if true, ensure file is world readable
 * @param error error to be filled in on failure
 * @returns #FALSE on failure
 */
dbus_bool_t
_dbus_string_save_to_file (const DBusString *str,
                           const DBusString *filename,
                           dbus_bool_t       world_readable,
                           DBusError        *error)
{
  HANDLE hnd;
  int bytes_to_write;
  const char *filename_c;
  DBusString tmp_filename;
  const char *tmp_filename_c;
  int total;
  const char *str_c;
  dbus_bool_t need_unlink;
  dbus_bool_t retval;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  hnd = INVALID_HANDLE_VALUE;
  retval = FALSE;
  need_unlink = FALSE;

  if (!_dbus_string_init (&tmp_filename))
    {
      dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
      return FALSE;
    }

  if (!_dbus_string_copy (filename, 0, &tmp_filename, 0))
    {
      dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
      _dbus_string_free (&tmp_filename);
      return FALSE;
    }

  if (!_dbus_string_append (&tmp_filename, "."))
    {
      dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
      _dbus_string_free (&tmp_filename);
      return FALSE;
    }

#define N_TMP_FILENAME_RANDOM_BYTES 8
  if (!_dbus_generate_random_ascii (&tmp_filename, N_TMP_FILENAME_RANDOM_BYTES))
    {
      dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
      _dbus_string_free (&tmp_filename);
      return FALSE;
    }

  filename_c = _dbus_string_get_const_data (filename);
  tmp_filename_c = _dbus_string_get_const_data (&tmp_filename);

  /* TODO - support world-readable in an atomic fashion */
  hnd = CreateFileA (tmp_filename_c, GENERIC_WRITE,
                     FILE_SHARE_READ | FILE_SHARE_WRITE,
                     NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL,
                     INVALID_HANDLE_VALUE);
  if (hnd == INVALID_HANDLE_VALUE)
    {
      char *emsg = _dbus_win_error_string (GetLastError ());
      dbus_set_error (error, _dbus_win_error_from_last_error (),
                       "Could not create \"%s\": %s", filename_c, emsg);
      _dbus_win_free_error_string (emsg);
      goto out;
    }
  if (world_readable)
    {
      if (! _dbus_make_file_world_readable (&tmp_filename, error))
        goto out;
    }

  _dbus_verbose ("tmp file %s hnd %p opened\n", tmp_filename_c, hnd);

  need_unlink = TRUE;

  total = 0;
  bytes_to_write = _dbus_string_get_length (str);
  str_c = _dbus_string_get_const_data (str);

  while (total < bytes_to_write)
    {
      DWORD bytes_written;
      BOOL res;

      res = WriteFile (hnd, str_c + total, bytes_to_write - total,
                       &bytes_written, NULL);

      if (res == 0 || bytes_written <= 0)
        {
          char *emsg = _dbus_win_error_string (GetLastError ());
          dbus_set_error (error, _dbus_win_error_from_last_error (),
                           "Could not write to %s: %s", tmp_filename_c, emsg);
          _dbus_win_free_error_string (emsg);
          goto out;
        }

      total += bytes_written;
    }

  if (CloseHandle (hnd) == 0)
    {
      char *emsg = _dbus_win_error_string (GetLastError ());
      dbus_set_error (error, _dbus_win_error_from_last_error (),
                       "Could not close file %s: %s", tmp_filename_c, emsg);
      _dbus_win_free_error_string (emsg);
      goto out;
    }

  hnd = INVALID_HANDLE_VALUE;

  /* Unlike rename(), MoveFileEx() can replace existing files */
  if (!MoveFileExA (tmp_filename_c, filename_c, MOVEFILE_REPLACE_EXISTING))
    {
      char *emsg = _dbus_win_error_string (GetLastError ());
      dbus_set_error (error, _dbus_win_error_from_last_error (),
                       "Could not rename %s to %s: %s",
                       tmp_filename_c, filename_c, emsg);
      _dbus_win_free_error_string (emsg);

      goto out;
    }

  need_unlink = FALSE;

  retval = TRUE;

 out:
  /* close first, then unlink */

  if (hnd != INVALID_HANDLE_VALUE)
    CloseHandle (hnd);

  if (need_unlink && DeleteFileA (tmp_filename_c) == 0)
    {
      char *emsg = _dbus_win_error_string (GetLastError ());
      _dbus_verbose ("Failed to unlink temp file %s: %s", tmp_filename_c,
                     emsg);
      _dbus_win_free_error_string (emsg);
    }

  _dbus_string_free (&tmp_filename);

  if (!retval)
    _DBUS_ASSERT_ERROR_IS_SET (error);

  return retval;
}