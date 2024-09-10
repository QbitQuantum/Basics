/* The destructor function for a collation-based indexer. */
static void
collation_indexer_destroy (indexer_t* ix)
{
    collation_indexer_t* etc = (collation_indexer_t*) ix->ix_etc;
    if (etc->converter) {
        ucnv_close(etc->converter);
        etc->converter = NULL;
    }

    if (etc->collator) {
        ucol_close(etc->collator);
        etc->collator = NULL;
    }
    if (etc->ix_keys != NULL) {
        ber_bvecfree (etc->ix_keys);
        etc->ix_keys = NULL;
    }
    slapi_ch_free((void**)&ix->ix_etc);
    ix->ix_etc = NULL; /* just for hygiene */
}