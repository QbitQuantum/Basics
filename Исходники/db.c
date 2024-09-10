/******************************************************************************
 *                                                                            *
 * Function: zbx_db_connect                                                   *
 *                                                                            *
 * Purpose: connect to the database                                           *
 *                                                                            *
 * Return value: ZBX_DB_OK - succefully connected                             *
 *               ZBX_DB_DOWN - database is down                               *
 *               ZBX_DB_FAIL - failed to connect                              *
 *                                                                            *
 ******************************************************************************/
int	zbx_db_connect(char *host, char *user, char *password, char *dbname, char *dbschema, char *dbsocket, int port)
{
	int		ret = ZBX_DB_OK;
#if defined(HAVE_IBM_DB2)
	char		*connect = NULL;
#elif defined(HAVE_ORACLE)
	char		*connect = NULL;
	sword		err = OCI_SUCCESS;
#elif defined(HAVE_POSTGRESQL)
	char		*cport = NULL;
	DB_RESULT	result;
	DB_ROW		row;
#endif

	txn_init = 1;

	assert(NULL != host);

#if defined(HAVE_IBM_DB2)
	connect = zbx_strdup(connect, "PROTOCOL=TCPIP;");
	if ('\0' != *host)
		connect = zbx_strdcatf(connect, "HOSTNAME=%s;", host);
	if (NULL != dbname && '\0' != *dbname)
		connect = zbx_strdcatf(connect, "DATABASE=%s;", dbname);
	if (0 != port)
		connect = zbx_strdcatf(connect, "PORT=%d;", port);
	if (NULL != user && '\0' != *user)
		connect = zbx_strdcatf(connect, "UID=%s;", user);
	if (NULL != password && '\0' != *password)
		connect = zbx_strdcatf(connect, "PWD=%s;", password);

	memset(&ibm_db2, 0, sizeof(ibm_db2));

	/* allocate an environment handle */
	if (SUCCEED != zbx_ibm_db2_success(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &ibm_db2.henv)))
		ret = ZBX_DB_FAIL;

	/* set attribute to enable application to run as ODBC 3.0 application; */
	/* recommended for pure IBM DB2 CLI, but not required */
	if (ZBX_DB_OK == ret && SUCCEED != zbx_ibm_db2_success(SQLSetEnvAttr(ibm_db2.henv, SQL_ATTR_ODBC_VERSION,
			(void *)SQL_OV_ODBC3, 0)))
		ret = ZBX_DB_FAIL;

	/* allocate a database connection handle */
	if (ZBX_DB_OK == ret && SUCCEED != zbx_ibm_db2_success(SQLAllocHandle(SQL_HANDLE_DBC, ibm_db2.henv,
			&ibm_db2.hdbc)))
		ret = ZBX_DB_FAIL;

	/* connect to the database */
	if (ZBX_DB_OK == ret && SUCCEED != zbx_ibm_db2_success(SQLDriverConnect(ibm_db2.hdbc, NULL, (SQLCHAR *)connect,
			SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT)))
		ret = ZBX_DB_FAIL;

	/* set autocommit on */
  	if (ZBX_DB_OK == ret && SUCCEED != zbx_ibm_db2_success(SQLSetConnectAttr(ibm_db2.hdbc, SQL_ATTR_AUTOCOMMIT,
								(SQLPOINTER)SQL_AUTOCOMMIT_ON, SQL_NTS)))
		ret = ZBX_DB_DOWN;

	/* we do not generate vendor escape clause sequences */
  	if (ZBX_DB_OK == ret && SUCCEED != zbx_ibm_db2_success(SQLSetConnectAttr(ibm_db2.hdbc, SQL_ATTR_NOSCAN,
								(SQLPOINTER)SQL_NOSCAN_ON, SQL_NTS)))
		ret = ZBX_DB_DOWN;

	/* set current schema */
	if (NULL != dbschema && '\0' != *dbschema && ZBX_DB_OK == ret)
	{
		char	*dbschema_esc;

		dbschema_esc = DBdyn_escape_string(dbschema);
		DBexecute("set current schema='%s'", dbschema_esc);
		zbx_free(dbschema_esc);
	}

	/* output error information */
	if (ZBX_DB_OK != ret)
	{
		zbx_ibm_db2_log_errors(SQL_HANDLE_ENV, ibm_db2.henv);
		zbx_ibm_db2_log_errors(SQL_HANDLE_DBC, ibm_db2.hdbc);

		zbx_db_close();
	}

	zbx_free(connect);
#elif defined(HAVE_MYSQL)
	conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, host, user, password, dbname, port, dbsocket, CLIENT_MULTI_STATEMENTS))
	{
		zabbix_errlog(ERR_Z3001, dbname, mysql_errno(conn), mysql_error(conn));
		ret = ZBX_DB_FAIL;
	}

	if (ZBX_DB_OK == ret)
	{
		if (0 != mysql_select_db(conn, dbname))
		{
			zabbix_errlog(ERR_Z3001, dbname, mysql_errno(conn), mysql_error(conn));
			ret = ZBX_DB_FAIL;
		}
	}

	if (ZBX_DB_OK == ret)
	{
		DBexecute("set names utf8");
	}

	if (ZBX_DB_FAIL == ret)
	{
		switch (mysql_errno(conn))
		{
			case CR_CONN_HOST_ERROR:
			case CR_SERVER_GONE_ERROR:
			case CR_CONNECTION_ERROR:
			case CR_SERVER_LOST:
			case CR_UNKNOWN_HOST:
			case ER_SERVER_SHUTDOWN:
			case ER_ACCESS_DENIED_ERROR:		/* wrong user or password */
			case ER_ILLEGAL_GRANT_FOR_TABLE:	/* user without any privileges */
			case ER_TABLEACCESS_DENIED_ERROR:	/* user without some privilege */
			case ER_UNKNOWN_ERROR:
				ret = ZBX_DB_DOWN;
				break;
			default:
				break;
		}
	}
#elif defined(HAVE_ORACLE)
#if defined(HAVE_GETENV) && defined(HAVE_PUTENV)
	if (NULL == getenv("NLS_LANG"))
		putenv("NLS_LANG=.UTF8");
#endif
	memset(&oracle, 0, sizeof(oracle));

	/* connection string format: [//]host[:port][/service name] */

	if ('\0' != *host)
	{
		connect = zbx_strdcatf(connect, "//%s", host);
		if (0 != port)
			connect = zbx_strdcatf(connect, ":%d", port);
		if (NULL != dbname && '\0' != *dbname)
			connect = zbx_strdcatf(connect, "/%s", dbname);
	}
	else
		ret = ZBX_DB_FAIL;

	if (ZBX_DB_OK == ret)
	{
		/* initialize environment */
		err = OCIEnvCreate((OCIEnv **)&oracle.envhp, (ub4)OCI_DEFAULT,
				(dvoid *)0, (dvoid * (*)(dvoid *,size_t))0,
				(dvoid * (*)(dvoid *, dvoid *, size_t))0,
				(void (*)(dvoid *, dvoid *))0, (size_t)0, (dvoid **)0);

		if (OCI_SUCCESS != err)
		{
			zabbix_errlog(ERR_Z3001, connect, err, zbx_oci_error(err));
			ret = ZBX_DB_FAIL;
		}
	}

	if (ZBX_DB_OK == ret)
	{
		/* allocate an error handle */
		(void)OCIHandleAlloc((dvoid *)oracle.envhp, (dvoid **)&oracle.errhp, OCI_HTYPE_ERROR,
				(size_t)0, (dvoid **)0);

		/* get the session */
		err = OCILogon2(oracle.envhp, oracle.errhp, &oracle.svchp,
				(text *)user, (ub4)(NULL != user ? strlen(user) : 0),
				(text *)password, (ub4)(NULL != password ? strlen(password) : 0),
				(text *)connect, (ub4)strlen(connect),
				OCI_DEFAULT);

		if (OCI_SUCCESS == err)
		{
			err = OCIAttrGet((void *)oracle.svchp, OCI_HTYPE_SVCCTX, (void *)&oracle.srvhp, (ub4 *)0,
					OCI_ATTR_SERVER, oracle.errhp);
		}

		if (OCI_SUCCESS != err)
		{
			zabbix_errlog(ERR_Z3001, connect, err, zbx_oci_error(err));
			ret = ZBX_DB_DOWN;
		}
	}

	if (ZBX_DB_OK == ret)
	{
		/* initialize statement handle */
		err = OCIHandleAlloc((dvoid *)oracle.envhp, (dvoid **)&oracle.stmthp, OCI_HTYPE_STMT,
				(size_t)0, (dvoid **)0);

		if (OCI_SUCCESS != err)
		{
			zabbix_errlog(ERR_Z3001, connect, err, zbx_oci_error(err));
			ret = ZBX_DB_DOWN;
		}
	}

	if (ZBX_DB_OK == ret)
		DBexecute("alter session set nls_numeric_characters='. '");

	zbx_free(connect);

	if (ZBX_DB_OK != ret)
		zbx_db_close();
#elif defined(HAVE_POSTGRESQL)
	if (0 != port)
		cport = zbx_dsprintf(cport, "%d", port);

	conn = PQsetdbLogin(host, cport, NULL, NULL, dbname, user, password);

	zbx_free(cport);

	/* check to see that the backend connection was successfully made */
	if (CONNECTION_OK != PQstatus(conn))
	{
		zabbix_errlog(ERR_Z3001, dbname, 0, PQerrorMessage(conn));
		ret = ZBX_DB_DOWN;
	}
	else
	{
		result = DBselect("select oid from pg_type where typname='bytea'");
		if (NULL != (row = DBfetch(result)))
			ZBX_PG_BYTEAOID = atoi(row[0]);
		DBfree_result(result);
	}

#ifdef HAVE_FUNCTION_PQSERVERVERSION
	ZBX_PG_SVERSION = PQserverVersion(conn);
	zabbix_log(LOG_LEVEL_DEBUG, "PostgreSQL Server version: %d", ZBX_PG_SVERSION);
#endif

	if (80100 <= ZBX_PG_SVERSION)
	{
		/* disable "nonstandard use of \' in a string literal" warning */
		DBexecute("set escape_string_warning to off");

		result = DBselect("show standard_conforming_strings");
		if (NULL != (row = DBfetch(result)))
			ZBX_PG_ESCAPE_BACKSLASH = (0 == strcmp(row[0], "off"));
		DBfree_result(result);
	}

	if (90000 <= ZBX_PG_SVERSION)
	{
		/* change the output format for values of type bytea from hex (the default) to escape */
		DBexecute("set bytea_output=escape");
	}
#elif defined(HAVE_SQLITE3)
#ifdef HAVE_FUNCTION_SQLITE3_OPEN_V2
	if (SQLITE_OK != sqlite3_open_v2(dbname, &conn, SQLITE_OPEN_READWRITE, NULL))
#else
	if (SQLITE_OK != sqlite3_open(dbname, &conn))
#endif
	{
		zabbix_errlog(ERR_Z3001, dbname, 0, sqlite3_errmsg(conn));
		sqlite3_close(conn);
		ret = ZBX_DB_DOWN;
	}
	else
	{
		char	*p, *path;

		/* do not return SQLITE_BUSY immediately, wait for N ms */
		sqlite3_busy_timeout(conn, SEC_PER_MIN * 1000);

		path = strdup(dbname);
		if (NULL != (p = strrchr(path, '/')))
			*++p = '\0';
		else
			*path = '\0';

		DBexecute("PRAGMA synchronous = 0");	/* OFF */
		DBexecute("PRAGMA temp_store = 2");	/* MEMORY */
		DBexecute("PRAGMA temp_store_directory = '%s'", path);

		zbx_free(path);
	}
#endif	/* HAVE_SQLITE3 */

	txn_init = 0;

	return ret;
}