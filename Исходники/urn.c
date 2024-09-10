void
urnStart(request_t * r, StoreEntry * e)
{
    LOCAL_ARRAY(char, urlres, 4096);
    request_t *urlres_r = NULL;
    const char *t;
    char *host;
    UrnState *urnState;
    StoreEntry *urlres_e;
    ErrorState *err;
    debug(52, 3) ("urnStart: '%s'\n", storeUrl(e));
    CBDATA_INIT_TYPE(UrnState);
    urnState = cbdataAlloc(UrnState);
    urnState->entry = e;
    urnState->request = requestLink(r);
    storeLockObject(urnState->entry);
    if (strncasecmp(strBuf(r->urlpath), "menu.", 5) == 0) {
	char *new_path = xstrdup(strBuf(r->urlpath) + 5);
	urnState->flags.force_menu = 1;
	stringReset(&r->urlpath, new_path);
	xfree(new_path);
    }
    if ((t = strChr(r->urlpath, ':')) != NULL) {
	strSet(r->urlpath, t, '\0');
	host = xstrdup(strBuf(r->urlpath));
	strSet(r->urlpath, t, ':');
    } else {
	host = xstrdup(strBuf(r->urlpath));
    }
    snprintf(urlres, 4096, "http://%s/uri-res/N2L?urn:%s", host, strBuf(r->urlpath));
    safe_free(host);
    urlres_r = urlParse(METHOD_GET, urlres);
    if (urlres_r == NULL) {
	debug(52, 3) ("urnStart: Bad uri-res URL %s\n", urlres);
	err = errorCon(ERR_URN_RESOLVE, HTTP_NOT_FOUND);
	err->url = xstrdup(urlres);
	errorAppendEntry(e, err);
	return;
    }
    httpHeaderPutStr(&urlres_r->header, HDR_ACCEPT, "text/plain");
    if ((urlres_e = storeGetPublic(urlres, METHOD_GET)) == NULL) {
	urlres_e = storeCreateEntry(urlres, urlres, null_request_flags, METHOD_GET);
	urnState->sc = storeClientListAdd(urlres_e, urnState);
	fwdStart(-1, urlres_e, urlres_r);
    } else {
	storeLockObject(urlres_e);
	urnState->sc = storeClientListAdd(urlres_e, urnState);
    }
    urnState->urlres_e = urlres_e;
    urnState->urlres_r = requestLink(urlres_r);
    storeClientCopy(urnState->sc, urlres_e,
	0,
	0,
	4096,
	memAllocate(MEM_4K_BUF),
	urnHandleReply,
	urnState);
}