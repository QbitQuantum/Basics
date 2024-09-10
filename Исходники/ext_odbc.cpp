ODBCParam::ODBCParam(const SQLHSTMT hdl_stmt, const int i_col)
{
  type = 0;
  decimal = 0;
  nullable = 0;
  col_size = 0;

  if (!SQL_SUCCEEDED(
        SQLDescribeParam(hdl_stmt, i_col, &type,
          &col_size, &decimal, &nullable))) {
    ODBCContext::extract_error(SQL_HANDLE_STMT, hdl_stmt);
    raise_warning("unable to retrieve param information.");
  }
}