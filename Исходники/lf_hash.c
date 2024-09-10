void *lf_hash_search(LF_HASH *hash, LF_PINS *pins, const void *key, uint keylen)
{
  LF_SLIST * volatile *el, *found;
  uint bucket, hashnr= calc_hash(hash, (uchar *)key, keylen);

  bucket= hashnr % hash->size;
  el= lf_dynarray_lvalue(&hash->array, bucket);
  if (unlikely(!el))
    return MY_ERRPTR;
  if (*el == NULL && unlikely(initialize_bucket(hash, el, bucket, pins)))
    return MY_ERRPTR;
  found= lsearch(el, hash->charset, my_reverse_bits(hashnr) | 1,
                 (uchar *)key, keylen, pins);
  return found ? found+1 : 0;
}