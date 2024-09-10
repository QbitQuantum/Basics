int MADB_KeyTypeCount(MADB_Dbc *Connection, char *TableName, int KeyFlag)
{
  int Count= 0;
  unsigned int i;
  char StmtStr[1024];
  char *p= StmtStr;
  char Database[65];
  SQLHSTMT Stmt= NULL;
  MADB_Stmt *KeyStmt;
  
  SQLGetConnectAttr((SQLHDBC)Connection, SQL_ATTR_CURRENT_CATALOG, Database, 65, NULL);
  p+= my_snprintf(p, 1024, "SELECT * FROM ");
  if (Database)
    p+= my_snprintf(p, 1024 - strlen(p), "`%s`.", Database);
  p+= my_snprintf(p, 1024 - strlen(p), "%s LIMIT 0", TableName);
  if (SQLAllocStmt((SQLHDBC)Connection, &Stmt) == SQL_ERROR ||
      SQLPrepare(Stmt, (SQLCHAR *)StmtStr, SQL_NTS) == SQL_ERROR ||
      SQLExecute(Stmt) == SQL_ERROR ||
      SQLFetch(Stmt) == SQL_ERROR)
      goto end;
  KeyStmt= (MADB_Stmt *)Stmt;
  for (i=0; i < mysql_stmt_field_count(KeyStmt->stmt); i++)
    if (KeyStmt->stmt->fields[i].flags & KeyFlag)
      Count++;
end:
  if (Stmt)
    SQLFreeHandle(SQL_HANDLE_STMT, Stmt);
  return Count;
}