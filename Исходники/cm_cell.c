/* if it's from DNS, see if it has expired
 * and check to make sure we have a valid set of volume servers
 * this function must not be called with a lock on cm_cellLock
 */
cm_cell_t *cm_UpdateCell(cm_cell_t * cp, afs_uint32 flags)
{
    long code = 0;
    cm_cell_rock_t rock;
    afs_uint32 mxheld = 0;

    if (cp == NULL)
        return NULL;

    lock_ObtainMutex(&cp->mx);
    mxheld = 1;

#ifdef AFS_FREELANCE_CLIENT
    if (cp->flags & CM_CELLFLAG_FREELANCE) {
        lock_ReleaseMutex(&cp->mx);
        return cp;
    }
#endif

    if (cm_IsServerListEmpty(cp->vlServersp) ||
        (time(0) > cp->timeout) ||
        (cm_dnsEnabled &&
         (cp->flags & CM_CELLFLAG_DNS) &&
         ((cp->flags & CM_CELLFLAG_VLSERVER_INVALID))))
    {
        lock_ReleaseMutex(&cp->mx);
        mxheld = 0;

        /* must empty cp->vlServersp */
        if (cp->vlServersp)
            cm_FreeServerList(&cp->vlServersp, CM_FREESERVERLIST_DELETE);

        rock.cellp = cp;
        rock.flags = flags;
        code = cm_SearchCellRegistry(1, cp->name, NULL, cp->linkedName, cm_AddCellProc, &rock);
        if (code && code != CM_ERROR_FORCE_DNS_LOOKUP)
            code = cm_SearchCellFileEx(cp->name, NULL, cp->linkedName, cm_AddCellProc, &rock);
        if (code == 0) {
            lock_ObtainMutex(&cp->mx);
            mxheld = 1;
	    cp->timeout = time(0) + 7200;
        }
        else {
            if (cm_dnsEnabled) {
                int ttl;

                code = cm_SearchCellByDNS(cp->name, NULL, &ttl, cm_AddCellProc, &rock);
                if (code == 0) {   /* got cell from DNS */
                    lock_ObtainMutex(&cp->mx);
                    mxheld = 1;
                    _InterlockedOr(&cp->flags, CM_CELLFLAG_DNS);
                    _InterlockedAnd(&cp->flags, ~CM_CELLFLAG_VLSERVER_INVALID);
		    cp->timeout = time(0) + ttl;
#ifdef DEBUG
                    fprintf(stderr, "cell %s: ttl=%d\n", cp->name, ttl);
#endif
		} else {
                    /* if we fail to find it this time, we'll just do nothing and leave the
                     * current entry alone
		     */
                    lock_ObtainMutex(&cp->mx);
                    mxheld = 1;
                    _InterlockedOr(&cp->flags, CM_CELLFLAG_VLSERVER_INVALID);
                }
	    }
	}
    }

    if (code == 0)
        cm_RandomizeServer(&cp->vlServersp);

    if (mxheld)
        lock_ReleaseMutex(&cp->mx);

    return code ? NULL : cp;
}