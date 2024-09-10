/// checks a character to be a valid part of an URL
inline bool IsURLChar(char c)
{
   return IsAlnum(c) || IsURLMark(c) || IsURLReserved(c) || c == '%' || c == '#' ||
          c == '[' || c == ']';
}