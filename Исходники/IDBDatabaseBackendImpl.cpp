// FIXME: Remove this as part of https://bugs.webkit.org/show_bug.cgi?id=102733.
PassRefPtr<IDBTransactionBackendInterface> IDBDatabaseBackendImpl::transaction(const Vector<int64_t>& objectStoreIds, unsigned short mode)
{
    return createTransaction(0, objectStoreIds, mode);
}