static void
test_params(void)
{
#define ARRAY_SIZE 2
	const rows_set_t *p;
	SQLULEN len;
	SQLUINTEGER *ids = MALLOC_N(SQLUINTEGER,ARRAY_SIZE);
	SQLLEN *id_lens = MALLOC_N(SQLLEN,ARRAY_SIZE);
	unsigned long int h, l;
	unsigned int n;

	for (n = 0; n < ARRAY_SIZE; ++n) {
		ids[n] = n;
		id_lens[n] = 0;
	}

	/* test setting just some test pointers */
	set_ipd_params1(int2ptr(0x01020304));
	check_ipd_params();
	set_ipd_params2(int2ptr(0xabcdef12));
	check_ipd_params();
	set_ipd_params3(int2ptr(0x87654321));
	check_ipd_params();

	/* now see results */
	for (p = param_set; *p != NULL; ++p) {
		odbc_reset_statement();
		len = 0xdeadbeef;
		len <<= 16;
		len <<= 16;
		len |= 12345678;

		(*p)(&len);
		check_ipd_params();

		CHKSetStmtAttr(SQL_ATTR_PARAMSET_SIZE, (void *) int2ptr(ARRAY_SIZE), 0, "S");
		CHKBindParameter(1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 5, 0, ids, 0, id_lens, "S");

		odbc_command("INSERT INTO #tmp1(i) VALUES(?)");
		SQLMoreResults(odbc_stmt);
		for (n = 0; n < ARRAY_SIZE; ++n)
			SQLMoreResults(odbc_stmt);
		l = len;
		len >>= 16;
		h = len >> 16;
		l &= 0xfffffffflu;
		if (h != 0 || l != 2) {
			fprintf(stderr, "Wrong number returned in param rows high %lu low %lu\n", h, l);
			exit(1);
		}
	}

	free(ids);
	free(id_lens);
}