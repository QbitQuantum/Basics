U_CDECL_END


#define LINES 6

void CollationThaiTest::TestInvalidThai(void) {
  const char *tests[LINES] = {
    "\\u0E44\\u0E01\\u0E44\\u0E01",
    "\\u0E44\\u0E01\\u0E01\\u0E44",
    "\\u0E01\\u0E44\\u0E01\\u0E44",
    "\\u0E01\\u0E01\\u0E44\\u0E44",
    "\\u0E44\\u0E44\\u0E01\\u0E01",
    "\\u0E01\\u0E44\\u0E44\\u0E01",
  };

  UChar strings[LINES][20];

  UChar *toSort[LINES];

  int32_t i = 0, j = 0, len = 0;

  UErrorCode coll_status = U_ZERO_ERROR;
  UnicodeString iteratorText;

  thaiColl = ucol_open ("th_TH", &coll_status);
  if (U_FAILURE(coll_status)) {
    errln("Error opening Thai collator: %s", u_errorName(coll_status));
    return;
  }

  CollationElementIterator* c = ((RuleBasedCollator *)coll)->createCollationElementIterator( iteratorText );

  for(i = 0; i < (int32_t)(sizeof(tests)/sizeof(tests[0])); i++) {
    len = u_unescape(tests[i], strings[i], 20);
    strings[i][len] = 0;
    toSort[i] = strings[i];
  }

  qsort (toSort, LINES, sizeof (UChar *), StrCmp);

  for (i=0; i < LINES; i++)
  {
    logln("%i", i);
      for (j=i+1; j < LINES; j++) {
          if (ucol_strcoll (thaiColl, toSort[i], -1, toSort[j], -1) == UCOL_GREATER)
          {
              // inconsistency ordering found!
            errln("Inconsistent ordering between strings %i and %i", i, j);
          }
      }
      iteratorText.setTo(toSort[i]);
      c->setText(iteratorText, coll_status);
      backAndForth(*c);
  }

  
  ucol_close(thaiColl);
  delete c;
}