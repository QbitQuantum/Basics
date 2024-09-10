static cairo_int_status_t
_cairo_win32_save_initial_clip (HDC hdc, cairo_win32_display_surface_t *surface)
{
    RECT rect;
    int clipBoxType;
    int gm;
    XFORM saved_xform;

    /* GetClipBox/GetClipRgn and friends interact badly with a world transform
     * set.  GetClipBox returns values in logical (transformed) coordinates;
     * it's unclear what GetClipRgn returns, because the region is empty in the
     * case of a SIMPLEREGION clip, but I assume device (untransformed) coordinates.
     * Similarly, IntersectClipRect works in logical units, whereas SelectClipRgn
     * works in device units.
     *
     * So, avoid the whole mess and get rid of the world transform
     * while we store our initial data and when we restore initial coordinates.
     *
     * XXX we may need to modify x/y by the ViewportOrg or WindowOrg
     * here in GM_COMPATIBLE; unclear.
     */
    gm = GetGraphicsMode (hdc);
    if (gm == GM_ADVANCED) {
	GetWorldTransform (hdc, &saved_xform);
	ModifyWorldTransform (hdc, NULL, MWT_IDENTITY);
    }

    clipBoxType = GetClipBox (hdc, &rect);
    if (clipBoxType == ERROR) {
	_cairo_win32_print_gdi_error (__FUNCTION__);
	SetGraphicsMode (hdc, gm);
	/* XXX: Can we make a more reasonable guess at the error cause here? */
	return _cairo_error (CAIRO_STATUS_DEVICE_ERROR);
    }

    surface->win32.extents.x = rect.left;
    surface->win32.extents.y = rect.top;
    surface->win32.extents.width = rect.right - rect.left;
    surface->win32.extents.height = rect.bottom - rect.top;

    surface->initial_clip_rgn = NULL;
    surface->had_simple_clip = FALSE;

    if (clipBoxType == COMPLEXREGION) {
	surface->initial_clip_rgn = CreateRectRgn (0, 0, 0, 0);
	if (GetClipRgn (hdc, surface->initial_clip_rgn) <= 0) {
	    DeleteObject(surface->initial_clip_rgn);
	    surface->initial_clip_rgn = NULL;
	}
    } else if (clipBoxType == SIMPLEREGION) {
	surface->had_simple_clip = TRUE;
    }

    if (gm == GM_ADVANCED)
	SetWorldTransform (hdc, &saved_xform);

    return CAIRO_STATUS_SUCCESS;
}