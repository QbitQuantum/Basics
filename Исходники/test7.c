main() {
   SQLHENV env;
   SQLHDBC dbc;
   SQLHSTMT stmt;
   SQLRETURN ret; /* ODBC API return status */
   SQLSMALLINT columns; /* number of columns in result-set */
   SQLCHAR table[ 64 ];
   SQLCHAR column[ 64 ];
   SQLINTEGER type;
   SQLLEN indicator[ 3 ];
   int i;

   /* Allocate an environment handle */
   SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);

   /* We want ODBC 3 support */
   SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);

   /* Allocate a connection handle */
   SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);

   /* Connect to the DSN mydsn */
   /* You will need to change mydsn to one you have created and tested */
   SQLDriverConnect(dbc, NULL, "DSN=PostgreSQL-rupen-aws;uid=poc;pwd=****;", SQL_NTS,
                 NULL, 0, NULL, SQL_DRIVER_COMPLETE);

   /* Allocate a statement handle */
   SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
   /* Retrieve a list of columns */

   SQLColumns(stmt, NULL, 0, NULL, 0, "t1", SQL_NTS, NULL, 0);

   ret = SQLBindCol( stmt, 3, SQL_C_CHAR,
         table, sizeof( table ), &indicator[ 0 ] );
   ret = SQLBindCol( stmt, 4, SQL_C_CHAR,
         column, sizeof( column ), &indicator[ 1 ] );
   ret = SQLBindCol( stmt, 5, SQL_C_LONG, &type, 0, &indicator[ 2 ] );

   /* Fetch the data */
   while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
      printf( "%s.%s type %d\n", table, column, type );
   }
}