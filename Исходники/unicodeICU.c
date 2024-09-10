int
Unicode_CompareWithLocale(const char *str1,                   // IN
                          const char *str2,                   // IN
                          const char *locale,                 // IN
                          UnicodeCompareOption compareOption) // IN
{
   UCollationResult compareResult;
   UColAttributeValue comparisonStrength;
   UErrorCode status = U_ZERO_ERROR;
   int result;
   UCollator *coll;
   UCharIterator str1Iter;
   UCharIterator str2Iter;

   uiter_setUTF8(&str1Iter, (const char *)str1, -1);
   uiter_setUTF8(&str2Iter, (const char *)str2, -1);

   switch (compareOption) {
   case UNICODE_COMPARE_DEFAULT:
      comparisonStrength = UCOL_DEFAULT;
      break;
   case UNICODE_COMPARE_IGNORE_ACCENTS:
      comparisonStrength = UCOL_PRIMARY;
      break;
   case UNICODE_COMPARE_IGNORE_CASE:
      comparisonStrength = UCOL_SECONDARY;
      break;
   case UNICODE_COMPARE_IGNORE_PUNCTUATION:
      comparisonStrength = UCOL_TERTIARY;
      break;
   default:
      NOT_IMPLEMENTED();
   }

   coll = ucol_open(locale, &status);

   ASSERT(U_SUCCESS(status));
   ASSERT(coll);

   if (U_FAILURE(status) || !coll) {
      return -1;
   }

   // Normalize all strings to NFD before comparing.
   ucol_setAttribute(coll, UCOL_NORMALIZATION_MODE, UCOL_ON, &status);
   ucol_setAttribute(coll, UCOL_STRENGTH, comparisonStrength, &status);

   ASSERT(U_SUCCESS(status));

   compareResult = ucol_strcollIter(coll, &str1Iter, &str2Iter, &status);

   ucol_close(coll);

   if (U_FAILURE(status)) {
      // We'll probably only get here if the input wasn't UTF-8.
      ASSERT(U_SUCCESS(status));
      return -1;
   }

   switch (compareResult) {
   case UCOL_LESS:
      result = -1;
      break;
   case UCOL_EQUAL:
      result = 0;
      break;
   case UCOL_GREATER:
      result = 1;
      break;
   default:
      NOT_IMPLEMENTED();
   }

   return result;
}