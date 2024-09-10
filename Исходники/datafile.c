int
brlDotNumberToIndex (wchar_t number, int *index) {
  const wchar_t *character = wmemchr(brlDotNumbers, number, ARRAY_COUNT(brlDotNumbers));
  if (!character) return 0;
  *index = character - brlDotNumbers;
  return 1;
}