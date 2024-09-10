// Scan shadow memory to calculate the number of cache lines being accessed,
// i.e., the number of non-zero bits indexed by BitIdx in each shadow byte.
// We also clear the lowest bits (most recent working set snapshot).
static u32 computeWorkingSizeAndReset(u32 BitIdx) {
  u32 WorkingSetSize = 0;
  MemoryMappingLayout MemIter(true/*cache*/);
  uptr Start, End, Prot;
  while (MemIter.Next(&Start, &End, nullptr/*offs*/, nullptr/*file*/,
                      0/*file size*/, &Prot)) {
    VPrintf(4, "%s: considering %p-%p app=%d shadow=%d prot=%u\n",
            __FUNCTION__, Start, End, Prot, isAppMem(Start),
            isShadowMem(Start));
    if (isShadowMem(Start) && (Prot & MemoryMappingLayout::kProtectionWrite)) {
      VPrintf(3, "%s: walking %p-%p\n", __FUNCTION__, Start, End);
      WorkingSetSize += countAndClearShadowValues(BitIdx, Start, End);
    }
  }
  return WorkingSetSize;
}