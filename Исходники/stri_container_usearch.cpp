/** the returned matcher shall not be deleted by the user
 *
 * it is assumed that \code{vectorize_next()} is used:
 * for \code{i >= this->n} the last matcher is returned
 *
 *
 * @param i index
 * @param searchStr string to search in
 * @param searchStr_len string length in UChars
 */
UStringSearch* StriContainerUStringSearch::getMatcher(R_len_t i, const UChar* searchStr, int32_t searchStr_len)
{
   if (!lastMatcher) {
      this->lastMatcherIndex = (i % n);
      UErrorCode status = U_ZERO_ERROR;
      lastMatcher = usearch_openFromCollator(this->get(i).getBuffer(), this->get(i).length(),
            searchStr, searchStr_len, col, NULL, &status);
      STRI__CHECKICUSTATUS_THROW(status, {usearch_close(lastMatcher); lastMatcher = NULL;})
      return lastMatcher;