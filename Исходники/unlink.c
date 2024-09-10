/**
 * @brief Delete a file
 *        If filename is a link, the link itself it removed.
 */
int _win_unlink(const char *filename)
{
  wchar_t szFile[_MAX_PATH + 1];
  long lRet;

  if (plibc_utf8_mode() == 1)
    lRet = plibc_conv_to_win_pathwconv_ex(filename, szFile, 0);
  else
    lRet = plibc_conv_to_win_path_ex(filename, (char *) szFile, 0);
  if (lRet != ERROR_SUCCESS)
  {
    SetErrnoFromWinError(lRet);
    return -1;
  }

  /* unlink sets errno */
  if (plibc_utf8_mode() == 1)
    return _wunlink(szFile);
  else
    return unlink((char *) szFile);
}