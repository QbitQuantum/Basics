/* Clear both lists.  Called without the allocation lock held.          */
GC_INNER void GC_print_all_errors(void)
{
    static GC_bool printing_errors = FALSE;
    GC_bool have_errors;
    unsigned i;
    DCL_LOCK_STATE;

    LOCK();
    if (printing_errors) {
        UNLOCK();
        return;
    }
    have_errors = GC_have_errors;
    printing_errors = TRUE;
    UNLOCK();

    if (GC_debugging_started) {
        GC_print_all_smashed();
    } else {
        have_errors = FALSE;
    }

    for (i = 0; i < GC_n_leaked; ++i) {
        ptr_t p = GC_leaked[i];
        if (HDR(p) -> hb_obj_kind == PTRFREE) {
            GC_err_printf("Leaked atomic object at ");
        } else {
            GC_err_printf("Leaked composite object at ");
        }
        GC_print_heap_obj(p);
        GC_err_printf("\n");
        GC_free(p);
        GC_leaked[i] = 0;
        have_errors = TRUE;
    }
    GC_n_leaked = 0;

    if (have_errors
#       ifndef GC_ABORT_ON_LEAK
            && GETENV("GC_ABORT_ON_LEAK") != NULL
#       endif
       ) {
        ABORT("Leaked or smashed objects encountered");
    }

    printing_errors = FALSE;
}