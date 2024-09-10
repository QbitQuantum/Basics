static INLINE void disposeFpgmPrep(MOVE table_fpgm_prep *table) {
	if (table->tag) sdsfree(table->tag);
	if (table->bytes) FREE(table->bytes);
}