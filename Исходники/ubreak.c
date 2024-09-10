void printAt(UBreakIterator* boundary, int32_t pos , UChar* str) {
  int32_t start;
  int32_t end = ubrk_following(boundary, pos);
  start = ubrk_previous(boundary);
  printTextRange(str, start, end );
}