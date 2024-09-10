static int fmap_readpage(fmap_t *m, unsigned int first_page, unsigned int count, unsigned int lock_count) {
    size_t readsz = 0, eintr_off;
    char *pptr = NULL, errtxt[256];
    uint32_t s;
    unsigned int i, page = first_page, force_read = 0;

    fmap_lock;
    for(i=0; i<count; i++) { /* prefault */
	/* Not worth checking if the page is already paged, just ping each */
	/* Also not worth reusing the loop below */
	volatile char faultme;
	faultme = ((char *)m)[(first_page+i) * m->pgsz + m->hdrsz];
    }
    fmap_unlock;
    for(i=0; i<=count; i++, page++) {
	int lock;
	if(lock_count) {
	    lock_count--;
	    lock = 1;
	} else lock = 0;
	if(i == count) {
	    /* we count one page too much to flush pending reads */
	    if(!pptr) return 0; /* if we have any */
	    force_read = 1;
	} else if((s=fmap_bitmap[page]) & FM_MASK_PAGED) {
	    /* page already paged */
	    if(lock) {
		/* we want locking */
		if(s & FM_MASK_LOCKED) {
		    /* page already locked */
		    s &= FM_MASK_COUNT;
		    if(s == FM_MASK_COUNT) { /* lock count already at max: fial! */
			cli_errmsg("fmap_readpage: lock count exceeded\n");
			return 1;
		    }
		    /* acceptable lock count: inc lock count */
		    fmap_bitmap[page]++;
		} else /* page not currently locked: set lock count = 1 */
		    fmap_bitmap[page] = 1 | FM_MASK_LOCKED | FM_MASK_PAGED;
	    } else {
		/* we don't want locking */
		if(!(s & FM_MASK_LOCKED)) {
		    /* page is not locked: we reset aging to max */
		    fmap_bitmap[page] = FM_MASK_PAGED | FM_MASK_COUNT;
		}
	    }
	    if(!pptr) continue;
	    force_read = 1;
	}

	if(force_read) {
	    /* we have some pending reads to perform */
	    if (m->handle_is_fd) {
		unsigned int j;
		int _fd = (int)(ssize_t)m->handle;
		for(j=first_page; j<page; j++) {
		    if(fmap_bitmap[j] & FM_MASK_SEEN) {
			/* page we've seen before: check mtime */
			STATBUF st;
			if(FSTAT(_fd, &st)) {
			    cli_strerror(errno, errtxt, sizeof(errtxt));
			    cli_warnmsg("fmap_readpage: fstat failed: %s\n", errtxt);
			    return 1;
			}
			if(m->mtime != st.st_mtime) {
			    cli_warnmsg("fmap_readpage: file changed as we read it\n");
			    return 1;
			}
			break;
		    }
		}
	    }

	    eintr_off = 0;
	    while(readsz) {
		ssize_t got;
		off_t target_offset = eintr_off + m->offset + (first_page * m->pgsz);
		got=m->pread_cb(m->handle, pptr, readsz, target_offset);

		if(got < 0 && errno == EINTR)
		    continue;

		if(got > 0) {
		    pptr += got;
		    eintr_off += got;
		    readsz -= got;
		    continue;
		}

		if(got < 0) {
		    cli_strerror(errno, errtxt, sizeof(errtxt));
		    cli_errmsg("fmap_readpage: pread error: %s\n", errtxt);
		}
		else {
		    cli_warnmsg("fmap_readpage: pread fail: asked for %lu bytes @ offset %lu, got %lu\n", (long unsigned int)readsz, (long unsigned int)target_offset, (long unsigned int)got);
		}
		return 1;
	    }

	    pptr = NULL;
	    force_read = 0;
	    readsz = 0;
	    continue;
	}

	/* page is not already paged */
	if(!pptr) {
	    /* set a new start for pending reads if we don't have one */
	    pptr = (char *)m + page * m->pgsz + m->hdrsz;
	    first_page = page;
	}
	if((page == m->pages - 1) && (m->real_len % m->pgsz))
	    readsz += m->real_len % m->pgsz;
	else
	    readsz += m->pgsz;
	if(lock) /* lock requested: set paged, lock page and set lock count to 1 */
	    fmap_bitmap[page] = FM_MASK_PAGED | FM_MASK_LOCKED | 1;
	else /* no locking: set paged and set aging to max */
	    fmap_bitmap[page] = FM_MASK_PAGED | FM_MASK_COUNT;
	m->paged++;
    }
    return 0;
}