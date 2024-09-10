int maxpriceproduct(SQLHANDLE hdbc)
{
  SQLRETURN cliRC = SQL_SUCCESS;
  int rc = 0;
  SQLHANDLE hstmt; /* statement handle */
  SQLVARCHAR xmldata[3000];

  /* query to be executed */
  SQLCHAR *stmt = (SQLCHAR *)" let $prod := for $product in db2-fn:xmlcolumn('PRODUCT.DESCRIPTION')"
                   " /product/description" 
	           " order by $product/price return $product"
                   " return <product> {$prod[1]/name} </product>";

  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
  DBC_HANDLE_CHECK(hdbc, cliRC);

  /* Set the attribute SQL_ATTR_XQUERY_STATEMENT to indicate that the query is an XQuery */
  rc = SQLSetStmtAttr(hstmt, SQL_ATTR_XQUERY_STATEMENT, (SQLPOINTER)SQL_TRUE, SQL_NTS);
  printf("%d", rc);

  if (rc != 0)
  {
    return rc;
  }
 
  printf("\n  Directly execute the statement\n");
  printf("    %s\n", stmt);

  /* directly execute the statement */
  cliRC = SQLExecDirect(hstmt, stmt, SQL_NTS);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* Bind column 1 to variable */
  cliRC = SQLBindCol(hstmt, 1, SQL_C_CHAR, &xmldata, 1000, NULL);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  
  /* Fetch each row and display */
  cliRC = SQLFetch(hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  if (cliRC == SQL_NO_DATA_FOUND)
  {
    printf("\n  Data not found.\n");
  }
   else 
   printf("%s \n\n",xmldata);

  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* free the statement handle */
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  return rc;
} /* maxpriceproduct */