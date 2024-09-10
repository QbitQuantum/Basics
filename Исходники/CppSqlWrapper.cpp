SqlDatabase::SqlDatabase(const char* szFile, bool useExclusiveWAL /* = true */) {
	mpDB = 0;
	mnBusyTimeoutMs = 60000; // 60 seconds
	assert(sqlite3_libversion_number()==SQLITE_VERSION_NUMBER);

	if (sqlite3_open(szFile, &mpDB) != SQLITE_OK)
		throw SqlDatabaseException("Unable to open/create database file.");
	setBusyTimeout(mnBusyTimeoutMs);
	if (useExclusiveWAL) {
		// Set the database to use Write-Ahead Logging and the EXCLUSIVE locking mode
		// for performance improvements:
		sqlExecute("PRAGMA locking_mode = EXCLUSIVE; PRAGMA journal_mode=WAL;");
	}
}