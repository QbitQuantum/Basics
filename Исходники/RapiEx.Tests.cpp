TEST_F(GetSystemParametersInfoTest, should_get_some_oem_info) {
  const int SPI_GETOEMINFO = 258;
  rapi::SystemParametersInfoInput input(SPI_GETOEMINFO, expectedSize, true);
  ASSERT_PRED_FORMAT3(assertInvoke, sizeof(input), (LPBYTE)&input, S_OK);
  ASSERT_FALSE(IsBadStringPtrW((LPCWSTR)output, expectedSize));
  // Just so we can inspect the output value while debugging.
  LPCWSTR oemText = (LPCWSTR)output;
}