BOOL _DestroyCursor(
    PCURSOR pcur,
    DWORD   cmdDestroy)
{
    PPROCESSINFO ppi;
    PPROCESSINFO ppiCursor;
    int          i;
    extern BOOL DestroyAniIcon(PACON pacon);

    if (pcur == NULL) {
        UserAssert(FALSE);
        return(TRUE);
    }
    ppi = PpiCurrent();
    ppiCursor = GETPPI(pcur);

    /*
     * Remove this icon from the caption icon cache.
     */
    for (i = 0; i < CCACHEDCAPTIONS; i++) {
        if (cachedCaptions[i].spcursor == pcur) {
            Unlock( &(cachedCaptions[i].spcursor) );
        }
    }

    /*
     * First step in destroying an cursor
     */
    switch (cmdDestroy) {

    case CURSOR_ALWAYSDESTROY:

        /*
         * Always destroy? then don't do any checking...
         */
        break;

    case CURSOR_CALLFROMCLIENT:

        /*
         * Can't destroy public cursors/icons.
         */
        if (ppiCursor == NULL)
            /*
             * Fake success if its a resource loaded icon because
             * this is how win95 responded.
             */
            return !!(pcur->CURSORF_flags & CURSORF_FROMRESOURCE);

        /*
         * If this cursor was loaded from a resource, don't free it till the
         * process exits.  This is the way we stay compatible with win3.0's
         * cursors which were actually resources.  Resources under win3 have
         * reference counting and other "features" like handle values that
         * never change.  Read more in the comment in
         * ServerLoadCreateCursorIcon().
         */
        if (pcur->CURSORF_flags & (CURSORF_LRSHARED | CURSORF_SECRET)) {
            return TRUE;
        }

        /*
         * One thread can't destroy the objects created by another.
         */
        if (ppiCursor != ppi) {
            RIPERR0(ERROR_DESTROY_OBJECT_OF_OTHER_THREAD, RIP_VERBOSE, "");
            return FALSE;
        }

        /*
         * fall through.
         */

    case CURSOR_THREADCLEANUP:

        /*
         * Don't destroy public objects either (pretend it worked though).
         */
        if (ppiCursor == NULL)
            return TRUE;
        break;
    }

    /*
     * First mark the object for destruction.  This tells the locking code that
     * we want to destroy this object when the lock count goes to 0.  If this
     * returns FALSE, we can't destroy the object yet.
     */
    if (!HMMarkObjectDestroy((PHEAD)pcur))
        return FALSE;

    if (pcur->strName.Length != 0) {
        UserFreePool((LPSTR)pcur->strName.Buffer);
    }

    if (pcur->atomModName != 0) {
        DeleteAtom(pcur->atomModName);
    }

    /*
     * If this is an ACON call its special routine to destroy it.
     */
    if (pcur->CURSORF_flags & CURSORF_ACON) {
        DestroyAniIcon((PACON)pcur);
    } else {
        if (pcur->hbmMask != NULL) {
            GreDeleteObject(pcur->hbmMask);
        }
        if (pcur->hbmColor != NULL) {
            GreDeleteObject(pcur->hbmColor);
        }
    }

    /*
     * Ok to destroy...  Free the handle (which will free the object and the
     * handle).
     */
    DestroyEmptyCursorObject(pcur);
    return TRUE;
}