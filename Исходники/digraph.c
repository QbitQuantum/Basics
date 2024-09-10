/// ":loadkeymap" command: load the following lines as the keymap.
///
/// @param eap
void ex_loadkeymap(exarg_T *eap)
{
  char_u *line;
  char_u *p;
  char_u *s;

#define KMAP_LLEN 200  // max length of "to" and "from" together
  char_u buf[KMAP_LLEN + 11];
  char_u *save_cpo = p_cpo;

  if (!getline_equal(eap->getline, eap->cookie, getsourceline)) {
    EMSG(_("E105: Using :loadkeymap not in a sourced file"));
    return;
  }

  // Stop any active keymap and clear the table.
  keymap_unload();

  curbuf->b_kmap_state = 0;
  ga_init(&curbuf->b_kmap_ga, (int)sizeof(kmap_T), 20);

  // Set 'cpoptions' to "C" to avoid line continuation.
  p_cpo = (char_u *)"C";

  // Get each line of the sourced file, break at the end.
  for (;;) {
    line = eap->getline(0, eap->cookie, 0);

    if (line == NULL) {
      break;
    }

    p = skipwhite(line);

    if ((*p != '"') && (*p != NUL)) {
      kmap_T *kp = GA_APPEND_VIA_PTR(kmap_T, &curbuf->b_kmap_ga);
      s = skiptowhite(p);
      kp->from = vim_strnsave(p, (size_t)(s - p));
      p = skipwhite(s);
      s = skiptowhite(p);
      kp->to = vim_strnsave(p, (size_t)(s - p));

      if ((STRLEN(kp->from) + STRLEN(kp->to) >= KMAP_LLEN)
          || (*kp->from == NUL)
          || (*kp->to == NUL)) {
        if (*kp->to == NUL) {
          EMSG(_("E791: Empty keymap entry"));
        }
        xfree(kp->from);
        xfree(kp->to);
        --curbuf->b_kmap_ga.ga_len;
      }
    }
    xfree(line);
  }

  // setup ":lnoremap" to map the keys
  for (int i = 0; i < curbuf->b_kmap_ga.ga_len; ++i) {
    vim_snprintf((char *)buf, sizeof(buf), "<buffer> %s %s",
                 ((kmap_T *)curbuf->b_kmap_ga.ga_data)[i].from,
                 ((kmap_T *)curbuf->b_kmap_ga.ga_data)[i].to);
    (void)do_map(2, buf, LANGMAP, FALSE);
  }

  p_cpo = save_cpo;

  curbuf->b_kmap_state |= KEYMAP_LOADED;
  status_redraw_curbuf();
}