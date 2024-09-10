int websUrlHandlerRequest(webs_t wp)
{
	websUrlHandlerType	*sp;
	int					i, first;

	a_assert(websValid(wp));

/*
 *	Delete the socket handler as we don't want to start reading any
 *	data on the connection as it may be for the next pipelined HTTP/1.1
 *	request if using Keep Alive
 */
	socketDeleteHandler(wp->sid);
	wp->state = WEBS_PROCESSING;
	websStats.handlerHits++;
	
	websSetRequestPath(wp, websGetDefaultDir(), NULL);

/*
 *	Eliminate security hole
 */
 	websCondenseMultipleChars(wp->path, '/');
	websCondenseMultipleChars(wp->url, '/');

	/* Fix by Luigi Auriemma 19 Jan 2004 */
	/* http://aluigi.altervista.org/adv/goahead-adv2.txt */
	if ((wp->path[0] != '/') || strchr(wp->path, '\\')) {
		websError(wp, 400, T("Bad request"));
		return 0;
	}

/*
 *	We loop over each handler in order till one accepts the request. 
 *	The security handler will handle the request if access is NOT allowed.
 */
	first = 1;
	for (i = 0; i < websUrlHandlerMax; i++) {
		sp = &websUrlHandler[i];
		if (sp->handler && gstrncmp(sp->urlPrefix, wp->path, sp->len) == 0) {
			if (first) {
				websSetEnv(wp);
				first = 0;
			}
			if ((*sp->handler)(wp, sp->urlPrefix, sp->webDir, sp->arg, 
					wp->url, wp->path, wp->query)) {
				return 1;
			}
			if (!websValid(wp)) {
				trace(0, 
				T("webs: handler %s called websDone, but didn't return 1\n"),
					sp->urlPrefix);
				return 1;
			}
		}
	}
/*
 *	If no handler processed the request, then return an error. Note: It is 
 *	the handlers responsibility to call websDone
 */
	if (i >= websUrlHandlerMax) {
      /*
       * 13 Mar 03 BgP
       * preventing a cross-site scripting exploit
		websError(wp, 200, T("No handler for this URL %s"), wp->url);
       */
		websError(wp, 200, T("No handler for this URL"));
	}
	return 0;
}