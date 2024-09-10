// Free -- Free Memory ---------------------------------------------CHeapBlock-
//
// When a block is freed it is merged with previous and next block
// if they are free.  If merged with next block then next block is
// removed from list.  If not merged with either block then this 
// block is added to free list.
//
// NULL pointers and invalid block pointers are ignored.
//
// NOTE: Must be re-entrant
//
U32 CHeapBlock::Free(void *pData)
{
	BLKHEAD *pBlk,*pPrevBlk,*pNextBlk;
	U32 cbRet=0;
	
	if (pData != NULL) {
		pBlk = GetBlk(pData);

		// Check if allocated block
		if (pBlk->tThis == TYPEALLOC) {
			Critical section;

			cbRet=pBlk->sThis;

			FREE(cbRet, pBlk->raAlloc);

			// Merge with next block if it is free
			pNextBlk = GetNext(pBlk);
			if (pNextBlk->tThis == TYPEFREE) {
				_Unlink(pNextBlk);
				pBlk->sThis += pNextBlk->sThis + sizeof(BLKHEAD);
				GetNext(pBlk)->sPrev = pBlk->sThis;
			}

			// Merge with previous block if it is free
			pPrevBlk = GetPrev(pBlk);
			if (pPrevBlk->tThis != TYPEFREE) {
				pBlk->tThis = TYPEFREE;
				_Link(pBlk);
			}
			else {
				pPrevBlk->sThis += pBlk->sThis + sizeof(BLKHEAD);
				GetNext(pPrevBlk)->sPrev = pPrevBlk->sThis;
			}
		}
	}

	return cbRet;
}