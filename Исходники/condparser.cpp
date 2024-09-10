static bool isAlphaNum(const QChar c)
{
   return isAlpha(c) || (c >= '0' && c <= '9');
}