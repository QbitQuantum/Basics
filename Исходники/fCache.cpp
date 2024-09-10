void fCacheDB::createTable()
{
    beginTransaction();
    executeSQL(std::string("CREATE TABLE IF NOT EXISTS " + std::string(TABLE_NAME) +
                "(id TEXT PRIMARY KEY, timestamp INTEGER, persistent INTEGER DEFAULT 0, data BLOB)").c_str());
    executeSQL(std::string("CREATE INDEX IF NOT EXISTS idx_id ON '" + std::string(TABLE_NAME) + "' (id);").c_str());
    executeSQL(std::string("CREATE INDEX IF NOT EXISTS idx_timestamp ON '" + std::string(TABLE_NAME) + "' (timestamp);").c_str());
    executeSQL(std::string("CREATE INDEX IF NOT EXISTS idx_persistent ON '" + std::string(TABLE_NAME) + "' (persistent);").c_str());
    commitTransaction();
}