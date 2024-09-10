bool JsonDbBtree::getOne(const QByteArray &key, QByteArray *value)
{
    bool inTransaction = mBtree->isWriting();
    Transaction *txn = inTransaction ? mBtree->writeTransaction() : mBtree->beginWrite();
    bool ok = txn->get(key, value);
    if (!inTransaction)
        txn->abort();
    return ok;
}