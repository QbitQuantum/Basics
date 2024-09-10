SQLRETURN SQL_API
SQLForeignKeysA(SQLHSTMT StatementHandle,
		SQLCHAR *PKCatalogName,
		SQLSMALLINT NameLength1,
		SQLCHAR *PKSchemaName,
		SQLSMALLINT NameLength2,
		SQLCHAR *PKTableName,
		SQLSMALLINT NameLength3,
		SQLCHAR *FKCatalogName,
		SQLSMALLINT NameLength4,
		SQLCHAR *FKSchemaName,
		SQLSMALLINT NameLength5,
		SQLCHAR *FKTableName,
		SQLSMALLINT NameLength6)
{
	return SQLForeignKeys(StatementHandle, PKCatalogName, NameLength1,
			      PKSchemaName, NameLength2,
			      PKTableName, NameLength3,
			      FKCatalogName, NameLength4,
			      FKSchemaName, NameLength5,
			      FKTableName, NameLength6);
}