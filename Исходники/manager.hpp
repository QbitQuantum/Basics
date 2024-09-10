void loadFromKVStoreWithJson(const std::string& kvfile,
                             const std::string& json,
                             Config& config,
                             const std::string& kvConfigName)
{
    static_assert(isVisitable<Config>::value, "Use CONFIG_REGISTER macro");

    KVStore store(kvfile);
    KVStore::Transaction transaction(store);
    FromKVJsonVisitor visitor(store, json, kvConfigName);
    config.accept(visitor);
    transaction.commit();
}