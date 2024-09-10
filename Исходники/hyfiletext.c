/** 
 * @internal walk the given UTF8 string, looking for non-ASCII characters.
 * @return  0 if none were found, or, if non-ASCII strings were found,
 * answer the length of the buffer if it were converted to platform
 * encoding
 *
 * @note this relies on the assumption that wide chars are Unicode.
 * If not, the platform will need different support for this
 */
static IDATA
walkUTF8String (const U_8 * buf, IDATA nbytes)
{
  const U_8 *end = buf + nbytes;
  const U_8 *cursor = buf;
  IDATA newLength = 0;
  int hasHighChars = 0;
  /* reset the shift state */
  wctomb (NULL, 0);
  while (cursor < end)
    {
      if ((*cursor & 0x80) == 0x80)
        {
          char temp[MB_CUR_MAX];
          int wcresult;
          U_16 unicode;
          U_32 numberU8Consumed =
            decodeUTF8CharN (cursor, &unicode, end - cursor);
          if (numberU8Consumed == 0)
            {
              /* an illegal encoding was encountered! Don't try to decode the string */
              return 0;
            }
          cursor += numberU8Consumed;
          /* calculate the encoded length of this character */
          wcresult = wctomb (temp, (wchar_t) unicode);
          if (wcresult == -1)
            {
              /* an un-encodable char was encountered */
              newLength += 1;
            }
          else
            {
              newLength += wcresult;
            }
          hasHighChars = 1;
        }
      else
        {
          newLength += 1;
          cursor += 1;
        }
    }
  return hasHighChars ? newLength : 0;
}