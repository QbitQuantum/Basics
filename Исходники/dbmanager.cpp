int DBManager::insert(const QString &statement)
{
	if (!isLoaded_) // There is no DB connection
		return 0;
	
	QStringList values;
	int error, rc = 0;
	const char *tail;
	sqlite3_stmt *stmt;
	int busyCnt = 0;
	int retryCnt = 0;
	
	do {
		do {
			if (busyCnt) {
				_SLEEP(100000);
				// BUSY COUNTER
			}
			error = sqlite3_prepare(db_, statement.toUtf8(), -1, &stmt, &tail);
		} while (error == SQLITE_BUSY && busyCnt++ < 120);
		
		if (error != SQLITE_OK) {
			if (error == SQLITE_BUSY)
				KMessageBox::sorry(0L, i18n("Sorry, Database is locked right now. Please try again later."));
			values = QStringList();
		} else {
			busyCnt = 0;
			
			while (1) {
				error = sqlite3_step(stmt);
				
				if (error == SQLITE_BUSY) {
					if (busyCnt++ > 120) {
						KMessageBox::sorry(0L, i18n("Sorry, Database is locked right now. Please try again later."));
						break;
					}
					_SLEEP(100000);
					continue;
				}
				if (error == SQLITE_DONE || error == SQLITE_ERROR)
					break;
			}
			
			rc = sqlite3_finalize(stmt);
			
			if (error != SQLITE_DONE && rc != SQLITE_SCHEMA) {
				values = QStringList();
			}
			if (rc == SQLITE_SCHEMA) {
				retryCnt++;
				if (retryCnt >= 10) {
					KMessageBox::error(0L, i18n("Retry count has reached maximum"));
					values = QStringList();
				}
			}
		}
	} while (rc == SQLITE_SCHEMA && retryCnt < 10);
	
	return sqlite3_last_insert_rowid(db_);
}