xHeap::xHeap()
{
  ASSERT(CeilPowerOfTwo(APP_HEAP_CHUNK_SIZE) == APP_HEAP_CHUNK_SIZE);

  pageSize = CeilPowerOfTwo(DEF_PAGE_SIZE < MAX_SMALL_SIZE*8 ? MAX_SMALL_SIZE*8 : DEF_PAGE_SIZE);
  smallPageSize = pageSize;

  MEMSET(&smallStats, 0, sizeof(smallStats));
  MEMSET(&largeStats, 0, sizeof(largeStats));
  
#ifdef DEBUG_APP_HEAP
  smallStats.minBlockDataSize = 0xFFFFFFFF;
  largeStats.minBlockDataSize = 0xFFFFFFFF;
#endif

  dummySmallPage.size = 0;
  dummySmallPage.next = NULL;
  smallPage = &dummySmallPage;
  MEMSET(freeSmallBlocks, 0, sizeof(freeSmallBlocks));
  smallPageOffs = 0;
#ifdef DEBUG_APP_HEAP
  dummySmallBlock.ResetLink();
  dummySmallBlock.sizeSlot = 0;
  dummySmallBlock.filename = "#dummy#";
  dummySmallBlock.line = 0;
#endif

#ifndef USE_APP_HEAP_SAVING_MODE
  mediumSizeMask = pageSize/2-1;
  MEMSET(&mediumStats, 0, sizeof(mediumStats));

#ifdef DEBUG_APP_HEAP
  mediumStats.minBlockDataSize = 0xFFFFFFFF;
#endif

  dummyBlock.ResetLink();
  dummyBlock.size = 0;
  dummyBlock.page = (uint16)-1;
  dummyBlock.isFree = true;
  // dummyBlock.type = BT_MEDIUM;
#ifdef DEBUG_APP_HEAP
  dummyBlock.filename = "#dummy#";
  dummyBlock.line = 0;
#endif

  dummyFree.ResetLink();
  dummyFree.ResetFreeLink();
  dummyFree.size = 0;
  dummyFree.page = (uint16)-1;
  dummyFree.isFree = false;
  // dummyFree.type = BT_MEDIUM;
#ifdef DEBUG_APP_HEAP
  dummyFree.filename = "#dummy#";
  dummyFree.line = 0;
#endif

  nextPage = 1;

#endif // USE_APP_HEAP_SAVING_MODE

  dummyLargeBlock.ResetLink();
  dummyLargeBlock.size = 0;
  dummyLargeBlock.page = (uint16)-1;
  dummyLargeBlock.isFree = false;
  // dummyLargeBlock.type = BT_LARGE;
#ifdef DEBUG_APP_HEAP
  dummyLargeBlock.filename = "#dummy#";
  dummyLargeBlock.line = 0;
#endif

  if(!instance)
  {
    *((xHeap**)(&instance)) = this;
  }
}