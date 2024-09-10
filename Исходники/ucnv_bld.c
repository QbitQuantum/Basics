/*                Not supported  API.  Marked U_CAPI only for use by test programs.    */
U_CFUNC UBool U_EXPORT2 ucnv_cleanup(void) {
    if (SHARED_DATA_HASHTABLE != NULL) {
        ucnv_flushCache();
        if (SHARED_DATA_HASHTABLE != NULL && uhash_count(SHARED_DATA_HASHTABLE) == 0) {
            uhash_close(SHARED_DATA_HASHTABLE);
            SHARED_DATA_HASHTABLE = NULL;
        }
    }

    umtx_destroy(&cnvCacheMutex);           /* Don't worry about destroying the mutex even  */
                                            /*  if the hash table still exists.  The mutex  */
                                            /*  will lazily re-init  itself if needed.      */
    return (SHARED_DATA_HASHTABLE == NULL);
}