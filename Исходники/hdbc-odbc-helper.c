SQLRETURN simpleSqlTables(SQLHSTMT stmt) {
  return SQLTables(stmt, NULL, 0, NULL, 0, (SQLCHAR *)"%", 1, (SQLCHAR *)"TABLE", 5);
}