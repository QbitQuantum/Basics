/*
 * Taken and adapted from R 3.2.2 src/main/gram.c@4915
 */
int ALIKEC_is_valid_name(const char *name)
{
  const char *p = name;
  int i;

  if(mbcslocale) {
    /* the only way to establish which chars are alpha etc is to
       use the wchar variants */
    size_t n = strlen(name), used;
    wchar_t wc;
    used = Mbrtowc(&wc, p, n, NULL);
    if((int) used <= 0) return 0;
    p += used; n -= used;
    if (wc != L'.' && !iswalpha(wc) ) return 0;
    if (wc == L'.') {
      /* We don't care about other than ASCII digits */
      if(isdigit(0xff & (int)*p)) return 0;
      /* Mbrtowc(&wc, p, n, NULL); if(iswdigit(wc)) return 0; */
    }
    while((int)(used = Mbrtowc(&wc, p, n, NULL)) > 0) {
      if (!(iswalnum(wc) || wc == L'.' || wc == L'_')) break;
      p += used; n -= used;
    }
    if (*p != '\0') return 0;
  } else {
    // nocov start current local has MB_CUR_MAX > 1, so this never runs
    int c = 0xff & *p++;
    if (c != '.' && !isalpha(c) ) return 0;
    if (c == '.' && isdigit(0xff & (int)*p)) return 0;
    while ( c = 0xff & *p++, (isalnum(c) || c == '.' || c == '_') ) ;
    if (c != '\0') return 0;
    // nocov end
  }

  if (strcmp(name, "...") == 0) return 1;

  const char * keywords[20] = {
    "NULL", "NA", "TRUE", "FALSE", "Inf", "NaN", "NA_integer_", "NA_real_",
    "NA_character_", "NA_complex_", "function", "while", "repeat", "for",
    "if", "in", "else", "next", "break", "..."
  };
  for (i = 0; i < 20; i++)
    if (strcmp(keywords[i], name) == 0) return 0;

  return 1;
}