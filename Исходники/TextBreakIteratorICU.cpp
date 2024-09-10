bool isTextBreak(TextBreakIterator* iterator, int position)
{
    return ubrk_isBoundary(reinterpret_cast<UBreakIterator*>(iterator), position);
}