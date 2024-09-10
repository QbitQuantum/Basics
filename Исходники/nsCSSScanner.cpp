/**
 * Gather up the characters in an identifier. The identfier was
 * started by "aChar" which will be appended to aIdent. The result
 * will be aIdent with all of the identifier characters appended
 * until the first non-identifier character is seen. The termination
 * character is unread for the future re-reading.
 *
 * Returns failure when the character sequence does not form an ident at
 * all, in which case the caller is responsible for pushing back or
 * otherwise handling aChar.  (This occurs only when aChar is '\'.)
 */
bool
nsCSSScanner::GatherIdent(int32_t aChar, nsString& aIdent)
{
  if (aChar == '\\') {
    if (!ParseAndAppendEscape(aIdent, false)) {
      return false;
    }
  } else {
    MOZ_ASSERT(aChar > 0);
    aIdent.Append(aChar);
  }
  for (;;) {
    // If nothing in pushback, first try to get as much as possible in one go
    if (!mPushbackCount && mOffset < mCount) {
      // See how much we can consume and append in one go
      uint32_t n = mOffset;
      // Count number of Ident characters that can be processed
      while (n < mCount && IsIdent(mReadPointer[n])) {
        ++n;
      }
      // Add to the token what we have so far
      if (n > mOffset) {
#ifdef CSS_REPORT_PARSE_ERRORS
        mColNumber += n - mOffset;
#endif
        aIdent.Append(&mReadPointer[mOffset], n - mOffset);
        mOffset = n;
      }
    }

    aChar = Read();
    if (aChar < 0) break;
    if (aChar == '\\') {
      if (!ParseAndAppendEscape(aIdent, false)) {
        Pushback(aChar);
        break;
      }
    } else if (IsIdent(aChar)) {
      aIdent.Append(PRUnichar(aChar));
    } else {
      Pushback(aChar);
      break;
    }
  }
  MOZ_ASSERT(aIdent.Length() > 0);
  return true;
}