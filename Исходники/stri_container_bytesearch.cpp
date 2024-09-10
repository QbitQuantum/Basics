/**
 *
 * @version 0.4-1 (Marek Gagolewski, 2014-12-07)
 */
bool StriContainerByteSearch::startsWith(R_len_t byteindex)
{
   if (flags&BYTESEARCH_CASE_INSENSITIVE) {
      for (R_len_t k = 0; k < patternLenCaseInsensitive; ++k) {
         UChar32 c;
         U8_NEXT(searchStr, byteindex, searchLen, c);
         c = u_toupper(c);
         if (patternStrCaseInsensitive[k] != c)
            return false;
      }
   }
   else {
      for (R_len_t k=0; k < patternLen; ++k)
         if (searchStr[byteindex+k] != patternStr[k])
            return false;
   }

   return true; // found
}