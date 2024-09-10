TEST(wchar, wmemmove_smoke) {
  const wchar_t const_wstr[] = L"This is a test of something or other.....";
  wchar_t wstr[NUM_WCHARS(sizeof(const_wstr))];

  EXPECT_EQ(wstr, wmemmove(wstr, const_wstr, NUM_WCHARS(sizeof(const_wstr))));
  EXPECT_STREQ(const_wstr, wstr);

  EXPECT_EQ(wstr+5, wmemmove(wstr+5, wstr, NUM_WCHARS(sizeof(const_wstr)) - 6));
  EXPECT_STREQ(L"This This is a test of something or other", wstr);
}