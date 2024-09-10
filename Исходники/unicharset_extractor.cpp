// Set character properties using wctype if we have it.
// Contributed by [email protected].
// Modified by Ray to use UNICHAR for unicode conversion
// and to check for wctype using autoconf/presence of windows.
void set_properties(UNICHARSET *unicharset, const char* const c_string) {
#ifdef USING_WCTYPE
  UNICHAR_ID id;
  int wc;

  // Convert the string to a unichar id.
  id = unicharset->unichar_to_id(c_string);

  // Set the other_case property to be this unichar id by default.
  unicharset->set_other_case(id, id);

  int step = UNICHAR::utf8_step(c_string);
  if (step == 0)
    return; // Invalid utf-8.

  // Get the next Unicode code point in the string.
  UNICHAR ch(c_string, step);
  wc = ch.first_uni();

  /* Copy the properties. */
  if (iswalpha(wc)) {
    unicharset->set_isalpha(id, 1);
    if (iswlower(wc)) {
      unicharset->set_islower(id, 1);
      unicharset->set_other_case(id, wc_to_unichar_id(*unicharset,
                                                      towupper(wc)));
    }
    if (iswupper(wc)) {
      unicharset->set_isupper(id, 1);
      unicharset->set_other_case(id, wc_to_unichar_id(*unicharset,
                                                      towlower(wc)));
    }
  }
  if (iswdigit(wc))
    unicharset->set_isdigit(id, 1);
  if(iswpunct(wc))
    unicharset->set_ispunctuation(id, 1);

#endif
}