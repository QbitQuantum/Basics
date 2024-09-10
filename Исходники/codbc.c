void bgl_odbc_driver_connect(SQLHANDLE dbc, char* constr)
{
  SQLRETURN v;
  v = SQLDriverConnect(dbc,NULL,constr,SQL_NTS,NULL,
		       0,NULL,SQL_DRIVER_NOPROMPT);

  if(!SQL_SUCCEEDED(v))
    {
	
      report_odbc_error("bgl_odbc_driver_connect",
			SQL_HANDLE_DBC, 
			dbc);
    }
}