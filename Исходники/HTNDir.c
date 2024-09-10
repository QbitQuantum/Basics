/*	HTNewsDir_new
**	----------
**    	Creates a structured stream object and sets up the initial HTML stuff
**	Returns the newsdir object if OK, else NULL
*/
PUBLIC HTNewsDir * HTNewsDir_new (HTRequest * request, const char * title,
				  HTNewsDirKey key, BOOL cache)
{
    HTNewsDir *dir;
    if (!request) return NULL;

    /* Create object */
    if ((dir = (HTNewsDir *) HT_CALLOC(1, sizeof (HTNewsDir))) == NULL)
        HT_OUTOFMEM("HTNewsDir_new");
    dir->target = HTMLGenerator(request, NULL, WWW_HTML,
				HTRequest_outputFormat(request),
				HTRequest_outputStream(request));
    HTAnchor_setFormat(HTRequest_anchor(request), WWW_HTML);
    dir->request = request;
    dir->key = key;
    dir->lastLevel = -1;  /* Added by MP. */

    /*  Get the newsgroup(s) name; added by MP. */
    {
        char* url = HTAnchor_physical(HTRequest_anchor(request));
        char* p = url+strlen(url);
        while (p > url && p[-1] != ':' && p[-1] != '/' && p[-1] != '\\')
            p--;
        StrAllocCopy (dir->name, p);
    }

    if (key != HT_NDK_NONE) {			       /* Thread is unsorted */
	int total = HTNews_maxArticles();
	dir->array = HTArray_new(total > 0 ? total : 128);
    }

    /* If we are asked to prepare a cache entry then create the cache array */
    if (cache) {
	int total = HTNews_maxArticles();
	dir->cache = HTArray_new(total > 0 ? total : 128);
    }

    /* Start the HTML stuff */
    {
	HTStructured *target = dir->target;
	const char *msg = title ? title : "News Listing";
	START(HTML_HTML);
	START(HTML_HEAD);
	START(HTML_TITLE);
	PUTS(msg);
	END(HTML_TITLE);
	END(HTML_HEAD);
	START(HTML_BODY);
	START(HTML_H1);
	PUTS(msg);
	END(HTML_H1);
    }
    return dir;
}