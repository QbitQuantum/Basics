/*********************************************************************
*
*       _IsAlphaNum
*/
static int _IsAlphaNum(int Key) {
  Key = _Tolower(Key);
  if (Key >= 'a' && Key <= 'z') {
    return 1;
  }
  if (Key >= '0' && Key <= '9') {
    return 1;
  }
  return 0;
}