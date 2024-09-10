static int
CheckNonrepeatableRead(void)
{
	SQLRETURN RetCode;

	/* transaction 2 read a row */
	SWAP_CONN();
	odbc_command("SELECT * FROM test_transaction WHERE t = 'initial' AND n = 1");
	SQLMoreResults(odbc_stmt);

	/* transaction 1 change a row and commit */
	SWAP_CONN();
	RetCode = odbc_command2("UPDATE test_transaction SET t = 'second' WHERE n = 1", "SE");
	if (RetCode == SQL_ERROR) {
		EndTransaction(SQL_ROLLBACK);
		SWAP_CONN();
		EndTransaction(SQL_ROLLBACK);
		SWAP_CONN();
		return 0;	/* no dirty read */
	}
	EndTransaction(SQL_COMMIT);

	SWAP_CONN();

	/* second transaction try to fetch commited row */
	odbc_command("SELECT * FROM test_transaction WHERE t = 'second' AND n = 1");

	CHKFetch("S");
	CHKFetch("No");
	SQLMoreResults(odbc_stmt);
	EndTransaction(SQL_ROLLBACK);
	SWAP_CONN();
	odbc_command("UPDATE test_transaction SET t = 'initial' WHERE n = 1");
	EndTransaction(SQL_COMMIT);
	return 1;
}