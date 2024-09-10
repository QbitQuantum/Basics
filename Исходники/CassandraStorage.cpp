bool CassandraStorage::read(const Bucket& bucket, const Key& key, const CommitCallback& cb, const String& timestamp) {
    bool is_new = false;
    Transaction* trans = getTransaction(bucket, &is_new);
    trans->push_back(StorageAction());
    StorageAction& action = trans->back();
    action.type = StorageAction::Read;
    action.key = key;

    // Run commit if this is a one-off transaction
    if (is_new)
        commitTransaction(bucket, cb, timestamp);

    return true;
}