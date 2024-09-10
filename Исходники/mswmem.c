void *SubAlloc(WORD wSeg, unsigned size)

/* wSeg is the global segment's selector */
{
    HANDLE  hBlock;     /* better be a stack variable */
    void    *Block;     /* better be a stack variable */
#if MEMTRACE
    WORD    RealSize = 0;/* better be a stack variable */
#endif
    SWITCH_DS(wSeg)
    hBlock = LocalAlloc (LMEM_FIXED | LMEM_NOCOMPACT, size);
    /* no point attempting compaction: everything is FIXED
       in this heap! */
    if (hBlock) {
	Block = (void*)(LPSTR)LocalLock (hBlock);
#if MEMTRACE
	RealSize = LocalSize (hBlock);
#endif
    }
    RESTORE_DS
#if MEMTRACE
    mtr[mtrx].m_func = MTR_SUBALLOC;
    mtr[mtrx].m_ptr.m_block = hBlock ? Block : NULL;
    mtr[mtrx].m_size = RealSize;
    mtr[mtrx++].m_optimseg = OptimumSeg;
#endif
    if (hBlock) return Block;       /* success ! */
    else return NULL;               /* failure!! */
} /* SubAlloc */