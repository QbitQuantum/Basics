static void
run (int format, gboolean alpha)
{
  guint8 data[2000] = { 0, };
  guint8 compressed[2000] = { 0, };
  gsize len; 
  gulong clen;
  int ret;
  char *s;

  switch (format) {
    case 3:
      len = create_palletized (data, alpha);
      g_print ("%u\n", len);
      break;
    default:
      g_assert_not_reached ();
      return;
  }
  
  if (alpha) {
    clen = sizeof (compressed);
    ret = compress2 (compressed, &clen, data, len, 9);
  } else {
    clen = sizeof (compressed) - 1;
    ret = compress2 (compressed + 1, &clen, data + 1, len - 1, 9);
    compressed[0] = data[0];
  }
  g_assert (ret == Z_OK);

  s = g_base64_encode (compressed, clen + 1);
  g_print ("%s\n\n", s);
  g_free (s);
}