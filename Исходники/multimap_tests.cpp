TYPED_TEST(MultimapTest, Remove)
{
  typedef TypeParam Map;

  Map map;

  map.put("foo", 1024);
  map.remove("foo", 1024);
  ASSERT_EQ(0u, map.get("foo").size());

  ASSERT_EQ(0u, map.size());

  map.put("foo", 1024);
  map.put("foo", 1025);
  ASSERT_EQ(2u, map.get("foo").size());

  ASSERT_EQ(2u, map.size());

  map.remove("foo");
  ASSERT_EQ(0u, map.get("foo").size());
  ASSERT_EQ(0u, map.size());
}