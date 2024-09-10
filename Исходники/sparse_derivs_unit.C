int vectester (Vector zerovec)
{
  using std::abs;
  using std::acos;
  using std::asin;
  using std::atan;
  using std::ceil;
  using std::cos;
  using std::cosh;
  using std::exp;
  using std::fabs;
  using std::floor;
  using std::log;
  using std::log10;
  using std::pow;
  using std::sin;
  using std::sinh;
  using std::sqrt;
  using std::tan;
  using std::tanh;

  typedef typename ValueType<Vector>::type DualScalar;
  typedef typename DualScalar::value_type Scalar;

  Vector random_vec = zerovec;

  typename DerivativeType<Vector>::type error_vec = 0;

  std::srand(12345); // Fixed seed for reproduceability of failures

  // Avoid divide by zero errors later
  for (unsigned int i=0; i != N; ++i)
    {
      random_vec.raw_at(i) = .25 + (static_cast<Scalar>(std::rand())/RAND_MAX);
      random_vec.raw_at(i).derivatives() = 1;
    }

  // Scalar pi = acos(Scalar(-1));

  int returnval = 0;

  // Running non-derivatives tests with DualNumbers sometimes catches
  // problems too

  one_test(2*random_vec - random_vec - random_vec);

  one_test(3*random_vec - random_vec*3);

  one_test((random_vec + random_vec)/2 - random_vec);

  // We had a problem in user code with the mixing of long double and
  // DualNumber<double, DynamicSparseNumberArray>

  one_test(2.L*random_vec - random_vec - 1.f*random_vec);

  // pow() is still having problems with sparse vectors?  Disabling it
  // for now.

  one_test(sqrt(random_vec) * sqrt(random_vec) - random_vec);
//  one_test(random_vec*random_vec - pow(random_vec,2));
//  one_test(sqrt(random_vec) - pow(random_vec,Scalar(.5)));

  // functions which map zero to non-zero are not defined for sparse
  // vectors.  This includes exp(), log(), cos(), cosh(),
  // pow(scalar,sparse), scalar/sparse, sparse +/- scalar...

  // one_test(log(exp(random_vec)) - random_vec);
  // one_test(exp(log(random_vec)) - random_vec);
  // one_test(exp(random_vec) - pow(exp(Scalar(1)), random_vec));

  // one_test(tan(random_vec) - sin(random_vec)/cos(random_vec));
  one_test(random_vec - sin(asin(random_vec)));
  // one_test(random_vec - cos(acos(random_vec)));
  one_test(random_vec - tan(atan(random_vec)));
  // one_test(1 - pow(sin(random_vec), 2) - pow(cos(random_vec), 2));
  // one_test(cos(random_vec) - sin(random_vec + pi/2));

  // one_test(tanh(random_vec) - sinh(random_vec)/cosh(random_vec));
  // one_test(1 + pow(sinh(random_vec), 2) - pow(cosh(random_vec), 2));

  // one_test(log10(random_vec) - log(random_vec)/log(Scalar(10)));

  one_test(floor(random_vec / 2));
  // one_test(ceil(random_vec / 2 - 1));

  one_test(abs(random_vec) - random_vec);
  // one_test(fabs(random_vec-.75) - abs(random_vec-.75));

  // And now for derivatives tests

  // one_test(derivatives(pow(sin(random_vec-2),2)) -
  //          2*sin(random_vec)*cos(random_vec));

  // one_test(derivatives(cos(2*random_vec)) + 2*sin(2*random_vec));
  // one_test(derivatives(tan(.5*random_vec)) - .5/pow(cos(.5*random_vec),2));

  // one_test(derivatives(sqrt(random_vec+1)) - 1/sqrt(random_vec+1)/2);

  // one_test(derivatives((random_vec-1)*(random_vec-1)) - 2*(random_vec-1));

//  one_test(derivatives(pow(random_vec,1.5)) -
//           1.5*pow(random_vec,.5));

  // one_test(derivatives(exp(pow(random_vec,3))) -
  //          exp(pow(random_vec,3))*3*pow(random_vec,2));

  // one_test(derivatives(exp(random_vec)) -
  //                      exp(random_vec));

  // one_test(derivatives(pow(2,random_vec)) -
  //          pow(2,random_vec)*log(Scalar(2)));

  // one_test(derivatives(asin(random_vec)) -
  //          1/sqrt(1-random_vec*random_vec));

  // one_test(derivatives(sinh(random_vec)) - cosh(random_vec));
  // one_test(derivatives(cosh(random_vec)) - sinh(random_vec));

  // one_test(derivatives(tanh(random_vec)) -
  //          derivatives(sinh(random_vec)/cosh(random_vec)));

  return returnval;
}