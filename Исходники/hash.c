static unsigned
hash (hash_table_type table,  const_string key)
{
  unsigned n = 0;

  /* Our keys aren't often anagrams of each other, so no point in
     weighting the characters.  */
  while (*key != 0)
#if defined (WIN32) && defined (KPSE_COMPAT_API)
    if (IS_KANJI(key)) {
      n = (n + n + (unsigned)(*key++)) % table.size;
      n = (n + n + (unsigned)(*key++)) % table.size;
    } else
#endif
    n = (n + n + TRANSFORM (*key++)) % table.size;

  return n;
}