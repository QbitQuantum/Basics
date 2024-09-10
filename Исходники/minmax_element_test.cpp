int test_main( int argc, char* argv[] )
{
#ifndef BOOST_NO_STDC_NAMESPACE
  using std::atoi;
#endif

  int n = 100;
  if (argc > 1) n = atoi(argv[1]);

  test<int>(n);
  test<custom>(n);

  return 0;
}