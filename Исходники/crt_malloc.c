void
CrT_free(void *p, const char *file, int line)
{
#if defined(HAVE_PTHREAD_H)
	LOCKCRT();
#endif
    Header m = ((Header) p) - 1;
    Block b = m->b;

#ifdef CRT_DEBUG_ALSO
    /* Look around for trashed ram blocks: */
    if (*m->end == CRT_FREE_MAGIC)
        crash("Duplicate free()", m, file, line);

    check_block(m, __FILE__, __LINE__);
    CrT_check(file, line);
    /* Don't clobber 'rover': */
    if (rover == m) {
        rover = rover->next;
    }
    /* Remove m from linklist of allocated blocks: */
    REMOVE(m);
    /* Remove m from just_touched[], if present: */
    {
        int i = CRT_NEW_TO_CHECK;

        while (i-- > 0) {
            if (just_touched[i] == m) {
                just_touched[i] = &root;
            }
        }
    }
    /* Mark m so as to give some chance of */
    /* diagnosing repeat free()s of same   */
    /* block:                              */
    *m->end = CRT_FREE_MAGIC;
#endif

    b->live_bytes -= m->size;
    b->live_blocks--;

    free(m);
#if defined(HAVE_PTHREAD_H)
	UNLOCKCRT();
#endif
}