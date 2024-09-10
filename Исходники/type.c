int
main(int argc, char **argv)
{
	const struct type *p;
	char buf[16];
	SQLINTEGER ind;
	SQLLEN lind;
	SQLHDESC desc;

	odbc_connect();

	/*
	 * test setting two time a descriptor
	 * success all user allocated are ARD or APD so type cheching can be done
	 * TODO freeing descriptor dissociate it from statements
	 */

	/* test C types */
	for (p = types; p->name; ++p) {
		if (SQL_SUCCEEDED
		    (SQLBindParameter(odbc_stmt, 1, SQL_PARAM_INPUT, p->type, SQL_VARCHAR, (SQLUINTEGER) (-1), 0, buf, 16, &lind))) {
			SQLSMALLINT concise_type, type, code;
			SQLHDESC desc;

			concise_type = type = code = 0;

			/* get APD */
			SQLGetStmtAttr(odbc_stmt, SQL_ATTR_APP_PARAM_DESC, &desc, sizeof(desc), &ind);

			SQLGetDescField(desc, 1, SQL_DESC_TYPE, &type, sizeof(SQLSMALLINT), &ind);
			SQLGetDescField(desc, 1, SQL_DESC_CONCISE_TYPE, &concise_type, sizeof(SQLSMALLINT), &ind);
			SQLGetDescField(desc, 1, SQL_DESC_DATETIME_INTERVAL_CODE, &code, sizeof(SQLSMALLINT), &ind);
			printf("Setted type %s -> [%d (%s), %d (%s), %d]\n",
			       p->name, (int) concise_type, get_type_name(concise_type), (int) type, get_type_name(type), code);
			check_msg(p->flags & FLAG_C, "Type not C successed to be set in APD");
		} else {
			SQLSMALLINT concise_type, type, code;
			SQLHDESC desc;

			concise_type = type = code = 0;

			fprintf(stderr, "Error setting type %d (%s)\n", (int) p->type, p->name);

			concise_type = p->type;
			SQLGetStmtAttr(odbc_stmt, SQL_ATTR_APP_PARAM_DESC, &desc, sizeof(desc), &ind);
			if (SQL_SUCCEEDED
			    (SQLSetDescField(desc, 1, SQL_DESC_CONCISE_TYPE, int2ptr(concise_type), sizeof(SQLSMALLINT))))
			{
				SQLGetDescField(desc, 1, SQL_DESC_TYPE, &type, sizeof(SQLSMALLINT), &ind);
				SQLGetDescField(desc, 1, SQL_DESC_CONCISE_TYPE, &concise_type, sizeof(SQLSMALLINT), &ind);
				SQLGetDescField(desc, 1, SQL_DESC_DATETIME_INTERVAL_CODE, &code, sizeof(SQLSMALLINT), &ind);
				printf("Setted type %s -> [%d (%s), %d (%s), %d]\n",
				       p->name,
				       (int) concise_type, get_type_name(concise_type), (int) type, get_type_name(type), code);
				check_msg(p->flags & FLAG_C, "Type not C successed to be set in APD");
			} else {
				check_msg(!(p->flags & FLAG_C), "Type C failed to be set in APD");
			}
		}
	}

	printf("\n\n");

	/* test SQL types */
	SQLGetStmtAttr(odbc_stmt, SQL_ATTR_IMP_PARAM_DESC, &desc, sizeof(desc), &ind);
	for (p = types; p->name; ++p) {
		SQLSMALLINT concise_type = p->type;

		if (SQL_SUCCEEDED
		    (SQLSetDescField(desc, 1, SQL_DESC_CONCISE_TYPE, int2ptr(concise_type), sizeof(SQLSMALLINT)))) {
			SQLSMALLINT concise_type, type, code;

			concise_type = type = code = 0;

			SQLGetDescField(desc, 1, SQL_DESC_TYPE, &type, sizeof(SQLSMALLINT), &ind);
			SQLGetDescField(desc, 1, SQL_DESC_CONCISE_TYPE, &concise_type, sizeof(SQLSMALLINT), &ind);
			SQLGetDescField(desc, 1, SQL_DESC_DATETIME_INTERVAL_CODE, &code, sizeof(SQLSMALLINT), &ind);
			printf("Setted type %s -> [%d (%s), %d (%s), %d]\n",
			       p->name, (int) concise_type, get_type_name(concise_type), (int) type, get_type_name(type), code);
			check_msg(p->flags & FLAG_SQL, "Type not SQL successed to be set in IPD");
		} else {
			fprintf(stderr, "Error setting type %d (%s)\n", (int) p->type, p->name);
			check_msg(!(p->flags & FLAG_SQL), "Type SQL failed to be set in IPD");
		}
	}

	odbc_disconnect();

	return result;
}