void remove_catalogs(void)
{	
	SQLRETURN	retcode;
	void        remove_update_queue_tables(void);

    sql_db_connection = (TM_CONNECTION *)malloc(sizeof(TM_CONNECTION));

	// Allocate an environment handle
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &(sql_db_connection->henv));

	if( retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO )
	{
		/* Set the ODBC version environment attribute */
		retcode = SQLSetEnvAttr(sql_db_connection->henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
			/* Allocate a connection handle */
			retcode = SQLAllocHandle(SQL_HANDLE_DBC, sql_db_connection->henv, &(sql_db_connection->hdbc));

			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
			{
				/* Connect to data source */
				retcode = SQLConnect(sql_db_connection->hdbc, (SQLCHAR*) odbc_dsn, SQL_NTS,
					(SQLCHAR*) username, SQL_NTS,
					(SQLCHAR*) password, SQL_NTS);

				if( retcode  == SQL_ERROR )
				{
					SQLFreeHandle(SQL_HANDLE_DBC, sql_db_connection->hdbc);
					SQLFreeHandle(SQL_HANDLE_ENV, sql_db_connection->henv);
        			printf ("Error: unable to connect to SQL Server\n");
       				puts ("Ensure that the DBMS is running and that your ODBC DSN settings are correct.");
        			exit (EXIT_FAILURE);
				}
			}
			else
			{
				SQLFreeHandle(SQL_HANDLE_DBC, sql_db_connection->hdbc);
				SQLFreeHandle(SQL_HANDLE_ENV, sql_db_connection->henv);
        		printf ("Error: unable to connect to SQL Server\n");
       			puts ("Ensure that the DBMS is running and that your ODBC DSN settings are correct.");
        		exit (EXIT_FAILURE);
			}
		}
	}
	else
	{
		SQLFreeHandle(SQL_HANDLE_ENV, sql_db_connection->henv);
        printf ("Error: unable to connect to SQL Server\n");
       	puts ("Ensure that the DBMS is running and that your ODBC DSN settings are correct.");
        exit (EXIT_FAILURE);
	}

	printf ("\n\nConnected to SQL Server.\n\n");

	puts ("Removing Vigilert's catalogs will delete your Vigilert triggers,");
	puts ("triggersets, data sources, pending mail, pending OS commands, and pending notices.");
	printf ("Are you sure you want to do this (Y/N)? ");
	fgets (yesno, sizeof (yesno), stdin);
    yesno[strlen (yesno) - 1] = '\0';  // Remove trailing \n.

	if (stricmp (yesno, "y") != 0)
	{
		exit (EXIT_SUCCESS);
	}

	puts ("");

	remove_update_queue_tables();

	exec_sql_stmt("drop table vl_DataSrc");
	puts ("vl_DataSrc");

	exec_sql_stmt("drop table vl_DataSrcAtb"),
	puts ("vl_datasrcatb");

	exec_sql_stmt("drop table vl_IDTable");
	puts ("vl_idtable");

	exec_sql_stmt("drop table vl_TriggerSet");
	puts ("vl_TriggerSet");

	exec_sql_stmt("drop table vl_Trigger");
	puts ("vl_Trigger");

	exec_sql_stmt("drop table vl_TrigDataSrcReln");
	puts ("vl_TrigDataSrcReln");

	exec_sql_stmt("drop table vl_mail");
	puts ("vl_mail");

	exec_sql_stmt("drop table vl_osexec");
	puts ("vl_osexec");

	exec_sql_stmt("drop table vl_notice");
	puts ("vl_notice");

	exec_sql_stmt("drop table vl_DataSrcMtb");
	puts ("vl_DataSrcMtb");

	exec_sql_stmt("drop table vl_null_tbl");
	puts ("vl_null_tbl");

	exec_sql_stmt("drop table vl_mon_watch");
	puts ("vl_mon_watch");

	exec_sql_stmt("drop table vl_mon_update");
	puts ("vl_mon_update");

	exec_sql_stmt("drop table vl_ext_fcn_tbl");
	puts ("vl_ext_fcn_tbl");
}