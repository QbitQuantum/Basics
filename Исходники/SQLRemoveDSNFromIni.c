BOOL
RemoveDSNFromIni (SQLPOINTER lpszDSN, SQLCHAR waMode)
{
  BOOL retcode = FALSE;
  char *_dsn_u8 = NULL;
  PCONFIG pCfg;

  /* Check dsn */
  if (waMode == 'A')
    {
      if (!lpszDSN || !ValidDSN (lpszDSN) || !STRLEN (lpszDSN))
	{
	  PUSH_ERROR (ODBC_ERROR_INVALID_DSN);
	  goto quit;
	}
      _dsn_u8 = lpszDSN;
    }
  else
    {
      if (!lpszDSN || !ValidDSNW (lpszDSN) || !WCSLEN (lpszDSN))
	{
	  PUSH_ERROR (ODBC_ERROR_INVALID_DSN);
	  goto quit;
	}

      _dsn_u8 = (char *) dm_SQL_WtoU8 ((SQLWCHAR *) lpszDSN, SQL_NTS);
      if (_dsn_u8 == NULL && lpszDSN)
	{
	  PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
	  goto quit;
	}
    }

  if (_iodbcdm_cfg_search_init (&pCfg, "odbc.ini", TRUE))
    {
      PUSH_ERROR (ODBC_ERROR_REQUEST_FAILED);
      goto quit;
    }

  if (strcmp (_dsn_u8, "Default"))
    {
      /* deletes a DSN from [ODBC data sources] section */
#ifdef WIN32
      _iodbcdm_cfg_write (pCfg, "ODBC 32 bit Data Sources", (LPSTR) _dsn_u8,
	  NULL);
#else
      _iodbcdm_cfg_write (pCfg, "ODBC Data Sources", (LPSTR) _dsn_u8, NULL);
#endif
    }

  /* deletes the DSN section in odbc.ini */
  _iodbcdm_cfg_write (pCfg, (LPSTR) _dsn_u8, NULL, NULL);

  if (_iodbcdm_cfg_commit (pCfg))
    {
      PUSH_ERROR (ODBC_ERROR_REQUEST_FAILED);
      goto done;
    }

  retcode = TRUE;

done:
  _iodbcdm_cfg_done (pCfg);

quit:
  if (_dsn_u8 != lpszDSN)
    MEM_FREE (_dsn_u8);

  return retcode;
}