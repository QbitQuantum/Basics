/*
 * @implemented
 */
int _ismbslead( const unsigned char *start, const unsigned char *str)
{
  int lead = 0;

  /* Lead bytes can also be trail bytes so we need to analyse the string
   */
  while (start <= str)
  {
    if (!*start)
      return 0;
    lead = !lead && _ismbblead(*start);
    start++;
  }

  return lead ? -1 : 0;
}