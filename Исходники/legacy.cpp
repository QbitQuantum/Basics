//int main(int argc, const char * const argv[]) {
int main(int, const char * const *) {
  static const char* test[4] = {
    "\\u304D\\u3085\\u3046\\u0000",
    "\\u30AD\\u30E6\\u30A6\\u0000",
    "\\u304D\\u3086\\u3046\\u0000",
    "\\u30AD\\u30E5\\u30A6\\u0000"
  };

#if 0
  static const char* test2[4] = {
    "dbc\\u0000",
      "cbc\\u0000",
      "bbc\\u0000",
      "abc\\u0000"
  };
#endif

  static UChar uTest[4][5];

  static uint8_t keys[4][32];

  uint32_t i = 0;

  for(i = 0; i<4; i++) {
    u_unescape(test[i], uTest[i], 5);
  }
  printArray("Before current", uTest, 4);
  test_current(uTest, 4, 5, keys);
  printArray("After current", uTest, 4);
  printKeys("Current keys", keys, 4);

  for(i = 0; i<4; i++) {
    u_unescape(test[i], uTest[i], 5);
  }
  printArray("Before legacy", uTest, 4);
  test_legacy(uTest, 4, 5, keys);
  printArray("After legacy", uTest, 4);
  printKeys("Legacy keys", keys, 4);


  return 0;
}