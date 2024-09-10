/**
 * Change the file-permission settings.
 */
int _win_chmod(const char *filename, int pmode)
{
  wchar_t szFile[_MAX_PATH + 1];
  long lRet;

  pmode &= (_S_IREAD | _S_IWRITE);

  if (_plibc_utf8_mode == 1)
    lRet = plibc_conv_to_win_pathwconv(filename, szFile, _MAX_PATH);
  else
    lRet = plibc_conv_to_win_path(filename, (char *) szFile, _MAX_PATH);
  if (lRet != ERROR_SUCCESS)
  {
    SetErrnoFromWinError(lRet);
    return -1;
  }

  /* chmod sets errno */
  if (_plibc_utf8_mode == 1)
    return _wchmod(szFile, pmode);
  else
    return chmod((char *) szFile, pmode);
}