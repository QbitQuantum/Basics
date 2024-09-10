gboolean pharse_search(char *s)
{
  return bsearch(&s, phrase, phraseN, sizeof(char *), qcmp_str) != NULL;
}