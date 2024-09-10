int main(int argc, char *argv[]) {
	// sql vars
	SQLHENV henv = SQL_NULL_HENV; // environment
	SQLHDBC hdbc = SQL_NULL_HDBC; // connection
	SQLHSTMT hstmt = SQL_NULL_HSTMT; // statement

	// sql connect
	sqlConnect(&henv, &hdbc, &hstmt);

	// input vars
	char beruf[BERUFSIZE + 1];
	char mitID[MITIDSIZE + 1];

	// program logic
	while (getBerufe(&henv, &hdbc, &hstmt, beruf)) {
		if (getMitarbeiter(&henv, &hdbc, &hstmt, beruf, mitID)) {
			if (getMitDetails(&henv, &hdbc, &hstmt, beruf, mitID)) {
				getProjektDetails(&henv, &hdbc, &hstmt, beruf, mitID);
			}
		}
	}

	puts("");

	// sql disconnect
	sqlDisconnect(&henv, &hdbc, &hstmt);

	return 0;
}