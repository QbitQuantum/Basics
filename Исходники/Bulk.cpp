/* 批量插入示例函数。*/
void *
run_bulk_delete()
{
    int raw_key[NUM_KEY_INT];
    DBT key;
    DB_ENV *envp;
    int bulk_size = 100;
    DB *dbp;
    DB_TXN *tid;
    int *delete_load;
    int delete_count, i, ret, op_flag;

    char *key_buf;
    void *p;
    int j;

    /* Initialize structs and arrays */
    memset(raw_key, 0, KEY_SIZE);
    memset(&key, 0, sizeof(DBT));
    tid = NULL;

    /*
     * 初始化批量删除使用的key buffer。由于批量删除不需要data，
     * 所以只需要初始化和填充key buffer。我们同样需要使用自己分配的内存。
     */
    key_buf = (char*) malloc(KEY_SIZE * bulk_size * 2);
    memset(key_buf, 0, KEY_SIZE * bulk_size * 2);

    /* 初始化key buffer DBT 对象，设置正确的flags和ulen成员。 */
    key.data = key_buf;
    key.ulen = KEY_SIZE * bulk_size * 2;
    key.flags = DB_DBT_USERMEM;
    op_flag = DB_MULTIPLE; /* 批量删除同样需要这个flag。*/

    /*
     * 批量删除所有的数据。每一批删除由key buffer DBT 当中的key
     * 指定的bulk_size条key/data pair. 这两个宏的详细用法见上文。
     */
    for (i = 0; i < delete_count / bulk_size; ) {
        /* 为批量删除初始化并填充一个key buffer DBT 对象。 */
        DB_MULTIPLE_WRITE_INIT(p, &key);
        for (j = i * bulk_size; j < (i + 1) * bulk_size; j++) {
            raw_key[0] = delete_load[j];
            DB_MULTIPLE_WRITE_NEXT(p, &key, raw_key, KEY_SIZE);
        }
        /* 启动事务。*/
        if ((ret = envp->txn_begin(envp, NULL, &tid, 0)) != 0) {
            envp->err(envp, ret, "[delete] DB_ENV->txn_begin");
            exit(EXIT_FAILURE);
        }

        /*
         * 执行批量删除。key buffer DBT
         * 当中的bulk_size条key指定的key/data pairs会被从数据库当中删除。
         */
        switch(ret = dbp->del(dbp, tid, &key, op_flag)) {
        case 0: /* 批量删除操作成功，提交事务。*/
            if ((ret = tid->commit(tid, 0)) != 0) {
                envp->err(envp, ret, "[delete] DB_TXN->commit");
                exit(EXIT_FAILURE);
            }
            break;
        case DB_LOCK_DEADLOCK:
            /* 如果数据库操作发生死锁，那么必须abort事务。然后，可以选择重新执行该操作。*/
            if ((ret = tid->abort(tid)) != 0) {
                envp->err(envp, ret, "[delete] DB_TXN->abort");
                exit(EXIT_FAILURE);
            }
            continue;
        default:
            envp->err(envp, ret, "[delete] DB->del ([%d]%d)", i, delete_load[i]);
            exit(EXIT_FAILURE);
        }
        i++;
    }

    (void)free(key_buf);

    return (NULL);
}