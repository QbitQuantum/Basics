PRInt32
nsCertTree::CmpBy(void *cache, nsIX509Cert *a, nsIX509Cert *b, 
                  sortCriterion c0, sortCriterion c1, sortCriterion c2)
{
  // This will be called when comparing items for display sorting.
  // Some items might have no cert associated, so either a or b is null.
  // We want all those orphans show at the top of the list,
  // so we treat a null cert as "smaller" by returning -1.
  // We don't try to sort within the group of no-cert entries,
  // so we treat them as equal wrt sort order.

  if (!a && !b)
    return 0;

  if (!a)
    return -1;

  if (!b)
    return 1;

  NS_ENSURE_TRUE( (cache!=0 && a!=0 && b!=0), 0 );

  CompareCacheHashEntry *ace = getCacheEntry(cache, a);
  CompareCacheHashEntry *bce = getCacheEntry(cache, b);

  PRInt32 cmp;
  cmp = CmpByCrit(a, ace, b, bce, c0, 0);
  if (cmp != 0)
    return cmp;

  if (c1 != sort_None) {
    cmp = CmpByCrit(a, ace, b, bce, c1, 1);
    if (cmp != 0)
      return cmp;
    
    if (c2 != sort_None) {
      return CmpByCrit(a, ace, b, bce, c2, 2);
    }
  }

  return cmp;
}