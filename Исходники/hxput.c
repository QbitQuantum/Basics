//--------------|---------------------------------------------
HXRET
hxput(HXFILE * hp, char const *recp, int leng)
{
    HXLOCAL loc, *locp = &loc;

    if (!hp || leng < 0 || !recp || leng > hxmaxrec(hp)
        || !(hp->mode & HX_UPDATE) || !hp->test)
        return HXERR_BAD_REQUEST;

    if (leng && !hx_test(hp, recp, leng))
        return HXERR_BAD_RECORD;

    if (SCANNING(hp) && hx_diff(hp, recp, RECDATA(_hxcurrec(hp))))
        return HXERR_BAD_REQUEST;

    ENTER(locp, hp, recp, 3);
    _hxlockset(locp, leng ? HIGH_LOCK : HEAD_LOCK);
    if (IS_MMAP(hp))
        _hxremap(locp);

    int     may_find = 1, loops = HX_MAX_CHAIN;
    int     newsize = leng ? leng + sizeof(HXREC) : 0;
    HXBUF  *currp = &locp->buf[0], *prevp = &locp->buf[1];

    // If scanning is on an overflow page, and hxdel might
    //  empty the page, hxput after hxnext can't just jump to
    //  the right page, because (prevp) is not loaded,
    //  so deleting currp would hard.
    _hxload(locp, currp, SCANNING(hp) && (leng || IS_HEAD(hp->buffer.pgno))
            ? hp->buffer.pgno : locp->head);

    while (1) {
        int     pos, hindpos, skip = 0;
        PAGENO  nextpg = currp->next;

        if (!--loops)
            LEAVE(locp, HXERR_BAD_FILE);

        // Search for the key (an old record to be deleted).
        // If SCANNING: the file is locked, and the matching
        //  record must be there.
        pos = !may_find ? -1
            : !SCANNING(hp) ? _hxfind(locp, currp, locp->hash, recp, &hindpos)
            : currp->pgno == hp->buffer.pgno ? hp->currpos : -1;

        if (pos >= 0) {
            char   *oldp = currp->data + pos;
            COUNT   oldsize = RECSIZE(oldp);
            int     delta = newsize - oldsize;

            locp->ret = RECLENG(oldp);
            may_find = 0;
            assert(!currp->delta);
            currp->delpos = pos;
            currp->delta = delta;

            if (!newsize) {     // hxdel or remove after inserted previously.

                _hxremove(currp, pos, oldsize);
                currp->recs--;
                if (SCANNING(hp))
                    hp->recsize = 0;

            } else if (FITS(hp, currp, delta, 0)) { // replace

                if (delta) {
                    memmove(oldp + newsize, oldp + oldsize,
                            currp->used - pos - oldsize);
                    currp->used += delta;
                    STSH(leng, oldp + sizeof(PAGENO));
                    if (SCANNING(hp))
                        hp->recsize = newsize;
                    DEINDEX(currp); // force indexify
                }

                memcpy(oldp + sizeof(HXREC), recp, leng);
                STAIN(currp);
                newsize = 0;

            } else if (SCANNING(hp)) {
                // At this point we are stuck: if we delete the old copy of
                // the record, we are committed to inserting the new copy
                // somewhere else, but that might require changing links
                // or even growing the file: a NO-NO during a hxnext scan.
                LEAVE(locp, HXERR_BAD_REQUEST);

            } else {            // Delete old version and continue (insert elsewhere).

                _hxremove(currp, pos, oldsize);
                currp->recs--;
            }
        }

        if (currp->used && !IS_HEAD(currp->pgno) && SHRUNK(prevp))
            skip = !_hxshift(locp, locp->head, 0, currp, prevp, NULL);

        // Insert the new record if it fits.
        if (newsize && FITS(hp, currp, newsize, 1)) {

            HXREC   hdr;

            STLG(locp->hash, &hdr.hash);
            STSH(leng, &hdr.leng);
            _hxappend(currp, (char *)&hdr, sizeof hdr);
            _hxappend(currp, recp, leng);
            currp->recs++;
            newsize = 0;
        }
        // If the current page contains only data of OTHER heads 
        // -- and hence, must be at the END of a chain --
        // unlink it from this chain. If the page is empty,
        // unlink it AND put it in the freemap.
        if (IS_HEAD(currp->pgno)) {
            skip = 0;
        } else if (!currp->used) {
            skip = 1;
            _hxputfreed(locp, currp);
            if (SCANNING(hp) && hp->buffer.pgno == currp->pgno)
                hp->buffer.used = 0;
        } else if (currp->next || !SHRUNK(currp)) {
            skip = 0;
        } else if (!skip) {     // If skip not set by _hxshift above...
            char const *rp, *ep;

            FOR_EACH_REC(rp, currp, ep)
                if (locp->head == _hxhead(locp, RECHASH(rp)))
                break;
            skip = rp == ep;    // No recs for locp->head in this tail.
        }
        if (skip)
            LINK(prevp, nextpg);
        else
            SWAP(prevp, currp);

        sync_save(locp, currp);

        if (!newsize && !prevp->next)
            break;

        if (!newsize && !may_find && !SHRUNK(prevp))
            break;

        if (prevp->next) {
            _hxload(locp, currp, prevp->next);
            continue;
        }
        // We are at the end of the chain, and rec not yet inserted.

        // Unlocking is necessary even if tail is not shared;
        //  it may be hp->tail.pgno in some other process.
        if (!FILE_HELD(hp) && !IS_HEAD(prevp->pgno))
            _hxunlock(locp, prevp->pgno, 1);

        // _hxshare/_hxfindfree may update the map (root etc).
        // Split MUST be locked before root, else risk deadlock.
        _hxlockset(locp, BOTH_LOCK);
        if (IS_MMAP(hp))
            _hxremap(locp);
        // At this point assert:
        // - head is locked, split is locked,
        // - head matches hash, npages matches filesize.
        // After locking the split, no other process can change
        // the file size.
        may_find = 0;
        COUNT   need = IS_HEAD(prevp->pgno) ? newsize : 0;

        if (!_hxshare(locp, currp, need)
            && !_hxgetfreed(locp, currp)
            && !_hxfindfree(locp, currp)) {

            // _hxgrow will zero samehead if it splits locp->head.
            PAGENO  samehead = locp->head;

            // _hxgrow will change the file length. A concurrent
            //  hxget/hxdel could miscalculate locp->head as
            //  being the newly-added page.
            _hxlock(locp, locp->npages, 0);
            _hxgrow(locp, currp, need, &samehead);
            DEBUG3("head=%u samehead=%u", locp->head, samehead);
            if (!samehead) {
                _hxputfreed(locp, currp);
                _hxpoint(locp);
                _hxload(locp, currp, locp->head);
                loops = HX_MAX_CHAIN;
                continue;
            }
        }
        // _hxgrow may clobber prevp, so we reload it. Even if
        // prevp->pgno == locp->head, prevp may contain an
        // obsolete copy of the head page. The empty page is
        // always appended to head. _hxshare only returns true
        // if currp is head and currp->next is 0, so it can't
        // clobber it. 

        _hxsave(locp, prevp);
        _hxload(locp, prevp, locp->head);
        LINK(currp, prevp->next);
        LINK(prevp, currp->pgno);
        currp->orig = DATASIZE(hp); // make SHRUNK be true
    }