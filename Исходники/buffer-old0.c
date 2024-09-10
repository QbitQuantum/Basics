int buf_ctor(struct buf_s *buf, size_t bsiz, size_t rblk, size_t wblk, int rline, int wline, size_t hpage, size_t ioar, size_t ioaw)
{
	int ret = -1;
	size_t adj, page, idx, rblki, wblki, bsiza, csiza;

	if (!buf) {
		fputs("buf: no buf ?\n", stderr);
		return -1;
	}

	if (bsiz < 2*rblk || bsiz < 2*wblk) {
		fputs("buf: 'buffer size' must be at least 2*max('read block, 'write block'),\n"
		      "     to avoid corner case starvations.\n", stderr);
		return -1;
	}
	memset(buf, 0, sizeof *buf);

#ifndef h_mingw
	page = sysconf(_SC_PAGESIZE);
	if (page == hpage) {
		hpage = 0;
	}
	page = hpage ? hpage : page;
	adj = MAX(page, SHMLBA);
#else
	hpage = 0;
	adj = page = 4096;
#endif

	bsiza = ALIGN(bsiz, adj);
	if (!(idx = is_pow2(bsiza))) {
		fprintf(stderr, "buf: 'aligned buffer size' must be power of 2, but is: 0x%zX\n", bsiza);
		goto out;
	}
	buf->mask = (((size_t)1 << idx) - 1);
	rblki = ALIGN(rblk, ioar);
	wblki = ALIGN(wblk, ioaw);
	csiza = ALIGN(rblki + wblki, adj);
	buf->size = bsiza;

	preset_shm(buf);
	if (setup_shm(buf, bsiza, csiza, hpage) < 0) {
		fputs("buf: falling back to regular malloc()\n", stderr);
		ret = 1;
		detach_shm(buf);
		rm_shm(buf);
		preset_mal(buf);
		if (setup_mal(buf, bsiza, csiza, adj) < 0) {
			detach_mal(buf);
			ret = -1;
			goto out;
		}
	} else
		ret = 0;

	buf->rchunk = buf->chk;
	buf->wchunk = buf->chk + rblki;

	buf->flags |= hpage && buf->mapW ? M_HUGE : 0;
	buf->flags |= rline ? M_LINER : 0;
	buf->flags |= wline ? M_LINEW : 0;
//	buf->page = page;
	buf->ioar = ioar;
	buf->ioaw = ioaw;
	buf->rblk = rblk;
	buf->wblk = wblk;
	buf->crcw = crc_beg();
	buf->crcr = buf->crcw;
#if 0
	if (rblk < wblk && rline && !wline) {
		fputs("buf: 'read block' must be greater or equal to 'write block',\n"
		      "     if the left side is in the line mode,\n"
		      "     and the right side is in the reblocking mode.\n", stderr);
		goto out;
	}
#endif

	DEB("\nbuf map: C:%p, B:%p, B+S:%p, W:%p\n", buf->mapC, buf->mapB, buf->mapB + buf->size, buf->mapW);
	DEB("buf buf: C:%p, B:%p\n", buf->chk, buf->buf);
out:
	if (ret < 0)
		buf_dtor(buf);
	fputc('\n', stderr);
	return ret;
}