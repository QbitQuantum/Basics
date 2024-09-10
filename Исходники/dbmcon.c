/* connect to two databases using a Type 2 connection with 
   two-phase commit */
int TwoConnType2TwoPhaseUse(SQLHANDLE henv,
                            char dbAlias1[],
                            char dbAlias2[],
                            char user1[],
                            char pswd1[],
                            char user2[],
                            char pswd2[])
{
  SQLRETURN cliRC = SQL_SUCCESS;
  int rc = 0;
  SQLHANDLE hdbc1, hdbc2; /* connection handles */
  SQLHANDLE hstmt1, hstmt2, hstmt3, hstmt4; /* statement handles */
  SQLHANDLE hstmt5, hstmt6, hstmt7, hstmt8; /* statement handles */

  struct
  {
    SQLINTEGER ind;
    SQLSMALLINT val;
  }
  rownumber; /* variable to be bound to the ROW column */

  struct
  {
    SQLINTEGER ind;
    SQLCHAR val[10];
  }
  value; /* variable to be bound to the VALUE column */

  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE CLI FUNCTIONS\n");
  printf("  SQLAllocHandle\n");
  printf("  SQLSetConnectAttr\n");
  printf("  SQLConnect\n");
  printf("  SQLExecDirect\n");
  printf("  SQLEndTran\n");
  printf("  SQLBindCol\n");
  printf("  SQLFetch\n");
  printf("  SQLDisconnect\n");
  printf("  SQLFreeHandle\n");
  printf("TO PERFORM TRANSACTIONS ON TWO CONNECTIONS\n");
  printf("USING TYPE 2 CONNECT WITH TWO-PHASE COMMIT:\n");

  /* allocate the first database connection handle */
  cliRC = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc1);
  DBC_HANDLE_CHECK(hdbc1, cliRC);

  /* allocate the second database connection handle */
  cliRC = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc2);
  DBC_HANDLE_CHECK(hdbc2, cliRC);

  /* set TYPE 2 CONNECT with two-phase commit for the both connections */
  printf("\n  Set TYPE 2 CONNECT two-phase commit for both connections.\n");
  cliRC = SQLSetConnectAttr(hdbc1,
                            SQL_ATTR_CONNECTTYPE,
                            (SQLPOINTER)SQL_COORDINATED_TRANS,
                            SQL_NTS);
  DBC_HANDLE_CHECK(hdbc1, cliRC);

  cliRC = SQLSetConnectAttr(hdbc1,
                            SQL_ATTR_SYNC_POINT,
                            (SQLPOINTER)SQL_TWOPHASE,
                            SQL_NTS);
  DBC_HANDLE_CHECK(hdbc1, cliRC);

  cliRC = SQLSetConnectAttr(hdbc2,
                            SQL_ATTR_CONNECTTYPE,
                            (SQLPOINTER)SQL_COORDINATED_TRANS,
                            SQL_NTS);
  DBC_HANDLE_CHECK(hdbc2, cliRC);
  cliRC = SQLSetConnectAttr(hdbc2,
                            SQL_ATTR_SYNC_POINT,
                            (SQLPOINTER)SQL_TWOPHASE,
                            SQL_NTS);
  DBC_HANDLE_CHECK(hdbc2, cliRC);

  printf("\n  Connect to '%s' database on connection 1.\n", dbAlias1);

  /* connect to the first database */
  cliRC = SQLConnect(hdbc1,
                     (SQLCHAR *)dbAlias1,
                     SQL_NTS,
                     (SQLCHAR *)user1,
                     SQL_NTS,
                     (SQLCHAR *)pswd1,
                     SQL_NTS);
  DBC_HANDLE_CHECK(hdbc1, cliRC);

  printf("  Connect to '%s' database on connection 2.\n", dbAlias2);

  /* connect to the second database */
  cliRC = SQLConnect(hdbc2,
                     (SQLCHAR *)dbAlias2,
                     SQL_NTS,
                     (SQLCHAR *)user2,
                     SQL_NTS,
                     (SQLCHAR *)pswd2,
                     SQL_NTS);
  DBC_HANDLE_CHECK(hdbc2, cliRC);

  /*********   Start using the connections  ************************/

  /* set AUTOCOMMIT OFF for both connections */
  printf("\n  Turn auto-commit OFF for connection 1.\n");
  cliRC = SQLSetConnectAttr(hdbc1,
                            SQL_ATTR_AUTOCOMMIT,
                            (SQLPOINTER)SQL_AUTOCOMMIT_OFF,
                            SQL_NTS);
  DBC_HANDLE_CHECK(hdbc1, cliRC);

  printf("  Turn auto-commit OFF for connection 2.\n");
  cliRC = SQLSetConnectAttr(hdbc2,
                            SQL_ATTR_AUTOCOMMIT,
                            (SQLPOINTER)SQL_AUTOCOMMIT_OFF,
                            SQL_NTS);
  DBC_HANDLE_CHECK(hdbc2, cliRC);

  /* allocate all statement handles */
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, &hstmt1);
  DBC_HANDLE_CHECK(hdbc1, cliRC);
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc2, &hstmt2);
  DBC_HANDLE_CHECK(hdbc2, cliRC);
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, &hstmt3);
  DBC_HANDLE_CHECK(hdbc1, cliRC);
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc2, &hstmt4);
  DBC_HANDLE_CHECK(hdbc2, cliRC);
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, &hstmt5);
  DBC_HANDLE_CHECK(hdbc1, cliRC);
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc2, &hstmt6);
  DBC_HANDLE_CHECK(hdbc2, cliRC);
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, &hstmt7);
  DBC_HANDLE_CHECK(hdbc1, cliRC);
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc2, &hstmt8);
  DBC_HANDLE_CHECK(hdbc2, cliRC);

  printf("\n  Perform statements on both connections:\n");
  printf("\n  Create table1 on connection 1.\n");

  /* create a table on connection 1 */
  cliRC = SQLExecDirect(hstmt1,
                        (SQLCHAR *)"CREATE TABLE table1(row INTEGER, value CHAR(10))",
                        SQL_NTS);
  MC_STMT_HANDLE_CHECK(hstmt1, henv, cliRC);

  printf("  Create table1 on connection 2.\n");

  /* create a table on connection 2 */
  cliRC = SQLExecDirect(hstmt2,
                        (SQLCHAR *)"CREATE TABLE table1(row INTEGER, value CHAR(10))",
                        SQL_NTS);
  MC_STMT_HANDLE_CHECK(hstmt2, henv, cliRC);

  printf("    Commit the transaction.\n");

  /* end the transaction */
  cliRC = SQLEndTran(SQL_HANDLE_DBC, hdbc1, SQL_COMMIT);
  DBC_HANDLE_CHECK(hdbc1, cliRC);

  /* insert values into both tables */
  printf("\n  Insert values (1, 'abc') into table1 on connection 1.\n");
  cliRC = SQLExecDirect(hstmt3,
                        (SQLCHAR *)"INSERT INTO table1 VALUES (1, 'abc')",
                        SQL_NTS);
  MC_STMT_HANDLE_CHECK(hstmt3, henv, cliRC);

  printf("  Insert values (1, 'def') into table1 on connection 2.\n");
  cliRC = SQLExecDirect(hstmt4,
                        (SQLCHAR *)"INSERT INTO table1 VALUES (1, 'def')",
                        SQL_NTS);
  MC_STMT_HANDLE_CHECK(hstmt4, henv, cliRC);
  
  printf("    Commit the transaction.\n");
  /* end the transaction */
  cliRC = SQLEndTran(SQL_HANDLE_DBC, hdbc1, SQL_COMMIT);
  DBC_HANDLE_CHECK(hdbc1, cliRC);

  printf("\n  Check values inserted on both connections:\n");

  /* check values successfully inserted on connection 1 */
  cliRC = SQLExecDirect(hstmt5,
                        (SQLCHAR *)"SELECT * FROM table1",
                        SQL_NTS);
  MC_STMT_HANDLE_CHECK(hstmt5, henv, cliRC);

  /* bind column 1 to variable */
  cliRC = SQLBindCol(hstmt5,
                     1,
                     SQL_C_SHORT,
                     &rownumber.val,
                     0,
                     &rownumber.ind);
  MC_STMT_HANDLE_CHECK(hstmt5, henv, cliRC);

  /* bind column 2 to variable */
  cliRC = SQLBindCol(hstmt5,
                     2,
                     SQL_C_CHAR,
                     value.val,
                     10,
                     &value.ind);
  MC_STMT_HANDLE_CHECK(hstmt5, henv, cliRC);

  printf("\n  CONNECTION 1");
  printf("\n  Fetch each row and display.\n");
  printf("    ROW #    VALUE     \n");
  printf("    -------- -------------\n");

  /* fetch each row and display */
  cliRC = SQLFetch(hstmt5);
  MC_STMT_HANDLE_CHECK(hstmt5, henv, cliRC);

  if (cliRC == SQL_NO_DATA_FOUND)
  {
    printf("\n  Data not found.\n");
  }
  while (cliRC != SQL_NO_DATA_FOUND)
  {
    printf("    %-8d %-10.10s \n", rownumber.val, value.val);

    /* fetch next row */
    cliRC = SQLFetch(hstmt5);
    MC_STMT_HANDLE_CHECK(hstmt5, henv, cliRC);
  }

  /* Check values successfully inserted on connection 2 */
  cliRC = SQLExecDirect(hstmt6,
                        (SQLCHAR *)"SELECT * FROM table1",
                        SQL_NTS);
  MC_STMT_HANDLE_CHECK(hstmt6, henv, cliRC);

  /* bind column 1 to variable */
  cliRC = SQLBindCol(hstmt6,
                     1,
                     SQL_C_SHORT,
                     &rownumber.val,
                     0,
                     &rownumber.ind);
  MC_STMT_HANDLE_CHECK(hstmt6, henv, cliRC);

  /* bind column 2 to variable */
  cliRC = SQLBindCol(hstmt6,
                     2,
                     SQL_C_CHAR,
                     value.val,
                     10,
                     &value.ind);
  MC_STMT_HANDLE_CHECK(hstmt6, henv, cliRC);

  printf("\n  CONNECTION 2\n");
  printf("  Fetch each row and display.\n");
  printf("    ROW #    VALUE     \n");
  printf("    -------- -------------\n");

  /* fetch each row and display */
  cliRC = SQLFetch(hstmt6);
  MC_STMT_HANDLE_CHECK(hstmt6, henv, cliRC);

  if (cliRC == SQL_NO_DATA_FOUND)
  {
    printf("\n  Data not found.\n");
  }
  while (cliRC != SQL_NO_DATA_FOUND)
  {
    printf("    %-8d %-10.10s \n", rownumber.val, value.val);

    /* fetch next row */
    cliRC = SQLFetch(hstmt6);
    MC_STMT_HANDLE_CHECK(hstmt6, henv, cliRC);
  }

  printf("\n  Drop table1 on connection 1.\n");

  cliRC = SQLExecDirect(hstmt7,
                        (SQLCHAR *)"DROP TABLE table1",
                        SQL_NTS);
  MC_STMT_HANDLE_CHECK(hstmt7, henv, cliRC);

  printf("  Drop table1 on connection 2.\n");

  cliRC = SQLExecDirect(hstmt8,
                        (SQLCHAR *)"DROP TABLE table1",
                        SQL_NTS);
  MC_STMT_HANDLE_CHECK(hstmt8, henv, cliRC);
  
  printf("    Commit the transaction.\n");
  /* end the transaction */
  cliRC = SQLEndTran(SQL_HANDLE_DBC, hdbc1, SQL_COMMIT);
  DBC_HANDLE_CHECK(hdbc1, cliRC);

  
  /* free all statement handles */
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt1);
  MC_STMT_HANDLE_CHECK(hstmt1, henv, cliRC);
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt2);
  MC_STMT_HANDLE_CHECK(hstmt2, henv, cliRC);
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt3);
  MC_STMT_HANDLE_CHECK(hstmt3, henv, cliRC);
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt4);
  MC_STMT_HANDLE_CHECK(hstmt4, henv, cliRC);
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt5);
  MC_STMT_HANDLE_CHECK(hstmt5, henv, cliRC);
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt6);
  MC_STMT_HANDLE_CHECK(hstmt6, henv, cliRC);
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt7);
  MC_STMT_HANDLE_CHECK(hstmt7, henv, cliRC);
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt8);
  MC_STMT_HANDLE_CHECK(hstmt8, henv, cliRC);

  /*********   Stop using the connections  *************************/

  printf("\n  Disconnect from '%s' database.\n", dbAlias1);

  /* disconnect from the first database */
  cliRC = SQLDisconnect(hdbc1);
  DBC_HANDLE_CHECK(hdbc1, cliRC);

  printf("  Disconnect from '%s' database.\n", dbAlias2);

  /* disconnect from the second database */
  cliRC = SQLDisconnect(hdbc2);
  DBC_HANDLE_CHECK(hdbc2, cliRC);

  /* free the handle for connection 1 */
  cliRC = SQLFreeHandle(SQL_HANDLE_DBC, hdbc1);
  DBC_HANDLE_CHECK(hdbc1, cliRC);

  /* free the handle for connection 2 */
  cliRC = SQLFreeHandle(SQL_HANDLE_DBC, hdbc2);
  DBC_HANDLE_CHECK(hdbc2, cliRC);

  return 0;
} /* TwoConnType2TwoPhaseUse */