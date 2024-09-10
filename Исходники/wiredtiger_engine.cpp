    int WiredTigerEngine::Del(const Slice& key, const Options& options)
    {
        ContextHolder& holder = GetContextHolder();
        WT_SESSION* session = holder.session;
        if (NULL == session)
        {
            return -1;
        }
//        if (holder.trasc_ref > 0)
//        {
//            DelOperation* op = new DelOperation;
//            op->key.assign((const char*) key.data(), key.size());
//            m_write_queue.Push(op);
//            holder.readonly_transc = false;
//            return 0;
//        }
        int ret = 0;
        WT_CURSOR *cursor = holder.batch == NULL ? create_wiredtiger_cursor(session) : holder.batch;
        if (NULL == cursor)
        {
            return -1;
        }
        WT_ITEM key_item;
        key_item.data = key.data();
        key_item.size = key.size();
        cursor->set_key(cursor, &key_item);
        ret = cursor->remove(cursor);
        CHECK_WT_RETURN(ret);
        if (holder.batch == NULL)
        {
            cursor->close(cursor);
            CHECK_WT_RETURN(ret);
        }
        else
        {
            holder.IncBatchWriteCount();
            if (holder.batch_write_count >= m_cfg.batch_commit_watermark)
            {
                holder.RestartBatchWrite();
            }
        }
        return 0;
    }