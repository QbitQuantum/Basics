DWORD
SearchPathA (LPCSTR lpPath, LPCSTR lpFileName, LPCSTR lpExtension,
             DWORD nBufferLength, LPSTR lpBuffer, LPSTR* lpFilePart)
{
  char *filename;
  char *filepart;
  int filename_len;
  
  _dbus_assert (lpPath == NULL);
  _dbus_assert (lpExtension == NULL);
  
  filename = find_program_in_inst_dir (lpFileName);
  if (!filename)
    {
      SetLastError (ERROR_FILE_NOT_FOUND);
      return 0;
    }

  filename_len = strlen (filename) + 1;
  if (filename_len > nBufferLength)
    {
      free (filename);
      return filename_len;
    }

  strcpy (lpBuffer, filename);
  free (filename);

  filepart = _mbsrchr (lpBuffer, '\\');
  if (!filepart)
    filepart = lpBuffer;
  *lpFilePart = filepart;

  return filename_len - 1;
}