static int unichar_getprops_point__enUS(const unichar *ptr)
{
    unichar before, after;
    if ((ptr[-1] & ~0xFF) || ptr[+1] & ~0xFF)
        return UCP_PUNCT;
    before = ptr[-1];
    after = ptr[+1];
    if (iswdigit((unsigned)before) && iswdigit((unsigned)after))
        return UCP_ALPHA;
    if (iswalpha((unsigned)before) && iswalpha((unsigned)after))
        return UCP_ALPHA;
    return UCP_PUNCT;
}