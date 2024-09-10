int
main (int argc, char *argv[])
{
   rc = SQLAllocEnv (&henv);
   IF_EERR_EXIT (henv, rc);

   rc = SQLAllocConnect (henv, &hdbc);
   IF_CERR_EXIT (hdbc, rc);

   rc = SQLConnect (hdbc,
       argc > 1 ? argv[1] : "1111", SQL_NTS,
       argc > 2 ? argv[2] : "dba", SQL_NTS,
       argc > 3 ? argv[3] : "dba", SQL_NTS);
   IF_CERR_EXIT (hdbc, rc);

   rc = SQLAllocStmt (hdbc, &hstmt);
   IF_CERR_EXIT (hdbc, rc);

   rc = SQLSetStmtOption (hstmt, SQL_ROWSET_SIZE, 10);
   rc = SQLSetStmtOption (hstmt, SQL_CURSOR_TYPE, SQL_CURSOR_KEYSET_DRIVEN);

   rc = SQLExecDirect (hstmt, "select distinct name_part (KEY_TABLE, 0) as DB from DB.DBA.SYS_KEYS", SQL_NTS);
   while (SQL_SUCCESS == (rc = SQLFetch (hstmt)))
     {
       char data[128];
       SDWORD len = sizeof (data);
       IF_ERR_EXIT (hstmt, rc);
       rc = SQLGetData (hstmt, 1, SQL_C_CHAR, data, sizeof (data), &len);
       IF_ERR_EXIT (hstmt, rc);
       if (rc == SQL_SUCCESS)
	 fprintf (stdout, "%s\n", data);
     }
   IF_ERR_EXIT (hstmt, rc);
   SQLDisconnect (hdbc);
   SQLFreeConnect (hdbc);
   SQLFreeEnv (henv);

   return 0;
}