int
main(int argc, char *argv[])
{
#define TEST_FILE "attributes.in"
	const char *in_file = FREETDS_SRCDIR "/" TEST_FILE;
	FILE *f;
	char buf[256];
	SQLINTEGER i;
	SQLLEN len;
	get_attr_t get_attr_p = get_attr_stmt;

	odbc_connect();
	/* TODO find another way */
	odbc_check_cursor();
	odbc_command("SET TEXTSIZE 4096");

	SQLBindCol(odbc_stmt, 1, SQL_C_SLONG, &i, sizeof(i), &len);

	f = fopen(in_file, "r");
	if (!f)
		f = fopen(TEST_FILE, "r");
	if (!f) {
		fprintf(stderr, "error opening test file\n");
		exit(1);
	}

	line_num = 0;
	while (fgets(buf, sizeof(buf), f)) {
		char *p = buf, *cmd;

		++line_num;

		while (isspace((unsigned char) *p))
			++p;
		cmd = strtok(p, SEP);

		/* skip comments */
		if (!cmd || cmd[0] == '#' || cmd[0] == 0 || cmd[0] == '\n')
			continue;

		if (strcmp(cmd, "odbc") == 0) {
			int odbc3 = get_int(strtok(NULL, SEP)) == 3 ? 1 : 0;

			if (odbc_use_version3 != odbc3) {
				odbc_use_version3 = odbc3;
				odbc_disconnect();
				odbc_connect();
				odbc_command("SET TEXTSIZE 4096");
				SQLBindCol(odbc_stmt, 1, SQL_C_SLONG, &i, sizeof(i), &len);
			}
			continue;
		}

		/* set attribute */
		if (strcmp(cmd, "set") == 0) {
			const struct attribute *attr = lookup_attr(strtok(NULL, SEP));
			char *value = strtok(NULL, SEP);
			SQLRETURN ret;

			if (!value)
				fatal("Line %u: value not defined\n", line_num);

			ret = SQL_ERROR;
			switch (attr->type) {
			case type_UINTEGER:
			case type_INTEGER:
				ret = SQLSetStmtAttr(odbc_stmt, attr->value, int2ptr(lookup(value, attr->lookup)),
						      sizeof(SQLINTEGER));
				break;
			case type_SMALLINT:
				ret = SQLSetStmtAttr(odbc_stmt, attr->value, int2ptr(lookup(value, attr->lookup)),
						      sizeof(SQLSMALLINT));
				break;
			case type_LEN:
				ret = SQLSetStmtAttr(odbc_stmt, attr->value, int2ptr(lookup(value, attr->lookup)),
						      sizeof(SQLLEN));
				break;
			case type_CHARP:
				ret = SQLSetStmtAttr(odbc_stmt, attr->value, (SQLPOINTER) value, SQL_NTS);
				break;
			case type_VOIDP:
			case type_DESC:
				fatal("Line %u: not implemented\n");
			}
			if (!SQL_SUCCEEDED(ret))
				fatal("Line %u: failure not expected setting statement attribute\n", line_num);
			get_attr_p = get_attr_stmt;
			continue;
		}

		/* test attribute */
		if (strcmp(cmd, "attr") == 0) {
			const struct attribute *attr = lookup_attr(strtok(NULL, SEP));
			char *value = strtok(NULL, SEP);
			int i, expected = lookup(value, attr->lookup);

			if (!value)
				fatal("Line %u: value not defined\n", line_num);

			i = get_attr_p(attr, expected);
			if (i != expected) {
				g_result = 1;
				fprintf(stderr, "Line %u: invalid %s got %d(%s) expected %s\n", line_num, attr->name, i, unlookup(i, attr->lookup), value);
			}
			continue;
		}

		if (strcmp(cmd, "reset") == 0) {
			odbc_reset_statement();
			continue;
		}

		fatal("Line %u: command '%s' not handled\n", line_num, cmd);
	}

	fclose(f);
	odbc_disconnect();

	printf("Done.\n");
	return g_result;
}