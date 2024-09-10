void findWordBoundary(const UChar* chars, int len, int position, int* start, int* end)
{
    UBreakIterator* it = wordBreakIterator(chars, len);
    *end = ubrk_following(it, position);
    if (*end < 0)
        *end = ubrk_last(it);
    *start = ubrk_previous(it);
}