BOOL INSTAPI
SQLGetAvailableDriversW (LPCWSTR lpszInfFile, LPWSTR lpszBuf, WORD cbBufMax,
    WORD FAR * pcbBufOut)
{
  BOOL retcode = FALSE;
  char *_inf_u8 = NULL;
  char *_buffer_u8 = NULL;
  SQLCHAR *ptr;
  SQLWCHAR *ptrW;
  WORD len = 0, length;

  _inf_u8 = (char *) dm_SQL_WtoU8 ((SQLWCHAR *) lpszInfFile, SQL_NTS);
  if (_inf_u8 == NULL && lpszInfFile)
    {
      PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
      goto done;
    }

  if (cbBufMax > 0)
    {
      if ((_buffer_u8 = malloc (cbBufMax * UTF8_MAX_CHAR_LEN + 1)) == NULL)
	{
	  PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
	  goto done;
	}
    }

  retcode =
      SQLGetAvailableDrivers (_inf_u8, _buffer_u8,
      cbBufMax * UTF8_MAX_CHAR_LEN, pcbBufOut);

  if (retcode == TRUE)
    {
      length = 0;

      for (ptr = _buffer_u8, ptrW = lpszBuf; *ptr;
	  ptr += STRLEN (ptr) + 1, ptrW += WCSLEN (ptrW) + 1)
	{
	  dm_StrCopyOut2_U8toW (ptr, ptrW, cbBufMax - 1, &len);
	  length += len;
	}

      *ptrW = L'\0';
      if (pcbBufOut)
	*pcbBufOut = length + 1;
    }

done:
  MEM_FREE (_inf_u8);
  MEM_FREE (_buffer_u8);

  return retcode;
}