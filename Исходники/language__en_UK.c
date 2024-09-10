static int unichar_getprops_point__xftqenUK(const unichar *ptr)
{
  unichar before, after;
  if ((ptr[-1] & ~0xFF) || ptr[+1] & ~0xFF)
    return UCP_PUNCT;
  before = ptr[-1];
  after = ptr[+1];
  if (('*' == before) && (('*' == after) || iswdigit(after) || iswalpha(after)))
    return UCP_ALPHA;
  if (iswdigit(before) && (('*' == after) || iswdigit(after)))
    return UCP_ALPHA;
  if (iswalpha(before) && (('*' == after) || iswalpha(after)))
    return UCP_ALPHA;
  return UCP_PUNCT;
}