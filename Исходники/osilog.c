long osi_LogFDGetInfo(osi_fd_t *ifd, osi_remGetInfoParms_t *outp)
{
    osi_logFD_t *lfdp;
    osi_log_t *logp;
    osi_logEntry_t *lep;
    char tbuffer[256];
    long ix;

    lfdp = (osi_logFD_t *) ifd;
    logp = lfdp->logp;

    /* see if we're done */
    if (lfdp->current >= lfdp->nused) return OSI_DBRPC_EOF;

    /* grab lock */
    thrd_EnterCrit(&logp->cs);

    /* compute which one we want */
    ix = lfdp->first + lfdp->current;
    if (ix >= logp->alloc) ix -= logp->alloc;
    lfdp->current++;
    lep = logp->datap + ix;	/* ptr arith to current index */

    StringCbPrintfA(tbuffer, sizeof(tbuffer), lep->formatp, lep->parms[0], lep->parms[1],
                    lep->parms[2], lep->parms[3], lep->parms[4]);

    /* now copy out info */
    StringCbCopyA(outp->sdata[0], sizeof(outp->sdata[0]), tbuffer);
    StringCbPrintfA(tbuffer, sizeof(tbuffer), "%5.6f", ((double)lep->micros)/1000000.0);
    StringCbCopyA(outp->sdata[1], sizeof(outp->sdata[0]), tbuffer);
    outp->idata[0] = lep->tid;
    outp->scount = 2;
    outp->icount = 1;

    thrd_LeaveCrit(&logp->cs);
    return 0;
}