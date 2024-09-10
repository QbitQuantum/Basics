static void
NextResults(SQLRETURN expected, int line)
{
	if (SQLMoreResults(Statement) != expected) {
		if (expected == SQL_SUCCESS)
			fprintf(stderr, "Expected another recordset line %d\n", line);
		else
			fprintf(stderr, "Not expected another recordset line %d\n", line);
		exit(1);
	}
}