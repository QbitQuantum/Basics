void CheckInfNan(int snprintf_fn(T*, size_t, const T*, ...),
                 const T* fmt, const T* fmt_plus,
                 const T* minus_inf, const T* inf_, const T* plus_inf,
                 const T* minus_nan, const T* nan_, const T* plus_nan) {
  T buf[BUFSIZ];

  snprintf_fn(buf, sizeof(buf), fmt, nan(""));
  EXPECT_STREQ(nan_, buf) << fmt;
  snprintf_fn(buf, sizeof(buf), fmt, -nan(""));
  EXPECT_STREQ(minus_nan, buf) << fmt;
  snprintf_fn(buf, sizeof(buf), fmt_plus, nan(""));
  EXPECT_STREQ(plus_nan, buf) << fmt_plus;
  snprintf_fn(buf, sizeof(buf), fmt_plus, -nan(""));
  EXPECT_STREQ(minus_nan, buf) << fmt_plus;

  snprintf_fn(buf, sizeof(buf), fmt, HUGE_VAL);
  EXPECT_STREQ(inf_, buf) << fmt;
  snprintf_fn(buf, sizeof(buf), fmt, -HUGE_VAL);
  EXPECT_STREQ(minus_inf, buf) << fmt;
  snprintf_fn(buf, sizeof(buf), fmt_plus, HUGE_VAL);
  EXPECT_STREQ(plus_inf, buf) << fmt_plus;
  snprintf_fn(buf, sizeof(buf), fmt_plus, -HUGE_VAL);
  EXPECT_STREQ(minus_inf, buf) << fmt_plus;
}