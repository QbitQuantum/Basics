void IpeEnv::allocateSpace(VarSymbol* var) const
{
#if 0
  int delta  = 8;      // NOAKES: Everything is 8 bytes

  INT_ASSERT(sStoreTail + delta <= sStoreSize);

  var->locationSet(0, sStoreTail);
  varAdd(var);

  sStoreTail = sStoreTail + delta;
#else
  INT_ASSERT(false);
#endif
}