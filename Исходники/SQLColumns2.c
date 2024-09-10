int print_columns(char *param_TableName)
{
	char *TableType = NULL;
	char schema[256] = { '\0', '\0', '\0' };
	char *schema_ptr = NULL;
	char *catalog_ptr = NULL;
	char TableName[129];
	char ColumnName[129];
	SQLSMALLINT ColumnType;
	char TableSchema[256];
	char TableCatalog[256];
	SQLSMALLINT schema_len, catalog_len, tname_len;
	SQLINTEGER tname_size, schema_size, catalog_size, cname_size,
	    ctype_size;

	SQLHANDLE StmtHandle = NULL;
	SQLRETURN rc;
	int ret_len;
	int numret = 0;

	int i;
	int l, RemoteFilter;

	if (!param_TableName) {
		return -1;
	}

	/* Allocate An SQL Statement Handle */
	rc = SQLAllocHandle(SQL_HANDLE_STMT, ConHandle, &StmtHandle);
	if (rc != SQL_SUCCESS) {
		printf("SQLAllocHandle call failed in print_columns on %s\n",
		       param_TableName);
		LogODBCError(rc, SQL_HANDLE_DBC, ConHandle);
		return -1;
	}

	catalog_ptr = NULL;
	strcpy(schema, Get_UserName());
	schema_len = strlen(schema);
	for (i = 0; i < schema_len; i++) {
		schema[i] = (char)toupper(schema[i]);
	}
	schema_ptr = schema;

	tname_len = (SQLSMALLINT) strlen(param_TableName);

	RemoteFilter = 1;
	schema_len = (SQLSMALLINT) (schema_ptr ? strlen(schema_ptr) : 0);
	catalog_len = (SQLSMALLINT) (catalog_ptr ? strlen(catalog_ptr) : 0);

	rc = SQLColumns(StmtHandle,
			(RemoteFilter ? catalog_ptr : NULL), catalog_len,
			(RemoteFilter ? schema_ptr : NULL), schema_len,
			param_TableName, tname_len, NULL, 0);

	if (rc != SQL_SUCCESS) {
		printf("SQLColumns call failed in print_columns on %s.%s.%s\n",
		       (catalog_ptr ? catalog_ptr : "%"),
		       (schema_ptr ? schema_ptr : "%"), param_TableName);
		LogODBCError(rc, SQL_HANDLE_STMT, StmtHandle);
		return -5;
	}

	rc = SQLBindCol(StmtHandle, 5, SQL_SMALLINT, (SQLPOINTER)
			& ColumnType, sizeof(ColumnType), &ctype_size);
	if (rc != SQL_SUCCESS) {
		printf
		    ("SQLBindCol (column type) call failed in print_columns on %s.%s.%s\n",
		     (catalog_ptr ? catalog_ptr : "%"),
		     (schema_ptr ? schema_ptr : "%"), param_TableName);

		LogODBCError(rc, SQL_HANDLE_STMT, StmtHandle);
		return -6;
	}

	rc = SQLBindCol(StmtHandle, 4, SQL_C_CHAR, (SQLPOINTER)
			& ColumnName, sizeof(ColumnName), &cname_size);
	if (rc != SQL_SUCCESS) {
		printf
		    ("SQLBindCol (column name) call failed in print_columns on %s.%s.%s\n",
		     (catalog_ptr ? catalog_ptr : "%"),
		     (schema_ptr ? schema_ptr : "%"), param_TableName);

		LogODBCError(rc, SQL_HANDLE_STMT, StmtHandle);
		return -7;
	}

	rc = SQLBindCol(StmtHandle, 3, SQL_C_CHAR, (SQLPOINTER)
			& TableName, sizeof(TableName), &tname_size);
	if (rc != SQL_SUCCESS) {
		printf
		    ("SQLBindCol (table name) call failed in print_columns on %s.%s.%s\n",
		     (catalog_ptr ? catalog_ptr : "%"),
		     (schema_ptr ? schema_ptr : "%"), param_TableName);

		LogODBCError(rc, SQL_HANDLE_STMT, StmtHandle);
		return -8;
	}

	rc = SQLBindCol(StmtHandle, 2, SQL_C_CHAR, (SQLPOINTER)
			& TableSchema, sizeof(TableSchema), &schema_size);
	if (rc != SQL_SUCCESS) {
		printf
		    ("SQLBindCol (schema) call failed in print_columns on %s.%s.%s\n",
		     (catalog_ptr ? catalog_ptr : "%"),
		     (schema_ptr ? schema_ptr : "%"), param_TableName);
		LogODBCError(rc, SQL_HANDLE_STMT, StmtHandle);
		return -9;
	}

	rc = SQLBindCol(StmtHandle, 1, SQL_C_CHAR, (SQLPOINTER)
			& TableCatalog, sizeof(TableCatalog), &catalog_size);
	if (rc != SQL_SUCCESS) {
		printf
		    ("SQLBindCol (catalog) call failed in print_columns on %s.%s.%s\n",
		     (catalog_ptr ? catalog_ptr : "%"),
		     (schema_ptr ? schema_ptr : "%"), param_TableName);
		LogODBCError(rc, SQL_HANDLE_STMT, StmtHandle);
		return -10;
	}

	/* loop over the result set */

	ret_len = 0;
	rc = SQL_SUCCESS;
	l = 0;

	while (rc == SQL_SUCCESS) {
		ColumnName[0] = '\0';
		TableName[0] = '\0';
		TableSchema[0] = '\0';
		TableCatalog[0] = '\0';
		l++;
		rc = SQLFetch(StmtHandle);
		if (rc != SQL_SUCCESS && rc != SQL_NO_DATA) {
			printf
			    ("SQLFetch call number %d failed (%d) in print_columns on %s.%s.%s\n",
			     l, rc, (catalog_ptr ? catalog_ptr : "%"),
			     (schema_ptr ? schema_ptr : "%"), param_TableName);
			LogODBCError(rc, SQL_HANDLE_STMT, StmtHandle);
			return -11;
		}
		/* only permit exact matches! */
		if (rc != SQL_NO_DATA) {
			if ((strcmp(param_TableName, TableName) == 0) &&
			    ((catalog_ptr == NULL)
			     || (strcmp(catalog_ptr, TableCatalog) == 0))
			    && ((schema_ptr == NULL)
				|| (strcmp(schema_ptr, TableSchema) == 0))) {
				numret++;
				VERBOSE
				    ("SQLColumns returned a match %s.%s.%s. Column name is %s\n",
				     TableCatalog, TableSchema, TableName,
				     ColumnName);
			} else {
				/*printf("SQLColumns returned a non-match %s.%s.%s\n",TableCatalog,TableSchema,TableName); */

			}
		}
	}

	VERBOSE("print_columns found %d matching columns:\n", numret);

	SQLFreeHandle(SQL_HANDLE_STMT, StmtHandle);

	if (rc == SQL_NO_DATA)
		return SQL_SUCCESS;
	return -1;

}