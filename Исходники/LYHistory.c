/*
 * Utility for listing visited links, making any repeated links the most
 * current in the list.  - FM
 */
void LYAddVisitedLink(DocInfo *doc)
{
    VisitedLink *tmp;
    HTList *cur;
    const char *title = (doc->title ? doc->title : NO_TITLE);

    if (isEmpty(doc->address)) {
	PrevVisitedLink = NULL;
	return;
    }

    /*
     * Exclude POST or HEAD replies, and bookmark, menu or list files.  - FM
     */
    if (doc->post_data || doc->isHEAD || doc->bookmark ||
	(			/* special url or a temp file */
	    (!StrNCmp(doc->address, "LYNX", 4) ||
	     !StrNCmp(doc->address, "file://localhost/", 17)))) {
	int related = 1;	/* First approximation only */

	if (LYIsUIPage(doc->address, UIP_HISTORY) ||
	    LYIsUIPage(doc->address, UIP_VLINKS) ||
	    LYIsUIPage(doc->address, UIP_SHOWINFO) ||
	    isLYNXMESSAGES(doc->address) ||
	    ((related = 0) != 0) ||
#ifdef DIRED_SUPPORT
	    LYIsUIPage(doc->address, UIP_DIRED_MENU) ||
	    LYIsUIPage(doc->address, UIP_UPLOAD_OPTIONS) ||
	    LYIsUIPage(doc->address, UIP_PERMIT_OPTIONS) ||
#endif /* DIRED_SUPPORT */
	    LYIsUIPage(doc->address, UIP_PRINT_OPTIONS) ||
	    LYIsUIPage(doc->address, UIP_DOWNLOAD_OPTIONS) ||
	    LYIsUIPage(doc->address, UIP_OPTIONS_MENU) ||
	    isLYNXEDITMAP(doc->address) ||
	    isLYNXKEYMAP(doc->address) ||
	    LYIsUIPage(doc->address, UIP_LIST_PAGE) ||
#ifdef USE_ADDRLIST_PAGE
	    LYIsUIPage(doc->address, UIP_ADDRLIST_PAGE) ||
#endif
	    LYIsUIPage(doc->address, UIP_CONFIG_DEF) ||
	    LYIsUIPage(doc->address, UIP_LYNXCFG) ||
	    isLYNXCOOKIE(doc->address) ||
	    LYIsUIPage(doc->address, UIP_TRACELOG)) {
	    if (!related)
		PrevVisitedLink = NULL;
	    return;
	}
    }

    if (!Visited_Links) {
	Visited_Links = HTList_new();
#ifdef LY_FIND_LEAKS
	atexit(Visited_Links_free);
#endif
	Latest_last.prev_latest = &Latest_first;
	Latest_first.next_latest = &Latest_last;
	Latest_last.next_latest = NULL;		/* Find bugs quick! */
	Latest_first.prev_latest = NULL;
	Last_by_first = Latest_tree = First_tree = NULL;
    }

    cur = Visited_Links;
    while (NULL != (tmp = (VisitedLink *) HTList_nextObject(cur))) {
	if (!strcmp(NonNull(tmp->address),
		    NonNull(doc->address))) {
	    PrevVisitedLink = PrevActiveVisitedLink = tmp;
	    /* Already visited.  Update the last-visited info. */
	    if (tmp->next_latest == &Latest_last)	/* optimization */
		return;

	    /* Remove from "latest" chain */
	    tmp->prev_latest->next_latest = tmp->next_latest;
	    tmp->next_latest->prev_latest = tmp->prev_latest;

	    /* Insert at the end of the "latest" chain */
	    Latest_last.prev_latest->next_latest = tmp;
	    tmp->prev_latest = Latest_last.prev_latest;
	    tmp->next_latest = &Latest_last;
	    Latest_last.prev_latest = tmp;
	    return;
	}
    }

    if ((tmp = typecalloc(VisitedLink)) == NULL)
	outofmem(__FILE__, "LYAddVisitedLink");

    StrAllocCopy(tmp->address, doc->address);
    LYformTitle(&(tmp->title), title);

    /* First-visited chain */
    HTList_appendObject(Visited_Links, tmp);	/* At end */
    tmp->prev_first = Last_by_first;
    Last_by_first = tmp;

    /* Tree structure */
    if (PrevVisitedLink) {
	VisitedLink *a = PrevVisitedLink;
	VisitedLink *b = a->next_tree;
	int l = PrevVisitedLink->level;

	/* Find last on the deeper levels */
	while (b && b->level > l)
	    a = b, b = b->next_tree;

	if (!b)			/* a == Latest_tree */
	    Latest_tree = tmp;
	tmp->next_tree = a->next_tree;
	a->next_tree = tmp;

	tmp->level = PrevVisitedLink->level + 1;
    } else {
	if (Latest_tree)
	    Latest_tree->next_tree = tmp;
	tmp->level = 0;
	tmp->next_tree = NULL;
	Latest_tree = tmp;
    }
    PrevVisitedLink = PrevActiveVisitedLink = tmp;
    if (!First_tree)
	First_tree = tmp;

    /* "latest" chain */
    Latest_last.prev_latest->next_latest = tmp;
    tmp->prev_latest = Latest_last.prev_latest;
    tmp->next_latest = &Latest_last;
    Latest_last.prev_latest = tmp;

    return;
}