void test_round_even()
{
  cout << "Testing 'RoundEven' tie-breaking\n";

  double min = boost::numeric::bounds<double>::lowest();
  double max = boost::numeric::bounds<double>::highest();

#if !defined(BOOST_NO_STDC_NAMESPACE)
  using std::floor ;
  using std::ceil ;
#endif
  test_round_even(min, floor(min));
  test_round_even(max, ceil (max));
  test_round_even(2.0, 2.0);
  test_round_even(2.3, 2.0);
  test_round_even(2.5, 2.0);
  test_round_even(2.7, 3.0);
  test_round_even(3.0, 3.0);
  test_round_even(3.3, 3.0);
  test_round_even(3.5, 4.0);
  test_round_even(3.7, 4.0);
}