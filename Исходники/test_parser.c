void check_functions(void) {
  long double *a = malloc(sizeof(long double));
  *a = 46;
  hashtbl_insert(vars, "a", a);

  ASSERT_EQ(evaluate("max(10, 20, 12, 15)"), 20);
  ASSERT_EQ(evaluate("min(11, 21, 15, 25)"), 11);
  ASSERT_EQ(evaluate("sum(1, 2, 3, 4, 5, 6)"), 21);
  ASSERT_EQ(evaluate("avg(3.4, 4e-2, 3.5, a)"), 13.235);
  ASSERT_EQ(evaluate("abs(-34)"), 34);

  *a = evaluate("random()");
  ASSERT_EQ(evaluate("cos(a)**2 + sin(a)**2"), 1.0);
  ASSERT_EQ(evaluate("sin(phi)/cos(phi) - tan(phi)"), 0.0);
  ASSERT_EQ(evaluate("1 + tan(a)**2 - 1/cos(a)**2"), 0.0);

  ASSERT_EQ(evaluate("atan2(a, phi) == atan(a/phi)"), 1);
  ASSERT_EQ(evaluate("acos(cos(phi)) - phi"), 0.0);
  ASSERT_EQ(evaluate("asin(sin(phi/4)) == phi/4"), 1);

  ASSERT_EQ(evaluate("log(exp(3))"), 3);
  ASSERT_EPS(evaluate("log(234 * 4234) - log(234) - log(4234)"), 0.0, 1.0e-5);

  ASSERT_EQ(roundl(evaluate("gamma(16)")), 1307674368000);
}