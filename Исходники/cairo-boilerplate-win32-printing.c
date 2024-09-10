static cairo_surface_t *
_cairo_boilerplate_win32_printing_create_surface (const char		    *name,
						  cairo_content_t	     content,
						  double		     width,
						  double		     height,
						  double		     max_width,
						  double		     max_height,
						  cairo_boilerplate_mode_t   mode,
						  void			   **closure)
{
    win32_target_closure_t *ptc;
    cairo_surface_t *surface;
    DOCINFO di;

    if (content == CAIRO_TEST_CONTENT_COLOR_ALPHA_FLATTENED)
	content = CAIRO_CONTENT_COLOR_ALPHA;

    *closure = ptc = xmalloc (sizeof (win32_target_closure_t));

    xasprintf (&ptc->filename, "%s.out.ps", name);
    xunlink (ptc->filename);

    memset (&di, 0, sizeof (DOCINFO));
    di.cbSize = sizeof (DOCINFO);
    di.lpszDocName = ptc->filename;
    di.lpszOutput = ptc->filename;

    ptc->width = width;
    ptc->height = height;

    create_printer_dc (ptc);
    if (ptc->dc == NULL) {
	printf("\nFailed to create printer\n");
	free (ptc->filename);
	free (ptc);
	return NULL;
    }
    StartDoc (ptc->dc, &di);
    StartPage (ptc->dc);
    surface = cairo_win32_printing_surface_create (ptc->dc);
    if (cairo_surface_status (surface)) {
	free (ptc->filename);
	free (ptc);
	return NULL;
    }
    cairo_surface_set_fallback_resolution (surface, 72., 72.);

    if (content == CAIRO_CONTENT_COLOR) {
	ptc->target = surface;
	surface = cairo_surface_create_similar (ptc->target,
						CAIRO_CONTENT_COLOR,
						width, height);
    } else {
	ptc->target = NULL;
    }

    if (cairo_surface_set_user_data (surface,
				     &win32_closure_key,
				     ptc,
				     NULL) != CAIRO_STATUS_SUCCESS) {
	cairo_surface_destroy (surface);
	if (ptc->target != NULL)
	    cairo_surface_destroy (ptc->target);
	free (ptc->filename);
	free (ptc);
	return NULL;
    }

    return surface;
}