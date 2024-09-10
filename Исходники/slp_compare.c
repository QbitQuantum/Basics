/** Lexical compare routine.
 *
 * Performs a lexical string compare on two normalized UTF-8 strings as
 * described in RFC 2608, section 6.4.
 *
 * @param[in] str1 - A pointer to string to be compared.
 * @param[in] str2 - A pointer to string to be compared.
 * @param[in] length - The maximum length to compare in bytes.
 *
 * @return Zero if @p str1 is equal to @p str2, less than zero if @p str1
 *    is greater than @p str2, greater than zero if @p str1 is less than
 *    @p str2.
 */
static int SLPCompareNormalizedString(const char * str1,
      const char * str2, size_t length)
{
#ifdef HAVE_ICU
   int result;
   UErrorCode uerr = 0;
   UChar * ustr1 = xmalloc((length + 1) * sizeof(UChar));
   UChar * ustr2 = xmalloc((length + 1) * sizeof(UChar));
   if (ustr1 && ustr2)
   {
      u_strFromUTF8(ustr1, (int32_t)length + 1, 0, str1,
            (int32_t)length, &uerr);
      u_strFromUTF8(ustr2, (int32_t)length + 1, 0, str2,
            (int32_t)length, &uerr);
   }
   if (ustr1 != 0 && ustr2 != 0 && uerr == 0)
      result = (int)u_strncasecmp(ustr1, ustr2, (int32_t)length, 0);
   else
      result = strncasecmp(str1, str2, length);
   xfree(ustr1);
   xfree(ustr2);
   return result;
#else
   return strncasecmp(str1, str2, length);
#endif /* HAVE_ICU */
}