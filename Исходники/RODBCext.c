/**
 * Fill cols data structure with parameters info and bind
 * query parameters to cols data fields.
 *
 * A query has to be already prepared using SQLPrepare()
 *
 * On error ODBC handle structure resources are cleared and error messages
 * are added to the error list.
 *
 * @param thisHandle ODBC handle structure with already prepared query
 * @param data data.frame-like structure with query data (columns refer
 *   to query parameters, rows to query executions) - used to determine
 *   query params C types
 * @param vtest debug level: 
 *   0-no debug, 
 *   1-verbose, 
 *   2-verbose with no query execution
 * @retval 1 on success, -1 on error
 */
SQLRETURN BindParameters(pRODBCHandle thisHandle, SEXP data){
  SQLRETURN res = 0;
  SQLSMALLINT nparams, col;

  /* Check the number of Query parameters */
  res = SQLNumParams(thisHandle->hStmt, &nparams);
  SQL_RESULT_CHECK(res, thisHandle, _("[RODBCext] Error: SQLNumParams failed"), res);
  if(nparams > 0 && nparams != LENGTH(data)){
  	SQL_RESULT_CHECK(
      SQL_ERROR, 
      thisHandle, 
      _("[RODBCext] Error: Number of parameters in query do not match number of columns in data"), 
      res
    );
  }
  
  cachenbind_free(thisHandle);
  thisHandle->ColData = Calloc(nparams, COLUMNS);
  thisHandle->nAllocated = nparams;

  for(col = 0; col < nparams; col++) {
    COLUMNS *column = &(thisHandle->ColData[col]);
    column->ColName[0] = '\0'; /* We don't know parameter name but we really don't need to */

    res = SQLDescribeParam(thisHandle->hStmt, col + 1, &column->DataType, 
          &column->ColSize, &column->DecimalDigits, &column->Nullable);
    /* ODBC driver does not support SQLDescribeParam - try to use default values and rely on the ODBC casting */
    if(res != SQL_SUCCESS && res != SQL_SUCCESS_WITH_INFO){
      switch(TYPEOF(VECTOR_ELT(data, col))) {
        case REALSXP:
          column->DataType = SQL_DOUBLE;
          column->ColSize = DOUBLE_COL_SIZE;
          break;
        case INTSXP:
          column->DataType = SQL_INTEGER;
          break;
        default:
          column->DataType = SQL_VARCHAR;
          column->ColSize = COLMAX;
          break;
      }
    }

    /* Bind parameter */
    switch(TYPEOF(VECTOR_ELT(data, col))) {
      case REALSXP:
        res = SQLBindParameter(
          thisHandle->hStmt,
          col + 1, SQL_PARAM_INPUT, SQL_C_DOUBLE,
          column->DataType, 
          column->ColSize,
          column->DecimalDigits,
          column->RData,  
          0,              
          column->IndPtr
        );
        break;
      case INTSXP:
        res = SQLBindParameter(
          thisHandle->hStmt,
          col + 1, SQL_PARAM_INPUT, SQL_C_SLONG,
          column->DataType,
          column->ColSize,
          column->DecimalDigits,
          column->IData,
          0,
          column->IndPtr
        );
        break;
      default:
        if(column->pData){
          Free(column->pData);
        }
        column->pData = Calloc(column->ColSize + 1, char);
        res = SQLBindParameter(
          thisHandle->hStmt,
          col + 1, SQL_PARAM_INPUT, SQL_C_CHAR,
          column->DataType,
          column->ColSize,
          column->DecimalDigits,
          column->pData,
          0,
          column->IndPtr
        );
        break;
    }
    SQL_RESULT_CHECK(res, thisHandle, _("[RODBCext] Error: SQLBindParameter failed"), res);
  }
  return 1;
}