// EscapeStr takes the passed in string and
// escapes it IN PLACE.
void
mozTXTToHTMLConv::EscapeStr(nsString& aInString, bool inAttribute)
{
  // the replace substring routines
  // don't seem to work if you have a character
  // in the in string that is also in the replacement
  // string! =(
  //aInString.ReplaceSubstring("&", "&amp;");
  //aInString.ReplaceSubstring("<", "&lt;");
  //aInString.ReplaceSubstring(">", "&gt;");
  for (uint32_t i = 0; i < aInString.Length();)
  {
    switch (aInString[i])
    {
    case '<':
      aInString.Cut(i, 1);
      aInString.Insert(NS_LITERAL_STRING("&lt;"), i);
      i += 4; // skip past the integers we just added
      break;
    case '>':
      aInString.Cut(i, 1);
      aInString.Insert(NS_LITERAL_STRING("&gt;"), i);
      i += 4; // skip past the integers we just added
      break;
    case '&':
      aInString.Cut(i, 1);
      aInString.Insert(NS_LITERAL_STRING("&amp;"), i);
      i += 5; // skip past the integers we just added
      break;
    case '"':
      if (inAttribute)
      {
        aInString.Cut(i, 1);
        aInString.Insert(NS_LITERAL_STRING("&quot;"), i);
        i += 6;
        break;
      }
      // else fall through
      MOZ_FALLTHROUGH;
    default:
      i++;
    }
  }
}