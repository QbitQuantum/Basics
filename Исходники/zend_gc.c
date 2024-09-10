ZEND_API void ZEND_FASTCALL gc_remove_from_buffer(zend_refcounted *ref)
{
	gc_root_buffer *root;
	uint32_t idx = GC_REF_ADDRESS(ref);

	GC_BENCH_INC(zval_remove_from_buffer);

	if (!GC_REF_CHECK_COLOR(ref, GC_BLACK)) {
		GC_TRACE_SET_COLOR(ref, GC_BLACK);
	}
	GC_REF_SET_INFO(ref, 0);

	/* Perform decompression only in case of large buffers */
	if (UNEXPECTED(GC_G(first_unused) >= GC_MAX_UNCOMPRESSED)) {
		gc_remove_compressed(ref, idx);
		return;
	}

	ZEND_ASSERT(idx);
	root = GC_IDX2PTR(idx);
	gc_remove_from_roots(root);
}