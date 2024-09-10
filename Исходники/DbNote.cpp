bool DbNote::createDB()
{
    sqlite3_stmt *statement;
    string stmnt = "CREATE TABLE KatTable(	KatKey INTEGER PRIMARY KEY\
										autoincrement,KatDesc TEXT);";
    if (!openDB())
    {
        throw SQLError("Can't open the DB-Connection");
        return false;
    }
    int req = sqlite3_prepare_v2(db, stmnt.c_str(), -1, &statement, 0);
    if (req != SQLITE_OK)
    {
        throw SQLError("Preparing Select-Statement failed in existCategory()");
        return false;
    }
    req = sqlite3_step(statement);
    sqlite3_finalize(statement);

    stmnt = "CREATE TABLE NoteTable( NoteKey INTEGER PRIMARY KEY autoincrement,\
						date TEXT,\
						NoteText TEXT,\
						NoteTitle TEXT,\
						KatKey INTEGER,\
						NoteRef INTEGER,\
						FOREIGN KEY (KatKey) REFERENCES KatTable(KatKey));";
    req = sqlite3_prepare_v2(db, stmnt.c_str(), -1, &statement, 0);
    if (req != SQLITE_OK)
    {
        throw SQLError("Preparing Select-Statement failed in existCategory()");
        return false;
    }
    req = sqlite3_step(statement);
    sqlite3_finalize(statement);
    sqlite3_close(db);
    Category c;
    c.setKatDesc("notice (default)");
    insertTable(c);
    return true;
}