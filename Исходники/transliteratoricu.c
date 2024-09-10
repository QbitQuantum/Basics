static gchar *
transliterator_icu_real_transliterate (TranslitTransliterator *self,
                                       const gchar            *input,
                                       guint                  *endpos,
                                       GError                **error)
{
  TransliteratorIcu *icu = TRANSLITERATOR_ICU (self);
  gchar *output;
  gint n_filtered = 0;
  UChar *ustr;
  int32_t ustrLength, ustrCapacity, limit;
  int32_t inputUstrLength;
  UErrorCode errorCode;

  ustr = ustring_from_utf8 (input, &ustrLength);
  inputUstrLength = ustrLength;
  limit = ustrLength;
  ustrCapacity = ustrLength + 1;

  do
    {
      errorCode = 0;

      /* We can't use utrans_transIncrementalUChars here, since the
       * output is sometimes unacceptable.
       *
       * For example, with the "Latin-Katakana" transliterator,
       * "kakikukeko" does not turn into Japanese characters until one
       * more vovel character follows.
       */
      utrans_transUChars (icu->trans,
			  ustr, &ustrLength, ustrCapacity,
			  0, &limit,
			  &errorCode);
      if (errorCode == U_BUFFER_OVERFLOW_ERROR)
	{
	  ustrCapacity = ustrLength + 1;
	  ustr = g_realloc (ustr, ustrCapacity);
	  ustrLength = inputUstrLength;
	  limit = inputUstrLength;
	}
    }
  while (errorCode == U_BUFFER_OVERFLOW_ERROR);

  if (errorCode != U_ZERO_ERROR)
    {
      g_free (ustr);
      g_set_error (error,
		   TRANSLIT_ERROR,
		   TRANSLIT_ERROR_FAILED,
		   "failed to transliterate: %s", u_errorName (errorCode));
      return NULL;
    }

  output = ustring_to_utf8 (ustr, ustrLength);
  g_free (ustr);

  if (endpos)
    *endpos = inputUstrLength;

  return output;
}