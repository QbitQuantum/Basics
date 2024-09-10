static int tgetInit(rpmtget tget, size_t nbuf)
{
    int rc;
    int xx;

    if (_rpmsw_stats) {
	tget->sop = xcalloc(1, sizeof(*tget->sop));
	tget->gop = xcalloc(1, sizeof(*tget->gop));
    }

fprintf(stderr, "===== %s\n", tget->uri);
    xx = rpmswEnter(tget->sop, 0);
    rc = Stat(tget->uri, &tget->sb);
    xx = rpmswExit(tget->sop, 1);
    if (rc < 0)
	goto exit;

    printStat(tget);

    if (nbuf == 0 && tget->sb.st_size > 0)
	nbuf = tget->sb.st_size;

    tget->fd = Fopen(tget->uri, "r.ufdio");
    if (tget->fd == NULL || Ferror(tget->fd)) {
	rc = -1;
	goto exit;
    }
    tget->nbuf = nbuf;
    tget->buf = xmalloc(tget->nbuf + 2);
    tget->buf[0] = '\0';

    tget->b = NULL;
    tget->nb = 0;

    rc = 0;

exit:
    if (rc)
	(void) tgetFini(tget);
    return rc;
}