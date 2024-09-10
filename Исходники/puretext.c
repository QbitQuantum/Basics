static pt_subst_t *get_nth_word_utf8(char *text, int idx) {
  // get nth word, return start (bytes) and length (bytes)
  // idx==0 for first word, etc

  register size_t toffs=0,xtoffs;
  gboolean isaspace=TRUE;

  pt_subst_t *subst=(pt_subst_t *)weed_malloc(sizeof(pt_subst_t));
  subst->start=0;

  while (text[toffs]!='\0') {
    wchar_t pwc;
    xtoffs=mbtowc(&pwc,&text[toffs],4);
    if (iswspace(pwc)) {
      if (idx==-1) {
        subst->length=toffs-subst->start;
        return subst;
      }
      isaspace=TRUE;
    } else if (isaspace) {
      if (--idx==-1) subst->start=toffs;
      isaspace=FALSE;
    }
    toffs+=xtoffs;
  }

  subst->length=toffs-subst->start;
  return subst;
}