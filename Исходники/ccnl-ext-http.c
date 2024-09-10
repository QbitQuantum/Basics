int
ccnl_http_status(struct ccnl_relay_s *ccnl, struct ccnl_http_s *http)
{
    static char txt[64000];
    char *hdr =
	"HTTP/1.1 200 OK\n\r"
	"Content-Type: text/html; charset=utf-8\n\r"
        "Connection: close\n\r\n\r", *cp;
    int len = strlen(hdr), i, j, cnt;
    time_t t;
    struct utsname uts;
    struct ccnl_face_s *f;
    struct ccnl_forward_s *fwd;
    struct ccnl_interest_s *ipt;
    struct ccnl_buf_s *bpt;

    strcpy(txt, hdr);
    len += sprintf(txt+len,
		   "<html><head><title>ccn-lite-relay status</title>\n"
		   "<style type=\"text/css\">\n"
		   "body {font-family: sans-serif;}\n"
		   "</style>\n"
		   "</head><body>\n");
    len += sprintf(txt+len, "\n<table borders=0>\n<tr><td>"
		   "<a href=\"\">[refresh]</a>&nbsp;&nbsp;<td>"
		   "ccn-lite-relay Status Page &nbsp;&nbsp;");
    uname(&uts);
    len += sprintf(txt+len, "node <strong>%s (%d)</strong>\n",
		   uts.nodename, getpid());
    t = time(NULL);
    cp = ctime(&t);
    cp[strlen(cp)-1] = 0;
    len += sprintf(txt+len, "<tr><td><td><font size=-1>%s &nbsp;&nbsp;", cp);
    cp = ctime(&ccnl->startup_time);
    cp[strlen(cp)-1] = 0;
    len += sprintf(txt+len, " (started %s)</font>\n</table>\n", cp);

    len += sprintf(txt+len, "\n<p><table borders=0 width=100%% bgcolor=#e0e0ff>"
		   "<tr><td><em>Forwarding Table</em></table><ul>\n");
    for (fwd = ccnl->fib, cnt = 0; fwd; fwd = fwd->next, cnt++);
    if (cnt > 0) {
	struct ccnl_forward_s **fwda;
	fwda = (struct ccnl_forward_s**) ccnl_malloc(cnt * sizeof(fwd));
	for (fwd = ccnl->fib, i = 0; fwd; fwd = fwd->next, i++)
	    fwda[i] = fwd;
	qsort(fwda, cnt, sizeof(fwd), ccnl_cmpfib);
	for (i = 0; i < cnt; i++) {
	    char fname[10];
	    sprintf(fname, "f%d", fwda[i]->face->faceid);
	    len += sprintf(txt+len,
			   "<li>via %4s: <font face=courier>%s</font>\n",
			   fname, ccnl_prefix_to_path(fwda[i]->prefix));
	}
	ccnl_free(fwda);
    }
    len += sprintf(txt+len, "</ul>\n");

    len += sprintf(txt+len, "\n<p><table borders=0 width=100%% bgcolor=#e0e0ff>"
		   "<tr><td><em>Faces</em></table><ul>\n");
    for (f = ccnl->faces, cnt = 0; f; f = f->next, cnt++);
    if (cnt > 0) {
	struct ccnl_face_s **fa;
	fa = (struct ccnl_face_s**) ccnl_malloc(cnt * sizeof(f));
	for (f = ccnl->faces, i = 0; f; f = f->next, i++)
	    fa[i] = f;
	qsort(fa, cnt, sizeof(f), ccnl_cmpfaceid);
	for (i = 0; i < cnt; i++) {
	    len += sprintf(txt+len,
			   "<li><strong>f%d</strong> (via i%d) &nbsp;"
			   "peer=<font face=courier>%s</font> &nbsp;ttl=",
			   fa[i]->faceid, fa[i]->ifndx,
			   ccnl_addr2ascii(&(fa[i]->peer)));
	    if (fa[i]->flags & CCNL_FACE_FLAGS_STATIC)
		len += sprintf(txt+len, "static");
	    else
		len += sprintf(txt+len, "%.1fsec",
			fa[i]->last_used + CCNL_FACE_TIMEOUT - CCNL_NOW());
	    for (j = 0, bpt = fa[i]->outq; bpt; bpt = bpt->next, j++);
	    len += sprintf(txt+len, " &nbsp;qlen=%d\n", j);
	}
	ccnl_free(fa);
    }
    len += sprintf(txt+len, "</ul>\n");

    len += sprintf(txt+len, "\n<p><table borders=0 width=100%% bgcolor=#e0e0ff>"
		   "<tr><td><em>Interfaces</em></table><ul>\n");
    for (i = 0; i < ccnl->ifcount; i++) {
	len += sprintf(txt+len, "<li><strong>i%d</strong>&nbsp;&nbsp;"
		       "addr=<font face=courier>%s</font>&nbsp;&nbsp;"
		       "qlen=%d/%d\n",
		       i, ccnl_addr2ascii(&ccnl->ifs[i].addr),
		       ccnl->ifs[i].qlen, CCNL_MAX_IF_QLEN);
    }
    len += sprintf(txt+len, "</ul>\n");

    len += sprintf(txt+len, "\n<p><table borders=0 width=100%% bgcolor=#e0e0ff>"
		   "<tr><td><em>Misc stats</em></table><ul>\n");
    for (cnt = 0, bpt = ccnl->nonces; bpt; bpt = bpt->next, cnt++);
    len += sprintf(txt+len, "<li>Nonces: %d\n", cnt);
    for (cnt = 0, ipt = ccnl->pit; ipt; ipt = ipt->next, cnt++);
    len += sprintf(txt+len, "<li>Pending interests: %d\n", cnt);
    len += sprintf(txt+len, "<li>Content chunks: %d (max=%d)\n",
		   ccnl->contentcnt, ccnl->max_cache_entries);
    len += sprintf(txt+len, "</ul>\n");

    len += sprintf(txt+len, "\n<p><table borders=0 width=100%% bgcolor=#e0e0ff>"
		   "<tr><td><em>Config</em></table><table borders=0>\n");
    len += sprintf(txt+len, "<tr><td>content.timeout:"
		   "<td align=right> %d<td>\n", CCNL_CONTENT_TIMEOUT);
    len += sprintf(txt+len, "<tr><td>face.timeout:"
		   "<td align=right> %d<td>\n", CCNL_FACE_TIMEOUT);
    len += sprintf(txt+len, "<tr><td>interest.maxretransmit:"
		   "<td align=right> %d<td>\n", CCNL_MAX_INTEREST_RETRANSMIT);
    len += sprintf(txt+len, "<tr><td>interest.timeout:"
		   "<td align=right> %d<td>\n", CCNL_INTEREST_TIMEOUT);
    len += sprintf(txt+len, "<tr><td>nonces.max:"
		   "<td align=right> %d<td>\n", CCNL_MAX_NONCES);

    len += sprintf(txt+len, "<tr><td>compile.featureset:<td><td>");
#ifdef USE_DEBUG
    len +=  sprintf(txt+len, " DEBUG");
#endif
#ifdef USE_DEBUG_MALLOC
    len +=  sprintf(txt+len, " DEBUG_MALLOC");
#endif
#ifdef USE_FRAG
    len +=  sprintf(txt+len, " FRAGS");
#endif
#ifdef USE_ETHERNET
    len +=  sprintf(txt+len, " ETHERNET");
#endif
#ifdef USE_HTTP_STATUS
    len +=  sprintf(txt+len, " HTTP_STATUS");
#endif
#ifdef USE_MGMT
    len +=  sprintf(txt+len, " MGMT");
#endif
#ifdef USE_SCHEDULER
    len +=  sprintf(txt+len, " SCHEDULER");
#endif
#ifdef USE_UNIXSOCKET
    len +=  sprintf(txt+len, " UNIXSOCKET");
#endif
    len +=  sprintf(txt+len, "\n");
    len += sprintf(txt+len, "<tr><td>compile.time:"
		   "<td><td>%s %s\n", __DATE__, __TIME__);
    len += sprintf(txt+len, "<tr><td>compile.ccnl_core_version:"
		   "<td><td>%s\n", CCNL_VERSION);
    len += sprintf(txt+len, "</table>\n");

    len += sprintf(txt+len, "\n<p><hr></body></html>\n");

    http->out = (unsigned char*) txt;
    http->outoffs = 0;
    http->outlen = len;

    return 0;
}