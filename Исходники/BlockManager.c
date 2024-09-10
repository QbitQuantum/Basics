void blman_realloc_blocks(blman *self)
{
    //inc block count
    self->blockCount += 1;

    //realloc block array
#ifndef _ALIGNED_REALLOC
    void *pNewBlocks = _ALIGNED_MALLOC(self->blockCount * BLOCK_SIZE, g_DataFileMallocAlignment);
    memcpy(pNewBlocks, self->blocks, (self->blockCount - 1) * BLOCK_SIZE);
    _ALIGNED_FREE(self->blocks);
    assert(pNewBlocks);
#else
    void *pNewBlocks = _ALIGNED_REALLOC(self->blocks, self->blockCount * BLOCK_SIZE, g_DataFileMallocAlignment);
    assert(pNewBlocks);
#endif
    
    //set new pointer
    self->blocks = (uint8*)pNewBlocks;

    //get new block
    uint8 *pNewBlock = blman_get_block(self, self->blockCount - 1);
    memset(pNewBlock, 0, BLOCK_SIZE);

    //init new block
    Block_InitBlock(pNewBlock);
}