void free_lru_cache(struct LruCache *cache) {
  int i;

  if(unlikely(traceLRU)) traceEvent(TRACE_NORMAL, "%s()", __FUNCTION__);

  for(i=0; i<cache->hash_size; i++) {
    struct LruCacheEntry *head = cache->hash[i];

    while(head != NULL) {
      struct LruCacheEntry *next = head->next;

      free_lru_cache_entry(cache, head);
      free(head);
#ifdef FULL_STATS
      cache->mem_size -= sizeof(struct LruCacheEntry);
#endif
      head = next;
    }
  }

  free(cache->hash);
#ifdef FULL_STATS
  cache->mem_size -= cache->hash_size*sizeof(struct LruCacheEntry*);
#endif
  free(cache->current_hash_size);
#ifdef FULL_STATS
  cache->mem_size -= cache->hash_size*sizeof(u_int32_t);
#endif

  pthread_rwlock_destroy(&cache->lruLock);
}