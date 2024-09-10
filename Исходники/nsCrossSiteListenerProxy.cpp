nsPreflightCache::CacheEntry*
nsPreflightCache::GetEntry(nsIURI* aURI,
                           nsIPrincipal* aPrincipal,
                           bool aWithCredentials,
                           bool aCreate)
{
    nsCString key;
    if (!GetCacheKey(aURI, aPrincipal, aWithCredentials, key)) {
        NS_WARNING("Invalid cache key!");
        return nullptr;
    }

    CacheEntry* entry;

    if (mTable.Get(key, &entry)) {
        // Entry already existed so just return it. Also update the LRU list.

        // Move to the head of the list.
        entry->removeFrom(mList);
        mList.insertFront(entry);

        return entry;
    }

    if (!aCreate) {
        return nullptr;
    }

    // This is a new entry, allocate and insert into the table now so that any
    // failures don't cause items to be removed from a full cache.
    entry = new CacheEntry(key);
    if (!entry) {
        NS_WARNING("Failed to allocate new cache entry!");
        return nullptr;
    }

    NS_ASSERTION(mTable.Count() <= PREFLIGHT_CACHE_SIZE,
                 "Something is borked, too many entries in the cache!");

    // Now enforce the max count.
    if (mTable.Count() == PREFLIGHT_CACHE_SIZE) {
        // Try to kick out all the expired entries.
        TimeStamp now = TimeStamp::NowLoRes();
        mTable.Enumerate(RemoveExpiredEntries, &now);

        // If that didn't remove anything then kick out the least recently used
        // entry.
        if (mTable.Count() == PREFLIGHT_CACHE_SIZE) {
            CacheEntry* lruEntry = static_cast<CacheEntry*>(mList.popLast());
            MOZ_ASSERT(lruEntry);

            // This will delete 'lruEntry'.
            mTable.Remove(lruEntry->mKey);

            NS_ASSERTION(mTable.Count() == PREFLIGHT_CACHE_SIZE - 1,
                         "Somehow tried to remove an entry that was never added!");
        }
    }

    mTable.Put(key, entry);
    mList.insertFront(entry);

    return entry;
}