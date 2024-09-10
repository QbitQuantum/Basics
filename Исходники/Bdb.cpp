/**
 * Cursor must be closed before the transaction is aborted/commited.
 * http://download.oracle.com/docs/cd/E17076_02/html/programmer_reference/transapp_cursor.html
 */
Bdb::ResponseCode Bdb::
update(const std::string& key, const std::string& value)
{
    if (!inited_) {
        fprintf(stderr, "insert called on uninitialized database");
        return Error;
    }
    DbTxn* txn = NULL;
    Dbc* cursor = NULL;

    Dbt dbkey, dbdata;
    dbkey.set_data(const_cast<char*>(key.c_str()));
    dbkey.set_size(key.size());
    dbdata.set_data(const_cast<char*>(value.c_str()));
    dbdata.set_size(value.size());

    Dbt currentData;
    currentData.set_data(NULL);
    currentData.set_ulen(0);
    currentData.set_dlen(0);
    currentData.set_doff(0);
    currentData.set_flags(DB_DBT_USERMEM | DB_DBT_PARTIAL);

    int rc = 0;
    for (uint32_t idx = 0; idx < numRetries_; idx++) {
        env_->txn_begin(NULL, &txn, 0);
        (*db_).cursor(txn, &cursor, DB_READ_COMMITTED);

        // move the cursor to the record.
        rc = cursor->get(&dbkey, &currentData, DB_SET | DB_RMW);
        if (rc != 0) {
            cursor->close();
            txn->abort();
            if (rc == DB_NOTFOUND) {
                return KeyNotFound;
            } else if (rc != DB_LOCK_DEADLOCK) {
                fprintf(stderr, "Db::get() returned: %s", db_strerror(rc));
                return Error;
            }
            continue;
        }

        // update the record.
        rc = cursor->put(NULL, &dbdata, DB_CURRENT);
        cursor->close();
        if (rc == 0) {
            txn->commit(DB_TXN_SYNC);
            return Success;
        } else {
            txn->abort();
            if (rc != DB_LOCK_DEADLOCK) {
                fprintf(stderr, "Db::put() returned: %s", db_strerror(rc));
                return Error;
            }
        }
    }
    fprintf(stderr, "update failed %d times", numRetries_);
    return Error;
}