/*
 * Dump the contents of a journal file.
 * @fn: journal filename to query.
 *
 * Each time mds restarts, it writes log entries starting from the very
 * first slot of the log.  Anyway, the function dumps all log entries,
 * some of them may be from previous incarnations of the MDS.
 */
void
sl_journal_dump(const char *fn)
{
	int i, ntotal, nmagic, nchksum, nformat, ndump, first = 1;
	uint32_t slot, highest_slot = -1, lowest_slot = -1;
	uint64_t chksum, highest_xid = 0, lowest_xid = 0;
	struct psc_journal_enthdr *pje;
	struct psc_journal_hdr *pjh;
	struct psc_journal *pj;
	struct stat statbuf;
	unsigned char *jbuf;
	ssize_t nb, pjhlen;
	time_t ts;

	ntotal = nmagic = nchksum = nformat = ndump = 0;

	pj = PSCALLOC(sizeof(*pj));

	strlcpy(pj->pj_name, pfl_basename(fn), sizeof(pj->pj_name));

	pj->pj_fd = open(fn, O_RDWR | O_DIRECT);
	if (pj->pj_fd == -1)
		psc_fatal("failed to open journal %s", fn);
	if (fstat(pj->pj_fd, &statbuf) == -1)
		psc_fatal("failed to stat journal %s", fn);

	/*
	 * O_DIRECT may impose alignment restrictions so align the
	 * buffer and perform I/O in multiples of file system block
	 * size.
	 */
	pjhlen = PSC_ALIGN(sizeof(*pjh), statbuf.st_blksize);
	pjh = psc_alloc(pjhlen, PAF_PAGEALIGN);
	nb = pread(pj->pj_fd, pjh, pjhlen, 0);
	if (nb != pjhlen)
		psc_fatal("failed to read journal header");

	pj->pj_hdr = pjh;
	if (pjh->pjh_magic != PJH_MAGIC)
		psc_fatalx("journal header has a bad magic number "
		    "%#"PRIx64, pjh->pjh_magic);

	if (pjh->pjh_version != PJH_VERSION)
		psc_fatalx("journal header has an invalid version "
		    "number %d", pjh->pjh_version);

	psc_crc64_init(&chksum);
	psc_crc64_add(&chksum, pjh, offsetof(struct psc_journal_hdr,
	    pjh_chksum));
	psc_crc64_fini(&chksum);

	if (pjh->pjh_chksum != chksum)
		psc_fatalx("journal header has an invalid checksum "
		    "value %"PSCPRIxCRC64" vs %"PSCPRIxCRC64,
		    pjh->pjh_chksum, chksum);

	if (S_ISREG(statbuf.st_mode) && statbuf.st_size !=
	    (off_t)(pjhlen + pjh->pjh_nents * PJ_PJESZ(pj)))
		psc_fatalx("size of the journal log %"PSCPRIdOFFT"d does "
		    "not match specs in its header", statbuf.st_size);

	if (pjh->pjh_nents % pjh->pjh_readsize)
		psc_fatalx("number of entries %d is not a multiple of the "
		    "readsize %d", pjh->pjh_nents, pjh->pjh_readsize);

	ts = pjh->pjh_timestamp;

	printf("%s:\n"
	    "  version: %u\n"
	    "  entry size: %u\n"
	    "  number of entries: %u\n"
	    "  batch read size: %u\n"
	    "  entry start offset: %"PRId64"\n"
	    "  format time: %s"
	    "  uuid: %"PRIx64"\n"
	    "  %8s %3s %12s %12s  %s\n",
	    fn, pjh->pjh_version, PJ_PJESZ(pj), pjh->pjh_nents,
	    pjh->pjh_readsize, pjh->pjh_start_off,
	    ctime(&ts), pjh->pjh_fsuuid,
	    "idx", "type", "xid", "txg", "details");

	jbuf = psc_alloc(PJ_PJESZ(pj) * pj->pj_hdr->pjh_readsize,
	    PAF_PAGEALIGN);
	for (slot = 0; slot < pjh->pjh_nents;
	    slot += pjh->pjh_readsize) {
		nb = pread(pj->pj_fd, jbuf, PJ_PJESZ(pj) *
		    pjh->pjh_readsize, PJ_GETENTOFF(pj, slot));
		if (nb != PJ_PJESZ(pj) * pjh->pjh_readsize)
			warn("failed to read %d log entries at slot %d",
			    pjh->pjh_readsize, slot);

		for (i = 0; i < pjh->pjh_readsize; i++) {
			ntotal++;
			pje = (void *)&jbuf[PJ_PJESZ(pj) * i];
			if (pje->pje_magic != PJE_MAGIC) {
				nmagic++;
				warnx("journal slot %d has a bad magic"
				    "number", slot + i);
				continue;
			}

			/*
			 * If we hit a new entry that is never used, we
			 * assume that the rest of the journal is never
			 * used.
			 */
			if (pje->pje_type == PJE_FORMAT) {
				nformat = nformat + pjh->pjh_nents -
				    (slot + i);
				goto done;
			}

			psc_crc64_init(&chksum);
			psc_crc64_add(&chksum, pje, offsetof(
			    struct psc_journal_enthdr, pje_chksum));
			psc_crc64_add(&chksum, pje->pje_data,
			    pje->pje_len);
			psc_crc64_fini(&chksum);

			if (pje->pje_chksum != chksum) {
				nchksum++;
				warnx("journal slot %d has a corrupt "
				    "checksum", slot + i);
				goto done;
			}
			ndump++;
			if (verbose)
				sl_journal_dump_entry(slot + i, pje);
			if (first) {
				first = 0;
				highest_xid = lowest_xid = pje->pje_xid;
				highest_slot = lowest_slot = slot + i;
				continue;
			}
			if (highest_xid < pje->pje_xid) {
				highest_xid = pje->pje_xid;
				highest_slot = slot + i;
			}
			if (lowest_xid > pje->pje_xid) {
				lowest_xid = pje->pje_xid;
				lowest_slot = slot + i;
			}
		}

	}

 done:
	if (close(pj->pj_fd) == -1)
		printf("failed closing journal %s", fn);

	psc_free(jbuf, PAF_PAGEALIGN, PJ_PJESZ(pj));
	PSCFREE(pj);

	printf("----------------------------------------------\n"
	    "%8d slot(s) scanned\n"
	    "%8d in use\n"
	    "%8d formatted\n"
	    "%8d bad magic\n"
	    "%8d bad checksum(s)\n"
	    "lowest transaction ID=%#"PRIx64" (slot=%d)\n"
	    "highest transaction ID=%#"PRIx64" (slot=%d)\n",
	    ntotal, ndump, nformat, nmagic, nchksum,
	    lowest_xid, lowest_slot,
	    highest_xid, highest_slot);
}