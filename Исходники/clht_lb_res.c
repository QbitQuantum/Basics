/* Insert a key-value entry into a hash table. */
int
clht_put(clht_t* h, clht_addr_t key, clht_val_t val) 
{
  clht_hashtable_t* hashtable = h->ht;
  size_t bin = clht_hash(hashtable, key);
  volatile bucket_t* bucket = hashtable->table + bin;

#if CLHT_READ_ONLY_FAIL == 1
  if (bucket_exists(bucket, key))
    {
      return false;
    }
#endif

  clht_lock_t* lock = &bucket->lock;
  while (!LOCK_ACQ(lock, hashtable))
    {
      hashtable = h->ht;
      size_t bin = clht_hash(hashtable, key);

      bucket = hashtable->table + bin;
      lock = &bucket->lock;
    }

  CLHT_GC_HT_VERSION_USED(hashtable);
  CLHT_CHECK_STATUS(h);
  clht_addr_t* empty = NULL;
  clht_val_t* empty_v = NULL;

  uint32_t j;
  do 
    {
      for (j = 0; j < ENTRIES_PER_BUCKET; j++) 
	{
	  if (bucket->key[j] == key) 
	    {
	      LOCK_RLS(lock);
	      return false;
	    }
	  else if (empty == NULL && bucket->key[j] == 0)
	    {
	      empty = (clht_addr_t*) &bucket->key[j];
	      empty_v = &bucket->val[j];
	    }
	}
        
      int resize = 0;
      if (likely(bucket->next == NULL))
	{
	  if (unlikely(empty == NULL))
	    {
	      DPP(put_num_failed_expand);

	      bucket_t* b = clht_bucket_create_stats(hashtable, &resize);
	      b->val[0] = val;
#ifdef __tile__
	      /* keep the writes in order */
	      _mm_sfence();
#endif
	      b->key[0] = key;
#ifdef __tile__
	      /* make sure they are visible */
	      _mm_sfence();
#endif
	      bucket->next = b;
	    }
	  else 
	    {
	      *empty_v = val;
#ifdef __tile__
	      /* keep the writes in order */
	      _mm_sfence();
#endif
	      *empty = key;
	    }

	  LOCK_RLS(lock);
	  if (unlikely(resize))
	    {
	      /* ht_resize_pes(h, 1); */
	      ht_status(h, 1, 0);
	    }
	  return true;
	}
      bucket = bucket->next;
    }
  while (true);
}