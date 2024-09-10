int MySQLConnection::ExecuteTransaction(SQLTransaction& transaction)
{
    std::list<SQLElementData> const& queries = transaction->m_queries;
    if (queries.empty())
        return -1;

    BeginTransaction();

    std::list<SQLElementData>::const_iterator itr;
    for (itr = queries.begin(); itr != queries.end(); ++itr)
    {
        SQLElementData const& data = *itr;
        switch (itr->type)
        {
            case SQL_ELEMENT_PREPARED:
            {
                PreparedStatement* stmt = data.element.stmt;
                ASSERT(stmt);
                if (!Execute(stmt))
                {
                    TC_LOG_WARN("sql.sql", "Transaction aborted. %u queries not executed.", (uint32)queries.size());
                    int errorCode = GetLastError();
                    RollbackTransaction();
                    return errorCode;
                }
            }
            break;
            case SQL_ELEMENT_RAW:
            {
                const char* sql = data.element.query;
                ASSERT(sql);
                if (!Execute(sql))
                {
                    TC_LOG_WARN("sql.sql", "Transaction aborted. %u queries not executed.", (uint32)queries.size());
                    int errorCode = GetLastError();
                    RollbackTransaction();
                    return errorCode;
                }
            }
            break;
        }
    }

    // we might encounter errors during certain queries, and depending on the kind of error
    // we might want to restart the transaction. So to prevent data loss, we only clean up when it's all done.
    // This is done in calling functions DatabaseWorkerPool<T>::DirectCommitTransaction and TransactionTask::Execute,
    // and not while iterating over every element.

    CommitTransaction();
    return 0;
}