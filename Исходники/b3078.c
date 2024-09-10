int
ODBC_Execute()
{

  SQLCHAR *      Statement = "select * from BTEST where id > ?";
  SQLUINTEGER    IDArray[ARRAY_SIZE];

  SQLINTEGER     IDIndArray[ARRAY_SIZE];

  SQLUSMALLINT   i, ParamStatusArray[ARRAY_SIZE];
  SQLUINTEGER    ParamsProcessed;

  if (SQLParamOptions(hstmt, ARRAY_SIZE, &ParamsProcessed) != SQL_SUCCESS)
    {
      ODBC_Errors ("ODBC_Execute");
      return -1;
    }

  IDArray[0] = 3;  IDIndArray[0] = 0;
  IDArray[1] = 2;  IDIndArray[1] = 0;
  IDArray[2] = 1;  IDIndArray[2] = 0;

  /*    Bind the parameters in column-wise fashion. */
  if (SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 5, 0, IDArray, 0, IDIndArray) != SQL_SUCCESS)
    {
      ODBC_Errors ("ODBC_Execute");
      return -1;
    }


  /*   Execute the statement. */
  if (SQLExecDirect(hstmt, Statement, SQL_NTS) != SQL_SUCCESS)
    {
      ODBC_Errors ("ODBC_Execute");
      return -1;
    }

  /*    Check to see which sets of parameters were processed successfully. */
  printf("Parameter Sets Processed = %d\n",ParamsProcessed);
  printf("--------------------------------------\n");
  return 0;
}