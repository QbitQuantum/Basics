static void
connect_to_db(char *dsn)
{
	SQLRETURN	ret;
	char		errmsg[500];
	SQLSMALLINT textlen;
	char		sqlstate[20];

	SQLAllocHandle(SQL_HANDLE_DBC, env, &conn);

	ret = SQLDriverConnect(conn, NULL, (SQLCHAR *) dsn, SQL_NTS, NULL, 0, NULL,
						   SQL_DRIVER_NOPROMPT);
	if (!SQL_SUCCEEDED(ret))
	{
		printf("connection to %s failed\n", dsn);

		ret = SQLGetDiagRec(SQL_HANDLE_DBC, conn, 1, sqlstate, NULL,
							errmsg, sizeof(errmsg), &textlen);
		if (ret == SQL_INVALID_HANDLE)
			printf("Invalid handle\n");
		else if (SQL_SUCCEEDED(ret))
			printf("%s=%s\n", sqlstate, errmsg);
		exit(1);
	}

	printf("connected to %s\n", dsn);

	ret = SQLAllocHandle(SQL_HANDLE_STMT, conn, &hstmt);
	if (!SQL_SUCCEEDED(ret))
	{
		printf("SQLAllocHandle failed\n");
		exit(1);
	}
}