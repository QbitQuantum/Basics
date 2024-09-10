TEST(Zlib, Basic)
{
  std::string s = Toolbox::GenerateUuid();
  s = s + s + s + s;
 
  std::string compressed, compressed2;
  ZlibCompressor c;
  c.Compress(compressed, s);

  std::vector<uint8_t> v, vv;
  StringToVector(v, s);
  c.Compress(compressed2, v);
  ASSERT_EQ(compressed, compressed2);

  std::string uncompressed;
  c.Uncompress(uncompressed, compressed);
  ASSERT_EQ(s.size(), uncompressed.size());
  ASSERT_EQ(0, memcmp(&s[0], &uncompressed[0], s.size()));

  StringToVector(vv, compressed);
  c.Uncompress(uncompressed, vv);
  ASSERT_EQ(s.size(), uncompressed.size());
  ASSERT_EQ(0, memcmp(&s[0], &uncompressed[0], s.size()));
}