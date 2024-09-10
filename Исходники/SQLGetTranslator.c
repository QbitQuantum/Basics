BOOL INSTAPI
SQLGetTranslatorW (HWND hwnd,
    LPWSTR lpszName,
    WORD cbNameMax,
    WORD FAR * pcbNameOut,
    LPWSTR lpszPath,
    WORD cbPathMax, WORD FAR * pcbPathOut, DWORD FAR * pvOption)
{
  char *_name_u8 = NULL;
  char *_path_u8 = NULL;
  BOOL retcode = FALSE;

  if (cbNameMax > 0)
    {
      if ((_name_u8 = malloc (cbNameMax * UTF8_MAX_CHAR_LEN + 1)) == NULL)
	{
	  PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
	  goto done;
	}
    }

  if (cbPathMax > 0)
    {
      if ((_path_u8 = malloc (cbPathMax * UTF8_MAX_CHAR_LEN + 1)) == NULL)
	{
	  PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
	  goto done;
	}
    }

  retcode =
      SQLGetTranslator (hwnd, _name_u8, cbNameMax * UTF8_MAX_CHAR_LEN,
      pcbNameOut, _path_u8, cbPathMax * UTF8_MAX_CHAR_LEN, pcbPathOut,
      pvOption);

  if (retcode == TRUE)
    {
      dm_StrCopyOut2_U8toW (_name_u8, lpszName, cbNameMax, pcbNameOut);
      dm_StrCopyOut2_U8toW (_path_u8, lpszPath, cbPathMax, pcbPathOut);
    }

done:
  MEM_FREE (_name_u8);
  MEM_FREE (_path_u8);

  return retcode;
}