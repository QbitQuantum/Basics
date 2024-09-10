void tss_delete( tss_t key )
{
    struct _PDCLIB_tss * prev = NULL;
    struct _PDCLIB_tss * cur  = _PDCLIB_tss_first;
    while(cur) {
        if(cur == key) {
            if(prev) {
                prev->_Next = key->_Next;
            } else {
                _PDCLIB_tss_first = key->_Next;
            }

            TlsFree(key->_Key);
            free(key);
            return;
        }
    }

    // Not actually a TSS key
    abort();
}