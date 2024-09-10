static void
_iodbcdm_env_settracing (GENV_t *genv)
{
  char buf[1024];

  genv = genv; /*UNUSED*/

  /*
   *  Check TraceFile keyword
   */
  SQLSetConfigMode (ODBC_BOTH_DSN);
  if( SQLGetPrivateProfileString ("ODBC", "TraceFile", "", buf, sizeof(buf) / sizeof(SQLTCHAR), "odbc.ini") == 0 || !buf[0])
    STRCPY (buf, SQL_OPT_TRACE_FILE_DEFAULT);
  trace_set_filename (buf);

  /*
   *  Check Trace keyword
   */
  SQLSetConfigMode (ODBC_BOTH_DSN);
  if ( SQLGetPrivateProfileString ("ODBC", "Trace", "", buf, sizeof(buf) / sizeof(SQLTCHAR), "odbc.ini") &&
      (STRCASEEQ (buf, "on") || STRCASEEQ (buf, "yes")
   || STRCASEEQ (buf, "1")))
    trace_start ();

  return;
}