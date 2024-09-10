/**
 * cairo_win32_surface_get_image:
 * @surface: a #cairo_surface_t
 *
 * Returns a #cairo_surface_t image surface that refers to the same bits
 * as the DIB of the Win32 surface.  If the passed-in win32 surface
 * is not a DIB surface, %NULL is returned.
 *
 * Return value: a #cairo_surface_t (owned by the win32 #cairo_surface_t),
 * or %NULL if the win32 surface is not a DIB.
 *
 * Since: 1.4
 **/
cairo_surface_t *
cairo_win32_surface_get_image (cairo_surface_t *surface)
{

    if (! _cairo_surface_is_win32 (surface)) {
        return _cairo_surface_create_in_error (_cairo_error (CAIRO_STATUS_SURFACE_TYPE_MISMATCH));
    }

    GdiFlush();
    return to_win32_display_surface(surface)->image;
}