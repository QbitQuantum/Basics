static int zram_bvec_write(struct zram *zram, struct bio_vec *bvec, u32 index,
			   int offset)
{
	int ret;
	u32 store_offset;
	size_t clen;
	struct zobj_header *zheader;
	struct page *page, *page_store;
	unsigned char *user_mem, *cmem, *src, *uncmem = NULL;

	page = bvec->bv_page;
	src = zram->compress_buffer;

	if (is_partial_io(bvec)) {
		/*
		 * This is a partial IO. We need to read the full page
		 * before to write the changes.
		 */
		uncmem = kmalloc(PAGE_SIZE, GFP_KERNEL);
		if (!uncmem) {
			pr_info("Error allocating temp memory!\n");
			ret = -ENOMEM;
			goto out;
		}
		ret = zram_read_before_write(zram, uncmem, index);
		if (ret) {
			kfree(uncmem);
			goto out;
		}
	}

	/*
	 * System overwrites unused sectors. Free memory associated
	 * with this sector now.
	 */
	if (zram->table[index].page ||
	    zram_test_flag(zram, index, ZRAM_ZERO))
		zram_free_page(zram, index);

	user_mem = kmap_atomic(page, KM_USER0);

	if (is_partial_io(bvec))
		memcpy(uncmem + offset, user_mem + bvec->bv_offset,
		       bvec->bv_len);
	else
		uncmem = user_mem;

	if (page_zero_filled(uncmem)) {
		kunmap_atomic(user_mem, KM_USER0);
		if (is_partial_io(bvec))
			kfree(uncmem);
		zram_stat_inc(&zram->stats.pages_zero);
		zram_set_flag(zram, index, ZRAM_ZERO);
		ret = 0;
		goto out;
	}

	COMPRESS(uncmem, PAGE_SIZE, src, &clen,
		zram->compress_workmem);
	ret = 0;

	kunmap_atomic(user_mem, KM_USER0);
	if (is_partial_io(bvec))
			kfree(uncmem);

	if (unlikely(ret != 0)) {
		pr_err("Compression failed! err=%d\n", ret);
		goto out;
	}

	/*
	 * Page is incompressible. Store it as-is (uncompressed)
	 * since we do not want to return too many disk write
	 * errors which has side effect of hanging the system.
	 */
	if (unlikely(clen > max_zpage_size)) {
		clen = PAGE_SIZE;
		page_store = alloc_page(GFP_NOIO | __GFP_HIGHMEM);
		if (unlikely(!page_store)) {
			pr_info("Error allocating memory for "
				"incompressible page: %u\n", index);
			ret = -ENOMEM;
			goto out;
		}

		store_offset = 0;
		zram_set_flag(zram, index, ZRAM_UNCOMPRESSED);
		zram_stat_inc(&zram->stats.pages_expand);
		zram->table[index].page = page_store;
		src = kmap_atomic(page, KM_USER0);
		goto memstore;
	}

	if (xv_malloc(zram->mem_pool, clen + sizeof(*zheader),
		      &zram->table[index].page, &store_offset,
		      GFP_NOIO | __GFP_HIGHMEM)) {
		pr_info("Error allocating memory for compressed "
			"page: %u, size=%zu\n", index, clen);
		ret = -ENOMEM;
		goto out;
	}

memstore:
	zram->table[index].offset = store_offset;

	cmem = kmap_atomic(zram->table[index].page, KM_USER1) +
		zram->table[index].offset;

#if 0
	/* Back-reference needed for memory defragmentation */
	if (!zram_test_flag(zram, index, ZRAM_UNCOMPRESSED)) {
		zheader = (struct zobj_header *)cmem;
		zheader->table_idx = index;
		cmem += sizeof(*zheader);
	}
#endif

	memcpy(cmem, src, clen);

	kunmap_atomic(cmem, KM_USER1);
	if (unlikely(zram_test_flag(zram, index, ZRAM_UNCOMPRESSED)))
		kunmap_atomic(src, KM_USER0);

	/* Update stats */
	zram_stat64_add(zram, &zram->stats.compr_size, clen);
	zram_stat_inc(&zram->stats.pages_stored);
	if (clen <= PAGE_SIZE / 2)
		zram_stat_inc(&zram->stats.good_compress);

	return 0;

out:
	if (ret)
		zram_stat64_inc(zram, &zram->stats.failed_writes);
	return ret;
}