static int _keyIndex(xdict *d, const void *key) {
  unsigned int h;
  xdictEntry *he;

  if (_expand(d) == XDICT_ERR) return -1;
  h = xdictHashKey(d, key) & d->sizemask;
  he = d->table[h];
  while (he) {
    if (xdictCompareHashKeys(d, key, he->key)) return -1;
    he = he->next;
  }
  return h;
}