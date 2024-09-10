static void bs1770gain_print_label(const char *label, int width, FILE *f)
{
#if defined (W_WIN32) // [
  wchar_t *wlabel;

  if (NULL==(wlabel=pbu_s2w(label))) {
    DMESSAGE("converting UTF-8 to UTF-16");
    goto wlabel;
  }
#endif // ]

  width+=6;

#if defined (W_WIN32) // [
  for (width-=wcslen(wlabel);0<width;--width)
    fputwc(L' ',f);
#else // ] [
  for (width-=strlen(label);0<width;--width)
    fputc(' ',f);
#endif // ]

#if defined (W_WIN32) // [
  fwprintf(f,L"%s:  ",wlabel);
#else // ] [
  fprintf(f,"%s:  ",label);
#endif // ]

#if defined (W_WIN32) // [
  free(wlabel);
wlabel:
  return;
#endif // ]
}