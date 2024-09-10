WMcursor *WIN_CreateWMCursor(_THIS,
		Uint8 *data, Uint8 *mask, int w, int h, int hot_x, int hot_y)
{
#ifdef USE_STATIC_CURSOR
	WMcursor *cursor;

	/* Allocate the cursor */
	cursor = (WMcursor *)SDL_malloc(sizeof(*cursor));
	if ( cursor ) {
		cursor->curs = LoadCursor(NULL, IDC_ARROW);
	}
	return(cursor);
#else
	WMcursor *cursor;
	int allowed_x;
	int allowed_y;
	int run, pad, i;
	Uint8 *aptr, *xptr;

	/* Check to make sure the cursor size is okay */
	allowed_x = GetSystemMetrics(SM_CXCURSOR);
	allowed_y = GetSystemMetrics(SM_CYCURSOR);
	if ( (w > allowed_x) || (h > allowed_y) ) {
		SDL_SetError("Only cursors of dimension (%dx%d) are allowed",
							allowed_x, allowed_y);
		return(NULL);
	}

	/* Allocate the cursor */
	cursor = (WMcursor *)SDL_malloc(sizeof(*cursor));
	if ( cursor == NULL ) {
		SDL_SetError("Out of memory");
		return(NULL);
	}
	cursor->curs = NULL;
	cursor->ands = NULL;
	cursor->xors = NULL;

	/* Pad out to the normal cursor size */
	run = PAD_BITS(w);
	pad = PAD_BITS(allowed_x)-run;
	aptr = cursor->ands = (Uint8 *)SDL_malloc((run+pad)*allowed_y);
	xptr = cursor->xors = (Uint8 *)SDL_malloc((run+pad)*allowed_y);
	if ( (aptr == NULL) || (xptr == NULL) ) {
		WIN_FreeWMCursor(NULL, cursor);
		SDL_OutOfMemory();
		return(NULL);
	}
	for ( i=0; i<h; ++i ) {
		memxor(xptr, data, mask, run);
		xptr += run;
		data += run;
		memnot(aptr, mask, run);
		mask += run;
		aptr += run;
		SDL_memset(xptr,  0, pad);
		xptr += pad;
		SDL_memset(aptr, ~0, pad);
		aptr += pad;
	}
	pad += run;
	for ( ; i<allowed_y; ++i ) {
		SDL_memset(xptr,  0, pad);
		xptr += pad;
		SDL_memset(aptr, ~0, pad);
		aptr += pad;
	}

	/* Create the cursor */
	cursor->curs = CreateCursor(
			(HINSTANCE)GetWindowLongPtr(SDL_Window, GWLP_HINSTANCE),
					hot_x, hot_y, allowed_x, allowed_y, 
						cursor->ands, cursor->xors);
	if ( cursor->curs == NULL ) {
		WIN_FreeWMCursor(NULL, cursor);
		SDL_SetError("Windows couldn't create the requested cursor");
		return(NULL);
	}
	return(cursor);
#endif /* USE_STATIC_CURSOR */
}