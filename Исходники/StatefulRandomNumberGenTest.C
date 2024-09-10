void
StatefulRandomNumberGenTest::testRandomGen()
{
  MooseRandom mrand;

  const unsigned n_gens = 3;
  const unsigned n_nums = 2;

  for (unsigned int i=0; i<n_gens; ++i)
    mrand.seed(i, i);

  // Save the state so that we can restore the generators
  mrand.saveState();

  std::vector<double> numbers(n_gens * n_nums);

  // Interleave the generators
  for (unsigned int i=0; i<n_nums; ++i)
    for (unsigned int j=0; j<n_gens; ++j)
      numbers[i*n_gens+j] = mrand.rand(j);


  // Reset the state
  mrand.restoreState();

  for (unsigned int i=0; i<n_nums; ++i)
    for (unsigned int j=0; j<n_gens; ++j)
      CPPUNIT_ASSERT( std::abs(mrand.rand(j) - numbers[i*n_gens+j]) < 1e-8);
}