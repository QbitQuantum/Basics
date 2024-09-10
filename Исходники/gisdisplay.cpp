void wxGISDisplay::Output(cairo_surface_t *pSurface, wxDC* pDC)
{
    cairo_t *cr = CreateContext(pDC);
    if(cr == NULL)
        return;

	cairo_set_source_surface (cr, pSurface, 0, 0);
	cairo_paint (cr);

//#ifdef __WXMSW__
    cairo_destroy (cr);
//#endif
}