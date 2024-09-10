/**************************************************************//**
Restores the stored position of a persistent cursor bufferfixing the page and
obtaining the specified latches. If the cursor position was saved when the
(1) cursor was positioned on a user record: this function restores the position
to the last record LESS OR EQUAL to the stored record;
(2) cursor was positioned on a page infimum record: restores the position to
the last record LESS than the user record which was the successor of the page
infimum;
(3) cursor was positioned on the page supremum: restores to the first record
GREATER than the user record which was the predecessor of the supremum.
(4) cursor was positioned before the first or after the last in an empty tree:
restores to before first or after the last in the tree.
@return TRUE if the cursor position was stored when it was on a user
record and it can be restored on a user record whose ordering fields
are identical to the ones of the original user record */
UNIV_INTERN
ibool
btr_pcur_restore_position_func(
/*===========================*/
	ulint		latch_mode,	/*!< in: BTR_SEARCH_LEAF, ... */
	btr_pcur_t*	cursor,		/*!< in: detached persistent cursor */
	const char*	file,		/*!< in: file name */
	ulint		line,		/*!< in: line where called */
	mtr_t*		mtr)		/*!< in: mtr */
{
	dict_index_t*	index;
	dtuple_t*	tuple;
	ulint		mode;
	ulint		old_mode;
	mem_heap_t*	heap;

	ut_ad(mtr);
	ut_ad(mtr->state == MTR_ACTIVE);

	index = btr_cur_get_index(btr_pcur_get_btr_cur(cursor));

	if (UNIV_UNLIKELY(cursor->old_stored != BTR_PCUR_OLD_STORED)
	    || UNIV_UNLIKELY(cursor->pos_state != BTR_PCUR_WAS_POSITIONED
			     && cursor->pos_state != BTR_PCUR_IS_POSITIONED)) {
		ut_print_buf(stderr, cursor, sizeof(btr_pcur_t));
		putc('\n', stderr);
		if (cursor->trx_if_known) {
			trx_print(stderr, cursor->trx_if_known, 0);
		}

		ut_error;
	}

	if (UNIV_UNLIKELY
	    (cursor->rel_pos == BTR_PCUR_AFTER_LAST_IN_TREE
	     || cursor->rel_pos == BTR_PCUR_BEFORE_FIRST_IN_TREE)) {

		/* In these cases we do not try an optimistic restoration,
		but always do a search */

		btr_cur_open_at_index_side(
			cursor->rel_pos == BTR_PCUR_BEFORE_FIRST_IN_TREE,
			index, latch_mode, btr_pcur_get_btr_cur(cursor), mtr);

		cursor->block_when_stored = btr_pcur_get_block(cursor);

		return(FALSE);
	}

	ut_a(cursor->old_rec);
	ut_a(cursor->old_n_fields);

	if (UNIV_LIKELY(latch_mode == BTR_SEARCH_LEAF)
	    || UNIV_LIKELY(latch_mode == BTR_MODIFY_LEAF)) {
		/* Try optimistic restoration */

		if (UNIV_LIKELY(buf_page_optimistic_get(
					latch_mode,
					cursor->block_when_stored,
					cursor->modify_clock,
					file, line, mtr))) {
			cursor->pos_state = BTR_PCUR_IS_POSITIONED;

			buf_block_dbg_add_level(btr_pcur_get_block(cursor),
						SYNC_TREE_NODE);

			if (cursor->rel_pos == BTR_PCUR_ON) {
#ifdef UNIV_DEBUG
				const rec_t*	rec;
				const ulint*	offsets1;
				const ulint*	offsets2;
#endif /* UNIV_DEBUG */
				cursor->latch_mode = latch_mode;
#ifdef UNIV_DEBUG
				rec = btr_pcur_get_rec(cursor);

				heap = mem_heap_create(256);
				offsets1 = rec_get_offsets(
					cursor->old_rec, index, NULL,
					cursor->old_n_fields, &heap);
				offsets2 = rec_get_offsets(
					rec, index, NULL,
					cursor->old_n_fields, &heap);

				ut_ad(!cmp_rec_rec(cursor->old_rec,
						   rec, offsets1, offsets2,
						   index));
				mem_heap_free(heap);
#endif /* UNIV_DEBUG */
				return(TRUE);
			}

			return(FALSE);
		}
	}

	/* If optimistic restoration did not succeed, open the cursor anew */

	heap = mem_heap_create(256);

	tuple = dict_index_build_data_tuple(index, cursor->old_rec,
					    cursor->old_n_fields, heap);

	/* Save the old search mode of the cursor */
	old_mode = cursor->search_mode;

	if (UNIV_LIKELY(cursor->rel_pos == BTR_PCUR_ON)) {
		mode = PAGE_CUR_LE;
	} else if (cursor->rel_pos == BTR_PCUR_AFTER) {
		mode = PAGE_CUR_G;
	} else {
		ut_ad(cursor->rel_pos == BTR_PCUR_BEFORE);
		mode = PAGE_CUR_L;
	}

	btr_pcur_open_with_no_init_func(index, tuple, mode, latch_mode,
					cursor, 0, file, line, mtr);

	/* Restore the old search mode */
	cursor->search_mode = old_mode;

	if (cursor->rel_pos == BTR_PCUR_ON
	    && btr_pcur_is_on_user_rec(cursor)
	    && 0 == cmp_dtuple_rec(tuple, btr_pcur_get_rec(cursor),
				   rec_get_offsets(
					   btr_pcur_get_rec(cursor), index,
					   NULL, ULINT_UNDEFINED, &heap))) {

		/* We have to store the NEW value for the modify clock, since
		the cursor can now be on a different page! But we can retain
		the value of old_rec */

		cursor->block_when_stored = btr_pcur_get_block(cursor);
		cursor->modify_clock = buf_block_get_modify_clock(
			cursor->block_when_stored);
		cursor->old_stored = BTR_PCUR_OLD_STORED;

		mem_heap_free(heap);

		return(TRUE);
	}

	mem_heap_free(heap);

	/* We have to store new position information, modify_clock etc.,
	to the cursor because it can now be on a different page, the record
	under it may have been removed, etc. */

	btr_pcur_store_position(cursor, mtr);

	return(FALSE);
}