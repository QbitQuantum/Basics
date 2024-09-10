void RHybridHeap::Walk(SWalkInfo* aInfo, TAny* aBfr, TInt aLth, TCellType aBfrType, TAllocatorType aAllocatorType)
{
    //
    // This function is always called from RHybridHeap::GetInfo.
    // Actual walk function is called if SWalkInfo pointer is defined
    // 
    //
    if ( aInfo )
        {
#ifdef __KERNEL_MODE__
		(void)aAllocatorType;
#if defined(_DEBUG)		
		if ( aBfrType == EGoodAllocatedCell )
			aInfo->iFunction(aInfo->iParam, aBfrType, ((TUint8*)aBfr+EDebugHdrSize), (aLth-EDebugHdrSize) );
		else
			aInfo->iFunction(aInfo->iParam, aBfrType,  aBfr, aLth );
#else
		aInfo->iFunction(aInfo->iParam, aBfrType, aBfr, aLth );
#endif
		
#else  // __KERNEL_MODE__
		
        if ( aAllocatorType & (EFullSlab + EPartialFullSlab + EEmptySlab + ESlabSpare) )
			{
			if ( aInfo->iHeap )
				{
				TUint32 dummy;
				TInt    npages;
				aInfo->iHeap->DoCheckSlab((slab*)aBfr, aAllocatorType);
				__HEAP_CORRUPTED_TEST_STATIC(aInfo->iHeap->CheckBitmap(Floor(aBfr, PAGESIZE), PAGESIZE, dummy, npages),
											 aInfo->iHeap, ETHeapBadCellAddress, aBfr, aLth);
				}
			if ( aAllocatorType & EPartialFullSlab )
				 WalkPartialFullSlab(aInfo, (slab*)aBfr, aBfrType, aLth);	
            else if ( aAllocatorType & EFullSlab )
					WalkFullSlab(aInfo, (slab*)aBfr, aBfrType, aLth);
			}
#if defined(_DEBUG)     
        else  if ( aBfrType == EGoodAllocatedCell )
            aInfo->iFunction(aInfo->iParam, aBfrType, ((TUint8*)aBfr+EDebugHdrSize), (aLth-EDebugHdrSize) );
        else
            aInfo->iFunction(aInfo->iParam, aBfrType,  aBfr, aLth );
#else
        else
            aInfo->iFunction(aInfo->iParam, aBfrType, aBfr, aLth );
#endif

#endif // __KERNEL_MODE	
        }