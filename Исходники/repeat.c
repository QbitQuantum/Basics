/***********************************************************************
 *
 * FUNCTION:    SubstituteStr
 *
 * DESCRIPTION: This routine substitutes the occurrence a token, within
 *              a string, with another string.
 *
 * PARAMETERS:  str    - string containing token string
 *              token  - the string to be replaced
 *              sub    - the string to substitute for the token
 *              subLen - length of the substitute string.
 *
 * RETURNED:    pointer to the string
 *
 ***********************************************************************/
static Char* SubstituteStr(Char* str, const Char* token, const Char* sub, UInt16 subLen) {
  const UInt16 tokenLen = StrLen(token);
  const UInt16 charsToMove = subLen - tokenLen;
  const UInt16 strLen = StrLen(str);
  MemHandle strH = MemPtrRecoverHandle(str);
  const UInt16 blockSize = MemHandleSize(strH);
  Char* ptr = StrStr(str, token);

  ASSERT(str);
  ASSERT(token);
  ASSERT(sub);

  /* Find the start of the token string, if it doesn't exist, exit. */
  if (ptr == NULL)
    return str;

  /* Resize the string if necessary. */
  if (strLen + charsToMove + 1 >= blockSize) {
    MemHandleUnlock(strH);
    MemHandleResize(strH, strLen + charsToMove + 1);
    str = MemHandleLock(strH);
    ASSERT(str);
    ptr = StrStr(str, token);
    ASSERT(ptr);
  }

  /* Make room for the substitute string. */
  if (charsToMove)
    MemMove(ptr + subLen, ptr + tokenLen, StrLen (ptr + tokenLen)+1);
  
  /* Replace the token with the substitute string. */
  MemMove(ptr, sub, subLen);
  
  return str;
}