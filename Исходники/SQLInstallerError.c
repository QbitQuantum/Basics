RETCODE INSTAPI
SQLInstallerErrorW (WORD iError, DWORD * pfErrorCode, LPWSTR lpszErrorMsg,
    WORD cbErrorMsgMax, WORD * pcbErrorMsg)
{
  char *_errormsg_u8 = NULL;
  RETCODE retcode = SQL_ERROR;

  if (cbErrorMsgMax > 0)
    {
      if ((_errormsg_u8 =
	      malloc (cbErrorMsgMax * UTF8_MAX_CHAR_LEN + 1)) == NULL)
	{
	  PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
	  goto done;
	}
    }

  retcode =
      SQLInstallerError (iError, pfErrorCode, _errormsg_u8,
      cbErrorMsgMax * UTF8_MAX_CHAR_LEN, pcbErrorMsg);

  if (retcode != SQL_ERROR)
    {
      dm_StrCopyOut2_U8toW (_errormsg_u8, lpszErrorMsg, cbErrorMsgMax,
	  pcbErrorMsg);
    }

done:
  MEM_FREE (_errormsg_u8);

  return retcode;
}