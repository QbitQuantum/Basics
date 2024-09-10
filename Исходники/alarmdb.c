int
AlarmDBDeleteAlarms(AlarmDBHandle *handle, const char *store, uint64_t guid)
{
    sqlite3_stmt *stmt;
    int dcode = 0;

    stmt = SqlPrepare(handle, 
                      "DELETE FROM alarms WHERE store = ? AND guid = ?;",
                      &handle->stmts.delAlarm);
    if (!stmt) {
        return -1;
    }
    if (SqlBindStr(stmt, 1, store) || 
        sqlite3_bind_int64(stmt, 2, guid) ||
        SQLITE_DONE != sqlite3_step(stmt))
    {
        dcode = -1;
    }
    
    sqlite3_reset(stmt);
    
    return dcode;
}