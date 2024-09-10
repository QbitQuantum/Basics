::testing::AssertionResult array_are_close(X const &x1, Y const &y1,double precision = 1.e-10) {
 triqs::arrays::array<typename X::value_type, X::rank> x = x1; 
 triqs::arrays::array<typename X::value_type, X::rank> y = y1; 
 if (x.domain() != y.domain()) 
 return ::testing::AssertionFailure() << "Comparing two arrays of different size "
          << "\n X = "<<  x << "\n Y = "<< y;

 if (max_element(abs(x - y)) < precision)
  return ::testing::AssertionSuccess();
 else
  return ::testing::AssertionFailure() << "max_element(abs(x-y)) = " << max_element(abs(x - y)) << "\n X = "<<  x << "\n Y = "<< y;
}