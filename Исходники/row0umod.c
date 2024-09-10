/***********************************************************//**
Delete unmarks a secondary index entry which must be found. It might not be
delete-marked at the moment, but it does not harm to unmark it anyway. We also
need to update the fields of the secondary index record if we updated its
fields but alphabetically they stayed the same, e.g., 'abc' -> 'aBc'.
@return	DB_FAIL or DB_SUCCESS or DB_OUT_OF_FILE_SPACE */
static
ulint
row_undo_mod_del_unmark_sec_and_undo_update(
    /*========================================*/
    ulint		mode,	/*!< in: search mode: BTR_MODIFY_LEAF or
				BTR_MODIFY_TREE */
    que_thr_t*	thr,	/*!< in: query thread */
    dict_index_t*	index,	/*!< in: index */
    const dtuple_t*	entry)	/*!< in: index entry */
{
    mem_heap_t*	heap;
    btr_pcur_t	pcur;
    upd_t*		update;
    ulint		err		= DB_SUCCESS;
    big_rec_t*	dummy_big_rec;
    mtr_t		mtr;
    trx_t*		trx		= thr_get_trx(thr);

    /* Ignore indexes that are being created. */
    if (UNIV_UNLIKELY(*index->name == TEMP_INDEX_PREFIX)) {

        return(DB_SUCCESS);
    }

    log_free_check();
    mtr_start(&mtr);

    if (UNIV_UNLIKELY(!row_search_index_entry(index, entry,
                      mode, &pcur, &mtr))) {
        fputs("InnoDB: error in sec index entry del undo in\n"
              "InnoDB: ", stderr);
        dict_index_name_print(stderr, trx, index);
        fputs("\n"
              "InnoDB: tuple ", stderr);
        dtuple_print(stderr, entry);
        fputs("\n"
              "InnoDB: record ", stderr);
        rec_print(stderr, btr_pcur_get_rec(&pcur), index);
        putc('\n', stderr);
        trx_print(stderr, trx, 0);
        fputs("\n"
              "InnoDB: Submit a detailed bug report"
              " to http://bugs.mysql.com\n", stderr);
    } else {
        btr_cur_t*	btr_cur = btr_pcur_get_btr_cur(&pcur);

        err = btr_cur_del_mark_set_sec_rec(BTR_NO_LOCKING_FLAG,
                                           btr_cur, FALSE, thr, &mtr);
        ut_a(err == DB_SUCCESS);
        heap = mem_heap_create(100);

        update = row_upd_build_sec_rec_difference_binary(
                     index, entry, btr_cur_get_rec(btr_cur), trx, heap);
        if (upd_get_n_fields(update) == 0) {

            /* Do nothing */

        } else if (mode == BTR_MODIFY_LEAF) {
            /* Try an optimistic updating of the record, keeping
            changes within the page */

            err = btr_cur_optimistic_update(
                      BTR_KEEP_SYS_FLAG | BTR_NO_LOCKING_FLAG,
                      btr_cur, update, 0, thr, &mtr);
            switch (err) {
            case DB_OVERFLOW:
            case DB_UNDERFLOW:
            case DB_ZIP_OVERFLOW:
                err = DB_FAIL;
            }
        } else {
            ut_a(mode == BTR_MODIFY_TREE);
            err = btr_cur_pessimistic_update(
                      BTR_KEEP_SYS_FLAG | BTR_NO_LOCKING_FLAG,
                      btr_cur, &heap, &dummy_big_rec,
                      update, 0, thr, &mtr);
            ut_a(!dummy_big_rec);
        }

        mem_heap_free(heap);
    }

    btr_pcur_close(&pcur);
    mtr_commit(&mtr);

    return(err);
}