static int64_t incrementInt64(stKVDatabase *database, int64_t key, int64_t incrementAmount) {
    startTransaction(database);
    int64_t returnValue = INT64_MIN;
    stTry {
        int64_t recordSize;
        int64_t *record = getRecord2(database, key, &recordSize);
        assert(recordSize >= sizeof(int64_t));
        record[0] += incrementAmount;
        returnValue = record[0];
        updateRecord(database, key, record, recordSize);
        free(record);
        commitTransaction(database);
    }stCatch(ex) {
        abortTransaction(database);
        stThrowNewCause(
                ex,
                ST_KV_DATABASE_EXCEPTION_ID,
                "MySQL increment record failed");
    }stTryEnd;
    return returnValue;
}