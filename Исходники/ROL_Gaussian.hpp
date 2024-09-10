 void test(std::ostream &outStream = std::cout ) const {
   size_t size = 1;
   std::vector<Real> X(size,4.*(Real)rand()/(Real)RAND_MAX - 2.);
   std::vector<int> T(size,0);
   Distribution<Real>::test(X,T,outStream);
 }