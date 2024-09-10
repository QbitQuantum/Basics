/*
 * Turned into macros --- see sql-wrap.h
 */
RETCODE
backsql_BindParamStr( SQLHSTMT sth, int par_ind, char *str, int maxlen )
{
	RETCODE		rc;

	rc = SQLBindParameter( sth, (SQLUSMALLINT)par_ind, SQL_PARAM_INPUT,
			SQL_C_CHAR, SQL_VARCHAR,
         		(SQLUINTEGER)maxlen, 0, (SQLPOINTER)str,
			(SQLUINTEGER)maxlen, NULL );
	return rc;
}