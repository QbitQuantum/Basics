int64 auth_verify_from_mydb_by_client(const char* guest, char* accesstoken, int accesslen)
{
    int ret, row, col;
    sqlite3 *db = NULL;
    char *errmsg = NULL, **result, sql[1024];
    uint64 time;
    int64 uid;

    // open database
    ret = sqlite3_open("./auth.db", &db);
    if (ret != SQLITE_OK) {
        LOGGER_ERROR("auth_verify_from_mydb_by_client open error: %s", sqlite3_errmsg(db));
        goto QUIT;
    }

    // check table exist
    snprintf(sql, sizeof(sql), "select count(*) from sqlite_master where type='table' and name='guest'");
    ret = sqlite3_get_table(db, sql, &result, &row, &col, &errmsg);
    if (ret != SQLITE_OK) {
        LOGGER_ERROR("auth_verify_from_mydb_by_client check table exist error: %d, %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        goto QUIT;
    }

    // if not exist then create
    if (atoi(result[1]) <= 0) {
        snprintf(sql, sizeof(sql), "create table guest(uid integer primary key autoincrement, name varchar(128), token varchar(128), time datatime)");
        ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
        if (ret != SQLITE_OK) {
            LOGGER_ERROR("auth_verify_from_mydb_by_client create table error: %d, %s", sqlite3_errcode(db), sqlite3_errmsg(db));
            goto QUIT;
        }
    }

    // check guest if exist
    snprintf(sql, sizeof(sql), "select * from guest where name='%s'", guest);
    ret = sqlite3_get_table(db, sql, &result, &row, &col, &errmsg);
    if (ret != SQLITE_OK) {
        LOGGER_ERROR("auth_verify_from_mydb_by_client get table error: %d, %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        goto QUIT;
    }

    time = GetTimeSec();
    snprintf(accesstoken, accesslen, "%lld", time);

    // if not exist then insert
    if (row <= 0) {
        snprintf(sql, sizeof(sql), "insert into guest (name, token, time) values('%s', '%s', %lld)", guest, accesstoken, time);
        ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
        if (ret != SQLITE_OK) {
            LOGGER_ERROR("auth_verify_from_mydb_by_client insert guest error: %s, %s", guest, sqlite3_errmsg(db));
            goto QUIT;
        }

        snprintf(sql, sizeof(sql), "select * from guest where name='%s'", guest);
        ret = sqlite3_get_table(db, sql, &result, &row, &col, &errmsg);
        if (ret != SQLITE_OK) {
            LOGGER_ERROR("auth_verify_from_mydb_by_client get table error: %d, %s", sqlite3_errcode(db), sqlite3_errmsg(db));
            goto QUIT;
        }
    } else {
        snprintf(sql, sizeof(sql), "update guest set token='%s', time=%lld where name='%s'", accesstoken, time, guest);
        ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
        if (ret != SQLITE_OK) {
            LOGGER_ERROR("auth_verify_from_mydb_by_client update guest error: %s, %s", guest, sqlite3_errmsg(db));
            goto QUIT;
        }
    }

    uid = atoll(result[col]);

QUIT:
    if (db) sqlite3_close(db);
    if (errmsg) sqlite3_free(errmsg);

    return uid;
}