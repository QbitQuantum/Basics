SQLRETURN SQL_API SQLPrimaryKeys(
    SQLHSTMT StatementHandle, SQLCHAR *CatalogName,
    SQLSMALLINT CatalogNameSize, SQLCHAR *SchemaName,
    SQLSMALLINT SchemaNameSize, SQLCHAR *TableName, SQLSMALLINT TableNameSize)
{
    o::SQLPrimaryKeys sqlPrimaryKeys(
        StatementHandle, CatalogName, CatalogNameSize, SchemaName,
        SchemaNameSize, TableName, TableNameSize);
    return sqlPrimaryKeys();
}