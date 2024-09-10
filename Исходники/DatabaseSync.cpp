void DatabaseSync::runTransaction(PassOwnPtr<SQLTransactionSyncCallback> callback, bool readOnly, ExceptionState& exceptionState)
{
    ASSERT(m_executionContext->isContextThread());

    if (sqliteDatabase().transactionInProgress()) {
        setLastErrorMessage("unable to start a transaction from within a transaction");
        exceptionState.throwUninformativeAndGenericDOMException(SQLDatabaseError);
        return;
    }

    RefPtr<SQLTransactionSync> transaction = SQLTransactionSync::create(this, callback, readOnly);
    transaction->begin(exceptionState);
    if (exceptionState.hadException()) {
        rollbackTransaction(transaction);
        return;
    }

    transaction->execute(exceptionState);
    if (exceptionState.hadException()) {
        rollbackTransaction(transaction);
        return;
    }

    transaction->commit(exceptionState);
    if (exceptionState.hadException()) {
        rollbackTransaction(transaction);
        return;
    }

    setLastErrorMessage("");
}