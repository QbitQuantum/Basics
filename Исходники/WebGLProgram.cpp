/** Takes an ASCII string like "foo[i]", turns it into "foo" and returns "[i]" in bracketPart
  * 
  * \param string input/output: the string to split, becomes the string without the bracket part
  * \param bracketPart output: gets the bracket part.
  * 
  * Notice that if there are multiple brackets like "foo[i].bar[j]", only the last bracket is split.
  */
static bool SplitLastSquareBracket(nsACString& string, nsCString& bracketPart)
{
    MOZ_ASSERT(bracketPart.IsEmpty(), "SplitLastSquareBracket must be called with empty bracketPart string");

    if (string.IsEmpty())
        return false;

    char *string_start = string.BeginWriting();
    char *s = string_start + string.Length() - 1;

    if (*s != ']')
        return false;

    while (*s != '[' && s != string_start)
        s--;

    if (*s != '[')
        return false;

    bracketPart.Assign(s);
    *s = 0;
    string.EndWriting();
    string.SetLength(s - string_start);
    return true;
}