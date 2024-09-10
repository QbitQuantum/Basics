/**
 * This method is called just after a "<" has been consumed 
 * and we know we're at the start of some kind of tagged 
 * element. We don't know yet if it's a tag or a comment.
 * 
 * @param   aChar is the last char read
 * @param   aToken is the out arg holding our new token (the function allocates
 *                 the return token using mTokenAllocator).
 * @param   aScanner represents our input source
 * @param   aFlushTokens is an OUT parameter use to tell consumers to flush
 *                       the current tokens after processing the current one.
 * @return  error code.
 */
nsresult
nsHTMLTokenizer::ConsumeTag(PRUnichar aChar,
                            CToken*& aToken,
                            nsScanner& aScanner,
                            bool& aFlushTokens)
{
  PRUnichar theNextChar, oldChar;
  nsresult result = aScanner.Peek(aChar, 1);

  if (NS_OK == result) {
    switch (aChar) {
      case kForwardSlash:
        result = aScanner.Peek(theNextChar, 2);

        if (NS_OK == result) {
          // Get the original "<" (we've already seen it with a Peek)
          aScanner.GetChar(oldChar);

          // XML allows non ASCII tag names, consume this as an end tag. This
          // is needed to make XML view source work
          bool isXML = !!(mFlags & NS_IPARSER_FLAG_XML);
          if (nsCRT::IsAsciiAlpha(theNextChar) ||
              kGreaterThan == theNextChar      ||
              (isXML && !nsCRT::IsAscii(theNextChar))) {
            result = ConsumeEndTag(aChar, aToken, aScanner);
          } else {
            result = ConsumeComment(aChar, aToken, aScanner);
          }
        }

        break;

      case kExclamation:
        result = aScanner.Peek(theNextChar, 2);

        if (NS_OK == result) {
          // Get the original "<" (we've already seen it with a Peek)
          aScanner.GetChar(oldChar);

          if (kMinus == theNextChar || kGreaterThan == theNextChar) {
            result = ConsumeComment(aChar, aToken, aScanner);
          } else {
            result = ConsumeSpecialMarkup(aChar, aToken, aScanner);
          }
        }
        break;

      case kQuestionMark:
        // It must be a processing instruction...
        // Get the original "<" (we've already seen it with a Peek)
        aScanner.GetChar(oldChar);
        result = ConsumeProcessingInstruction(aChar, aToken, aScanner);
        break;

      default:
        // XML allows non ASCII tag names, consume this as a start tag.
        bool isXML = !!(mFlags & NS_IPARSER_FLAG_XML);
        if (nsCRT::IsAsciiAlpha(aChar) ||
            (isXML && !nsCRT::IsAscii(aChar))) {
          // Get the original "<" (we've already seen it with a Peek)
          aScanner.GetChar(oldChar);
          result = ConsumeStartTag(aChar, aToken, aScanner, aFlushTokens);
        } else {
          // We are not dealing with a tag. So, don't consume the original
          // char and leave the decision to ConsumeText().
          result = ConsumeText(aToken, aScanner);
        }
    }
  }

  // Last ditch attempt to make sure we don't lose data.
  if (kEOF == result && !aScanner.IsIncremental()) {
    // Whoops, we don't want to lose any data! Consume the rest as text.
    // This normally happens for either a trailing < or </
    result = ConsumeText(aToken, aScanner);
  }

  return result;
}