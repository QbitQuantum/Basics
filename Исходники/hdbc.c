RETCODE SQL_API 
SQLFreeConnect (HDBC hdbc)
{
  GENV_t FAR *genv;
  DBC_t FAR *pdbc = (DBC_t FAR *) hdbc;
  DBC_t FAR *tpdbc;

  if (hdbc == SQL_NULL_HDBC)
    {
      return SQL_INVALID_HANDLE;
    }

  /* check state */
  if (pdbc->state != en_dbc_allocated)
    {
      PUSHSQLERR (pdbc->herr, en_S1010);

      return SQL_ERROR;
    }

  genv = (GENV_t FAR *) pdbc->genv;

  for (tpdbc = (DBC_t FAR *) genv->hdbc;
      tpdbc != NULL;
      tpdbc = tpdbc->next)
    {
      if (pdbc == tpdbc)
	{
	  genv->hdbc = pdbc->next;
	  break;
	}

      if (pdbc == tpdbc->next)
	{
	  tpdbc->next = pdbc->next;
	  break;
	}
    }

  /* free this dbc */
  _iodbcdm_driverunload (pdbc);
  _iodbcdm_freesqlerrlist (pdbc->herr);

  if (pdbc->tfile)
    {
      MEM_FREE (pdbc->tfile);
    }

  SQLSetConnectOption (pdbc, SQL_OPT_TRACE, SQL_OPT_TRACE_OFF);

  MEM_FREE (pdbc);

  return SQL_SUCCESS;
}