/**
* Returns the text of the given node. The result depends on the type of the node. If it represents
* a quoted text entity then two consecutive quote chars are replaced by a single one and if
* escape sequence parsing is not switched off (as per sql mode) then such sequences are handled too.
*/
std::string MySQLRecognitionBase::token_text(pANTLR3_BASE_TREE node, bool keepQuotes)
{
  pANTLR3_STRING text = node->getText(node);
  if (text == NULL)
    return "";

  std::string chars;
  pANTLR3_COMMON_TOKEN token = node->getToken(node);
  ANTLR3_UINT32 type = (token != NULL) ? token->type : ANTLR3_TOKEN_INVALID;

  if (type == STRING_TOKEN)
  {
    // STRING is the grouping subtree for multiple consecutive string literals, which
    // must be concatenated.
    for (ANTLR3_UINT32 index = 0; index < node->getChildCount(node); index++)
    {
      pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)node->getChild(node, index);
      chars += token_text(child, keepQuotes);
    }

    return chars;
  }

  chars = (const char*)text->chars;
  std::string quote_char;
  switch (type)
  {
  case BACK_TICK_QUOTED_ID:
    quote_char = "`";
    break;
  case SINGLE_QUOTED_TEXT:
    quote_char = "'";
    break;
  case DOUBLE_QUOTED_TEXT:
    quote_char = "\"";
    break;
  default:
    return chars;
  }

  // First unquote then handle escape squences and double quotes.
  if (chars.size() < 3)
  {
    if (keepQuotes)
      return chars;
    return ""; // Also handles an invalid single quote char gracefully.
  }

  // Need to unquote even if keepQuotes is true to avoid trouble with replacing the outer quotes.
  // Add them back below.
  chars = base::unquote(chars);

  if ((d->_sql_mode & SQL_MODE_NO_BACKSLASH_ESCAPES) == 0)
    chars = base::unescape_sql_string(chars, quote_char[0]);
  else
    if (token->user1 > 0)
    {
      // The field user1 is set by the parser to the number of quote char pairs it found.
      // So we can use it to shortcut our handling here.
      base::replace(chars, quote_char + quote_char, quote_char);
    }

  if (keepQuotes)
    return quote_char + chars + quote_char;
  return chars;
}