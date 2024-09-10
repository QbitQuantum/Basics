/// Like hash_find(), but caller computes "hash".
///
/// @param[in]  key  The key of the looked-for item. Must not be NULL.
/// @param[in]  key_len  Key length.
/// @param[in]  hash  The precomputed hash for the key.
///
/// @return Pointer to the hashitem corresponding to the given key.
///         If not found, then return pointer to the empty item that would be
///         used for that key.
///         WARNING: Returned pointer becomes invalid as soon as the hash table
///                  is changed in any way.
hashitem_T *hash_lookup(hashtab_T *const ht,
                        const char *const key, const size_t key_len,
                        const hash_T hash)
{
#ifdef HT_DEBUG
  hash_count_lookup++;
#endif  // ifdef HT_DEBUG

  // Quickly handle the most common situations:
  // - return if there is no item at all
  // - skip over a removed item
  // - return if the item matches
  hash_T idx = hash & ht->ht_mask;
  hashitem_T *hi = &ht->ht_array[idx];

  if (hi->hi_key == NULL) {
    return hi;
  }

  hashitem_T *freeitem = NULL;
  if (hi->hi_key == HI_KEY_REMOVED) {
    freeitem = hi;
  } else if ((hi->hi_hash == hash)
             && (STRNCMP(hi->hi_key, key, key_len) == 0)
             && hi->hi_key[key_len] == NUL) {
    return hi;
  }

  // Need to search through the table to find the key. The algorithm
  // to step through the table starts with large steps, gradually becoming
  // smaller down to (1/4 table size + 1). This means it goes through all
  // table entries in the end.
  // When we run into a NULL key it's clear that the key isn't there.
  // Return the first available slot found (can be a slot of a removed
  // item).
  for (hash_T perturb = hash;; perturb >>= PERTURB_SHIFT) {
#ifdef HT_DEBUG
    // count a "miss" for hashtab lookup
    hash_count_perturb++;
#endif  // ifdef HT_DEBUG
    idx = 5 * idx + perturb + 1;
    hi = &ht->ht_array[idx & ht->ht_mask];

    if (hi->hi_key == NULL) {
      return freeitem == NULL ? hi : freeitem;
    }

    if ((hi->hi_hash == hash)
        && (hi->hi_key != HI_KEY_REMOVED)
        && (STRNCMP(hi->hi_key, key, key_len) == 0)
        && hi->hi_key[key_len] == NUL) {
      return hi;
    }

    if ((hi->hi_key == HI_KEY_REMOVED) && (freeitem == NULL)) {
      freeitem = hi;
    }
  }
}