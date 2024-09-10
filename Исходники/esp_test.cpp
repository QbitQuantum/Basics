TEST(TEST3, test3) {
  srand(time(NULL));
  Esp esp;
  size_t size = 10000;
  string str = "";
  for (size_t i = 0; i < size; ++i) {
    str += rand();
  }

  esp.readString(str);
  esp.compress();
  esp.convertRCFG2CFG();

  vector<char> istring;
  esp.decompress(istring);

  ASSERT_EQ(true, str.size() == istring.size());
  for (size_t i = 0; i < str.size(); ++i) 
    ASSERT_EQ(true, str[i] == istring[i]);
}