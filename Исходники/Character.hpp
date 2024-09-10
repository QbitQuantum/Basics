// Checks for a blank character, that is, a space or a tab.
inline bool isWhitespace(int c)
{
  return ( isblank (c) == 0 ? false : true);
}