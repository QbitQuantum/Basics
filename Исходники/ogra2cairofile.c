static int
close_emf(cairo_surface_t *surface)
{
  HDC hdc;
  HENHMETAFILE emf;
  int r;

  hdc = cairo_win32_surface_get_dc(surface);
  cairo_surface_flush(surface);
  cairo_surface_copy_page(surface);
  cairo_surface_finish(surface);

  r = 1;

  EndPage(hdc);
  emf = CloseEnhMetaFile(hdc);
  if (emf == NULL) {
    return 1;
  }
  DeleteEnhMetaFile(emf);
  /* DeleteDC() is called in the cairo library */
  return r;
}