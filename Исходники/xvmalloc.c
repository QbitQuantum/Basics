/*
 * Free block identified with <page, offset>
 */
void xv_free(struct xv_pool *pool, struct page *page, u32 offset)
{
	void *page_start;
	struct block_header *block, *tmpblock;

	offset -= XV_ALIGN;

	spin_lock(&pool->lock);

	page_start = get_ptr_atomic(page, 0, KM_USER0);
	block = (struct block_header *)((char *)page_start + offset);

	/* Catch double free bugs */
	BUG_ON(test_flag(block, BLOCK_FREE));

	block->size = ALIGN(block->size, XV_ALIGN);

	tmpblock = BLOCK_NEXT(block);
	if (offset + block->size + XV_ALIGN == PAGE_SIZE)
		tmpblock = NULL;

	/* Merge next block if its free */
	if (tmpblock && test_flag(tmpblock, BLOCK_FREE)) {
		/*
		 * Blocks smaller than XV_MIN_ALLOC_SIZE
		 * are not inserted in any free list.
		 */
		if (tmpblock->size >= XV_MIN_ALLOC_SIZE) {
			remove_block(pool, page,
				    offset + block->size + XV_ALIGN, tmpblock,
				    get_index_for_insert(tmpblock->size));
		}
		block->size += tmpblock->size + XV_ALIGN;
	}

	/* Merge previous block if its free */
	if (test_flag(block, PREV_FREE)) {
		tmpblock = (struct block_header *)((char *)(page_start) +
						get_blockprev(block));
		offset = offset - tmpblock->size - XV_ALIGN;

		if (tmpblock->size >= XV_MIN_ALLOC_SIZE)
			remove_block(pool, page, offset, tmpblock,
				    get_index_for_insert(tmpblock->size));

		tmpblock->size += block->size + XV_ALIGN;
		block = tmpblock;
	}

	/* No used objects in this page. Free it. */
	if (block->size == PAGE_SIZE - XV_ALIGN) {
		put_ptr_atomic(page_start, KM_USER0);
		spin_unlock(&pool->lock);

		__free_page(page);
		stat_dec(&pool->total_pages);
		return;
	}

	set_flag(block, BLOCK_FREE);
	if (block->size >= XV_MIN_ALLOC_SIZE)
		insert_block(pool, page, offset, block);

	if (offset + block->size + XV_ALIGN != PAGE_SIZE) {
		tmpblock = BLOCK_NEXT(block);
		set_flag(tmpblock, PREV_FREE);
		set_blockprev(tmpblock, offset);
	}

	put_ptr_atomic(page_start, KM_USER0);
	spin_unlock(&pool->lock);
}