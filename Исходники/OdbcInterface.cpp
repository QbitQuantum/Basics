int OdbcStatement::GetColCount()
{
  SQLINTEGER colcount;
  SQLRETURN result = SQLColAttribute(mSqlStatementHandle, 1, SQL_DESC_COUNT, 0, 0, 0, &colcount);
  if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
  {
    return colcount;
  }
  else
  {
    SQLTCHAR sql_state[7];
    SQLTCHAR message_text[1024];
    GetDiag(sql_state,message_text,1024);
    TCHAR szMsg[1200];
    _stprintf(szMsg, _T( "OdbcStatement::GetColCount() - SQLColAttribute failed.\n%s"),message_text);
    throw szMsg;
  }
}