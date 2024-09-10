TEST(search, lfind_lsearch) {
  int xs[10];
  memset(xs, 0, sizeof(xs));
  size_t x_size = 0;

  int needle;

  // lfind(3) can't find '2' in the empty table.
  needle = 2;
  ASSERT_EQ(nullptr, lfind(&needle, xs, &x_size, sizeof(xs[0]), int_cmp));
  ASSERT_EQ(0U, x_size);

  // lsearch(3) will add it.
  ASSERT_EQ(&xs[0], lsearch(&needle, xs, &x_size, sizeof(xs[0]), int_cmp));
  ASSERT_EQ(2, xs[0]);
  ASSERT_EQ(1U, x_size);

  // And then lfind(3) can find it.
  ASSERT_EQ(&xs[0], lfind(&needle, xs, &x_size, sizeof(xs[0]), int_cmp));
  ASSERT_EQ(1U, x_size);

  // Inserting a duplicate does nothing (but returns the existing element).
  ASSERT_EQ(&xs[0], lsearch(&needle, xs, &x_size, sizeof(xs[0]), int_cmp));
  ASSERT_EQ(1U, x_size);
}