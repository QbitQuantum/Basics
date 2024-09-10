TEST_F(PacksTests, test_version) {
  auto fpack = Pack("foobar", getPackWithDiscovery());
  EXPECT_EQ(fpack.getVersion(), "1.5.0");
}