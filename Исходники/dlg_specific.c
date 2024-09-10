void
getDSNinfo(ConnInfo *ci, char overwrite)
{
	CSTR	func = "getDSNinfo";
	char	   *DSN = ci->dsn;
	char		encoded_item[LARGE_REGISTRY_LEN],
				temp[SMALL_REGISTRY_LEN];

/*
 *	If a driver keyword was present, then dont use a DSN and return.
 *	If DSN is null and no driver, then use the default datasource.
 */
	mylog("%s: DSN=%s overwrite=%d\n", func, DSN, overwrite);
	if (DSN[0] == '\0')
	{
		if (ci->drivername[0] != '\0')
			return;
		else
			strncpy_null(DSN, INI_DSN, sizeof(ci->dsn));
	}

	/* brute-force chop off trailing blanks... */
	while (*(DSN + strlen(DSN) - 1) == ' ')
		*(DSN + strlen(DSN) - 1) = '\0';

	if (ci->drivername[0] == '\0' || overwrite)
	{
		getDriverNameFromDSN(DSN, ci->drivername, sizeof(ci->drivername));
		if (ci->drivername[0] && stricmp(ci->drivername, DBMS_NAME))
			getCommonDefaults(ci->drivername, ODBCINST_INI, ci);
	}

	/* Proceed with getting info for the given DSN. */

	if (ci->desc[0] == '\0' || overwrite)
		SQLGetPrivateProfileString(DSN, INI_KDESC, "", ci->desc, sizeof(ci->desc), ODBC_INI);

	if (ci->server[0] == '\0' || overwrite)
		SQLGetPrivateProfileString(DSN, INI_SERVER, "", ci->server, sizeof(ci->server), ODBC_INI);

	if (ci->database[0] == '\0' || overwrite)
		SQLGetPrivateProfileString(DSN, INI_DATABASE, "", ci->database, sizeof(ci->database), ODBC_INI);

	if (ci->username[0] == '\0' || overwrite)
		SQLGetPrivateProfileString(DSN, INI_USERNAME, "", ci->username, sizeof(ci->username), ODBC_INI);

	if (ci->password[0] == '\0' || overwrite)
	{
		SQLGetPrivateProfileString(DSN, INI_PASSWORD, "", encoded_item, sizeof(encoded_item), ODBC_INI);
		decode(encoded_item, ci->password, sizeof(ci->password));
	}

	if (ci->port[0] == '\0' || overwrite)
		SQLGetPrivateProfileString(DSN, INI_PORT, "", ci->port, sizeof(ci->port), ODBC_INI);

	if (ci->onlyread[0] == '\0' || overwrite)
		SQLGetPrivateProfileString(DSN, INI_READONLY, "", ci->onlyread, sizeof(ci->onlyread), ODBC_INI);

	if (ci->show_oid_column[0] == '\0' || overwrite)
		SQLGetPrivateProfileString(DSN, INI_SHOWOIDCOLUMN, "", ci->show_oid_column, sizeof(ci->show_oid_column), ODBC_INI);

	if (ci->fake_oid_index[0] == '\0' || overwrite)
		SQLGetPrivateProfileString(DSN, INI_FAKEOIDINDEX, "", ci->fake_oid_index, sizeof(ci->fake_oid_index), ODBC_INI);

	if (ci->row_versioning[0] == '\0' || overwrite)
		SQLGetPrivateProfileString(DSN, INI_ROWVERSIONING, "", ci->row_versioning, sizeof(ci->row_versioning), ODBC_INI);

	if (ci->show_system_tables[0] == '\0' || overwrite)
		SQLGetPrivateProfileString(DSN, INI_SHOWSYSTEMTABLES, "", ci->show_system_tables, sizeof(ci->show_system_tables), ODBC_INI);

	if (ci->protocol[0] == '\0' || overwrite)
	{
		char	*ptr;
		SQLGetPrivateProfileString(DSN, INI_PROTOCOL, "", ci->protocol, sizeof(ci->protocol), ODBC_INI);
		if (ptr = strchr(ci->protocol, '-'), NULL != ptr)
		{
			*ptr = '\0';
			if (overwrite || ci->rollback_on_error < 0)
			{
				ci->rollback_on_error = atoi(ptr + 1);
				mylog("rollback_on_error=%d\n", ci->rollback_on_error);
			}
		}
	}

	if (ci->conn_settings[0] == '\0' || overwrite)
	{
		SQLGetPrivateProfileString(DSN, INI_CONNSETTINGS, "", encoded_item, sizeof(encoded_item), ODBC_INI);
		decode(encoded_item, ci->conn_settings, sizeof(ci->conn_settings));
	}

	if (ci->translation_dll[0] == '\0' || overwrite)
		SQLGetPrivateProfileString(DSN, INI_TRANSLATIONDLL, "", ci->translation_dll, sizeof(ci->translation_dll), ODBC_INI);

	if (ci->translation_option[0] == '\0' || overwrite)
		SQLGetPrivateProfileString(DSN, INI_TRANSLATIONOPTION, "", ci->translation_option, sizeof(ci->translation_option), ODBC_INI);

	if (ci->disallow_premature < 0 || overwrite)
	{
		SQLGetPrivateProfileString(DSN, INI_DISALLOWPREMATURE, "", temp, sizeof(temp), ODBC_INI);
		if (temp[0])
			ci->disallow_premature = atoi(temp);
	}

	if (ci->allow_keyset < 0 || overwrite)
	{
		SQLGetPrivateProfileString(DSN, INI_UPDATABLECURSORS, "", temp, sizeof(temp), ODBC_INI);
		if (temp[0])
			ci->allow_keyset = atoi(temp);
	}

	if (ci->lf_conversion < 0 || overwrite)
	{
		SQLGetPrivateProfileString(DSN, INI_LFCONVERSION, "", temp, sizeof(temp), ODBC_INI);
		if (temp[0])
			ci->lf_conversion = atoi(temp);
	}

	if (ci->true_is_minus1 < 0 || overwrite)
	{
		SQLGetPrivateProfileString(DSN, INI_TRUEISMINUS1, "", temp, sizeof(temp), ODBC_INI);
		if (temp[0])
			ci->true_is_minus1 = atoi(temp);
	}

	if (ci->int8_as < -100 || overwrite)
	{
		SQLGetPrivateProfileString(DSN, INI_INT8AS, "", temp, sizeof(temp), ODBC_INI);
		if (temp[0])
			ci->int8_as = atoi(temp);
	}

	if (ci->bytea_as_longvarbinary < 0 || overwrite)
	{
		SQLGetPrivateProfileString(DSN, INI_BYTEAASLONGVARBINARY, "", temp, sizeof(temp), ODBC_INI);
		if (temp[0])
			ci->bytea_as_longvarbinary = atoi(temp);
	}

	if (ci->use_server_side_prepare < 0 || overwrite)
	{
		SQLGetPrivateProfileString(DSN, INI_USESERVERSIDEPREPARE, "", temp, sizeof(temp), ODBC_INI);
		if (temp[0])
			ci->use_server_side_prepare = atoi(temp);
	}

	if (ci->lower_case_identifier < 0 || overwrite)
	{
		SQLGetPrivateProfileString(DSN, INI_LOWERCASEIDENTIFIER, "", temp, sizeof(temp), ODBC_INI);
		if (temp[0])
			ci->lower_case_identifier = atoi(temp);
	}

	if (ci->greenplum < 0 || overwrite)
	{
		SQLGetPrivateProfileString(DSN, INI_GREENPLUM, "", temp, sizeof(temp), ODBC_INI);
		if (temp[0])
			ci->greenplum = atoi(temp);
	}

	if (ci->gssauth_use_gssapi < 0 || overwrite)
	{
		SQLGetPrivateProfileString(DSN, INI_GSSAUTHUSEGSSAPI, "", temp, sizeof(temp), ODBC_INI);
		if (temp[0])
			ci->gssauth_use_gssapi = atoi(temp);
	}

	if (ci->sslmode[0] == '\0' || overwrite)
		SQLGetPrivateProfileString(DSN, INI_SSLMODE, "", ci->sslmode, sizeof(ci->sslmode), ODBC_INI);

#ifdef	_HANDLE_ENLIST_IN_DTC_
	if (ci->xa_opt < 0 || overwrite)
	{
		SQLGetPrivateProfileString(DSN, INI_XAOPT, "", temp, sizeof(temp), ODBC_INI);
		if (temp[0])
			ci->xa_opt = atoi(temp);
	}
#endif /* _HANDLE_ENLIST_IN_DTC_ */

	/* Force abbrev connstr or bde */
	SQLGetPrivateProfileString(DSN, INI_EXTRAOPTIONS, "",
					temp, sizeof(temp), ODBC_INI);
	if (temp[0])
	{
		UInt4	val = 0;

		sscanf(temp, "%x", &val);
		replaceExtraOptions(ci, val, overwrite);
		mylog("force_abbrev=%d bde=%d cvt_null_date=%d\n", ci->force_abbrev_connstr, ci->bde_environment, ci->cvt_null_date_string);
	}

	/* Allow override of odbcinst.ini parameters here */
	getCommonDefaults(DSN, ODBC_INI, ci);

	qlog("DSN info: DSN='%s',server='%s',port='%s',dbase='%s',user='******',passwd='%s'\n",
		 DSN,
		 ci->server,
		 ci->port,
		 ci->database,
		 ci->username,
		 ci->password ? "xxxxx" : "");
	qlog("          onlyread='%s',protocol='%s',showoid='%s',fakeoidindex='%s',showsystable='%s'\n",
		 ci->onlyread,
		 ci->protocol,
		 ci->show_oid_column,
		 ci->fake_oid_index,
		 ci->show_system_tables);

	if (get_qlog())
	{
		char	*enc = (char *) check_client_encoding(ci->conn_settings);

		qlog("          conn_settings='%s', conn_encoding='%s'\n", ci->conn_settings,
			NULL != enc ? enc : "(null)");
		if (NULL != enc)
			free(enc);
		qlog("          translation_dll='%s',translation_option='%s'\n",
		 	ci->translation_dll,
		 	ci->translation_option);
	}
}