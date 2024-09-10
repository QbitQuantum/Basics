unsigned char get_symbol(int select) {
  long code = 0;
  int length;
  int index;

  for (length = 0; length < 16; length++) {
    code = (2 * code) | get_one_bit();
    if (code <= MaxCode[select][length]) { break; }
  }
  index = ValPtr[select][length] + code - MinCode[select][length];

  if (index < MAX_SIZE(select / 2)) { return HTable[select][index]; }
  ERR("%ld:\tWARNING:\tOverflowing symbol table !\n", FTELL());
  return 0;
}