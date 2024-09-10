static void expect_contents(const quotient_filter<T, H, B> &c,
                            const initializer_list<size_t> hash_list) {
  ASSERT_TRUE(hash_list.size() > 0) << "For empty filters use expect_empty()";

  EXPECT_FALSE(c.empty());
  EXPECT_EQ(hash_list.size(), c.size());
  EXPECT_EQ(ptrdiff_t(hash_list.size()), distance(c.begin(), c.end()));
  EXPECT_FLOAT_EQ(float(c.size()) / c.slot_count(), c.load_factor());
  EXPECT_LE(c.load_factor(), c.max_load_factor());

  auto it = c.begin();
  for (const size_t hash : hash_list) {
    ASSERT_TRUE(it != c.end());
    EXPECT_EQ(hash, *it++);
  }
  EXPECT_TRUE(it == c.end());
}