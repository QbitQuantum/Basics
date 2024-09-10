/* OleStdFree
** ----------
**    free memory using the currently active IMalloc* allocator
*/
STDAPI_(void) OleStdFree(LPVOID pmem)
{
#ifdef Q_OS_TEMP
    return;
#else
    LPMALLOC pmalloc;

    if (pmem == NULL)
        return;

    if (CoGetMalloc(MEMCTX_TASK, &pmalloc) != NOERROR) {
        return;
    }

    pmalloc->lpVtbl->Free(pmalloc, pmem);

    if (pmalloc != NULL) {
        pmalloc->lpVtbl->Release(pmalloc);
    }
#endif
}