/* Returns the width of string S when output in font FONT. */
int
bogl_metrics (const char *s, int n, const struct bogl_font *font)
{
  int cx = 0;
  wchar_t wc;
  int k;

  mbtowc (0, 0, 0);
  for (; (k = mbtowc (&wc, s, n)) > 0; s += k, n -= k)
    cx += bogl_font_glyph (font, wc, NULL);
  return cx;
}