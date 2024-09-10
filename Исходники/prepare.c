static int
sqlLockAndPrepare(sql * db,		/* Database handle. */
		      const char *zSql,		/* UTF-8 encoded SQL statement. */
		      int nBytes,		/* Length of zSql in bytes. */
		      int saveSqlFlag,		/* True to copy SQL text into the sql_stmt */
		      Vdbe * pOld,		/* VM being reprepared */
		      sql_stmt ** ppStmt,	/* OUT: A pointer to the prepared statement */
		      const char **pzTail)	/* OUT: End of parsed string */
{
	int rc;

	*ppStmt = 0;
	if (!sqlSafetyCheckOk(db) || zSql == 0) {
		return SQL_MISUSE;
	}
	rc = sqlPrepare(db, zSql, nBytes, saveSqlFlag, pOld, ppStmt,
			    pzTail);
	if (rc == SQL_SCHEMA) {
		sql_finalize(*ppStmt);
		rc = sqlPrepare(db, zSql, nBytes, saveSqlFlag, pOld, ppStmt,
				    pzTail);
	}
	assert(rc == SQL_OK || *ppStmt == 0);
	return rc;
}