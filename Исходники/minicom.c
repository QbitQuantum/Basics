/*
 * fmg 8/20/97
 * drawhist_look()
 * Redraw the window, highlight line that was found to contain
 * pattern 'look'
 * Needed by re-draw screen function after EACH find_next()
 */
void drawhist_look(WIN *w, int y, int r, wchar_t *look, int case_matters)
{
  int f;
  ELM *tmp_e;
  wchar_t tmp_line[MAXCOLS];

  tmp_line[0]='\0';
  w->direct = 0;
  for (f = 0; f < w->ys; f++) {
    tmp_e = mc_getline(w, y++);

    /* First we "accumulate" the line into a variable */
    mc_wdrawelm_var(w, tmp_e, tmp_line);

    /* Does it have what we want? */
    if (wcslen(look) > 1 && wcslen(tmp_line) > 1) {
      if (StrStr(tmp_line,look, case_matters))
        mc_wdrawelm_inverse(w, f, tmp_e); /* 'inverse' it */
      else
        mc_wdrawelm(w, f, tmp_e); /* 'normal' output */
    }
  }

  if (r)
    mc_wredraw(w, 1);
  w->direct = 1;
}