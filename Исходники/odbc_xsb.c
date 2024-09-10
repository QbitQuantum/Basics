/*-----------------------------------------------------------------------------*/
void ODBCUserTables()
{
  struct Cursor *cur = (struct Cursor *)ptoc_int(2);
  UWORD TablePrivilegeExists;
  RETCODE rc;

  /* since some ODBC drivers don't implement the function SQLTablePrivileges*/
  /* we check it first*/
  SQLGetFunctions(cur->hdbc,SQL_API_SQLTABLEPRIVILEGES,&TablePrivilegeExists);
  if (!TablePrivilegeExists) {
    printf("Privilege concept does not exist in this DVMS: you probably can access any of the existing tables\n");
    ctop_int(3, 2);
    return;
  }
  if (((rc=SQLTablePrivileges(cur->hstmt,
			      NULL, 0,
			      NULL, 0,
			      NULL, 0)) == SQL_SUCCESS) ||
      (rc == SQL_SUCCESS_WITH_INFO)) 
    ctop_int(3,0);
  else {
    ctop_int(3,PrintErrorMsg(cur));
    SetCursorClose(cur);
  }
  return; 
}