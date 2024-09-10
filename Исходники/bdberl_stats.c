static void do_async_stat(void* arg)
{
    // Payload is: << DbRef:32, Flags:32 >>
    PortData* d = (PortData*)arg;

    // Get the database object, using the provided ref
    DB* db = bdberl_lookup_dbref(d->async_dbref);
    DBTYPE type = DB_UNKNOWN;
    int rc = db->get_type(db, &type);
    if (rc != 0)
    {
        bdberl_async_cleanup_and_send_rc(d, rc);
        return;
    }

    void *sp = NULL;
    rc = db->stat(db, d->txn, &sp, d->async_flags);
    if (rc != 0 || sp == NULL)
    {
        bdberl_async_cleanup_and_send_rc(d, rc);
    }
    else
    {
        switch(type)
        {
            case DB_BTREE: /*FALLTHRU*/
            case DB_RECNO:
                async_cleanup_and_send_btree_stats(d, type == DB_BTREE ? "btree" :"recno", sp);
                break;
            case DB_HASH:
                async_cleanup_and_send_hash_stats(d, sp);
                break;
#ifdef ENABLE_QUEUE
            case DB_QUEUE:
                async_cleanup_and_send_queue_stats(d, sp);
                break;
#endif
            default:
                bdberl_async_cleanup_and_send_rc(d, ERROR_INVALID_DB_TYPE);
                break;
        }
    }

    // Finally, clean up value buffer (driver_send_term made a copy)
    if (NULL != sp)
    {
        driver_free(sp);
    }
}