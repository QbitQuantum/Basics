/* get the privileges for tables that meet specified criteria */
int TbListTablePrivileges(SQLHANDLE hdbc)
{
  SQLRETURN cliRC = SQL_SUCCESS;
  int rc = 0;
  SQLHANDLE hstmt; /* statement handle */

  struct
  {
    SQLINTEGER ind;
    SQLCHAR val[129];
  }
  tbSchema, tbName, grantor, grantee, privilege;

  struct
  {
    SQLINTEGER ind;
    SQLCHAR val[4];
  }
  is_grantable;

  /* criteria look for */
  SQLCHAR tbSchemaPattern[] = "%";
  SQLCHAR tbNamePattern[] = "ORG";

  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE CLI FUNCTIONS\n");
  printf("  SQLSetConnectAttr\n");
  printf("  SQLAllocHandle\n");
  printf("  SQLTablePrivileges\n");
  printf("  SQLBindCol\n");
  printf("  SQLFetch\n");
  printf("  SQLFreeHandle\n");
  printf("TO GET PRIVILEGES FOR TABLES THAT MEET SPECIFIED CRITERIA:\n");

  /* set AUTOCOMMIT on */
  cliRC = SQLSetConnectAttr(hdbc,
                            SQL_ATTR_AUTOCOMMIT,
                            (SQLPOINTER)SQL_AUTOCOMMIT_ON,
                            SQL_NTS);
  DBC_HANDLE_CHECK(hdbc, cliRC);

  /* allocate a statement handle */
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
  DBC_HANDLE_CHECK(hdbc, cliRC);

  /* call SQLTablePrivileges */
  printf("\n  Call SQLTablePrivileges for:\n");
  printf("    tbSchemaPattern = %s\n", tbSchemaPattern);
  printf("    tbNamePattern = %s\n", tbNamePattern);

  /* get privileges associated with a table */
  cliRC = SQLTablePrivileges(hstmt,
                             NULL,
                             0,
                             tbSchemaPattern,
                             SQL_NTS,
                             tbNamePattern,
                             SQL_NTS);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* bind column 2 to variable */
  cliRC = SQLBindCol(hstmt, 2, SQL_C_CHAR, tbSchema.val, 129, &tbSchema.ind);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* bind column 3 to variable */
  cliRC = SQLBindCol(hstmt, 3, SQL_C_CHAR, tbName.val, 129, &tbName.ind);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* bind column 4 to variable */
  cliRC = SQLBindCol(hstmt,
                     4,
                     SQL_C_CHAR,
                     (SQLPOINTER)grantor.val,
                     129,
                     &grantor.ind);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* bind column 5 to variable */
  cliRC = SQLBindCol(hstmt,
                     5,
                     SQL_C_CHAR,
                     (SQLPOINTER)grantee.val,
                     129,
                     &grantee.ind);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* bind column 6 to variable */
  cliRC = SQLBindCol(hstmt,
                     6,
                     SQL_C_CHAR,
                     (SQLPOINTER)privilege.val,
                     129,
                     &privilege.ind);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* bind column 7 to variable */
  cliRC = SQLBindCol(hstmt,
                     7,
                     SQL_C_CHAR,
                     (SQLPOINTER)is_grantable.val,
                     4,
                     &is_grantable.ind);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* fetch each row and display */
  printf("\n  Current User's Privileges \n");
  printf("    Table Grantor  Grantee      Privilege  Grantable\n");
  printf("    ----- -------- ------------ ---------- ---------\n");

  /* fetch next row */
  cliRC = SQLFetch(hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  if (cliRC == SQL_NO_DATA_FOUND)
  {
    printf("\n  Data not found.\n");
  }
  while (cliRC != SQL_NO_DATA_FOUND)
  {
    printf("    %-5s", tbName.val);
    printf(" %-8s", grantor.val);
    printf(" %-12s", grantee.val);
    printf(" %-10s", privilege.val);
    printf(" %-3s\n", is_grantable.val);

    /* fetch next row */
    cliRC = SQLFetch(hstmt);
    STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  } /* endwhile */

  /* free the statement handle */
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  return rc;
} /* TbListTablePrivileges */