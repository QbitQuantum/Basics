int vectester (Vector zerovec)
{
  using std::abs;
  using std::acos;
  using std::asin;
  using std::atan;
  using std::floor;
  using std::pow;
  using std::sin;
  using std::sqrt;
  using std::tan;

  typedef typename Vector::value_type Scalar;

  Vector random_vec = zerovec;

  Vector error_vec = zerovec;

  std::srand(12345); // Fixed seed for reproduceability of failures

  // Avoid divide by zero errors or acos(x>1) NaNs later
  for (unsigned int i=0; i != random_vec.size(); ++i)
    random_vec.raw_at(i) = .25 + (static_cast<Scalar>(std::rand())/RAND_MAX/2);

  int returnval = 0;

  one_test(2*random_vec - random_vec - random_vec);

  one_test(3*random_vec - random_vec*3);

  one_test((random_vec + random_vec)/2 - random_vec);

  one_test(sqrt(random_vec) * sqrt(random_vec) - random_vec);
  one_test(random_vec*random_vec - pow(random_vec,2));
  one_test(sqrt(random_vec) - pow(random_vec,Scalar(.5)));

  one_test(random_vec - sin(asin(random_vec)));
  one_test(random_vec - tan(atan(random_vec)));

  one_test(floor(random_vec / 2));
  one_test(abs(random_vec) - random_vec);

  return returnval;
}