void zend_hash_display(const HashTable *ht)
{
    Bucket *p;
    uint i;

    if (UNEXPECTED(ht->nNumOfElements == 0)) {
        zend_output_debug_string(0, "The hash is empty");
        return;
    }
    for (i = 0; i < ht->nNumOfElements; i++) {
        p = ht->arBuckets[i];
        while (p != NULL) {
            zend_output_debug_string(0, "%s <==> 0x%lX\n", p->arKey, p->h);
            p = p->pNext;
        }
    }

    p = ht->pListTail;
    while (p != NULL) {
        zend_output_debug_string(0, "%s <==> 0x%lX\n", p->arKey, p->h);
        p = p->pListLast;
    }
}