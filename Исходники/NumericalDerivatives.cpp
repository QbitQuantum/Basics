 Matrix NumericalDerivatives::Hessian(const Vector &x,
                                      bool quick_and_dirty) const {
   int dim = x.size();
   SpdMatrix ans(x.size());
   const double tol = cbrt(std::numeric_limits<double>::epsilon());
   for (int i = 0; i < dim; ++i) {
     double hi = tol * std::max<double>(0.1, fabs(x[i]));
     int lo = quick_and_dirty ? i : 0;
     for (int j = lo; j < dim; ++j) {
       double hj = tol * std::max<double>(0.1, fabs(x[j]));
       if (i == j) {
         ans(i, j) = homogeneous_scalar_second_derivative(x, i, hi);
       } else {
         ans(i, j) = scalar_second_derivative(x, i, hi, j, hj);
       }
     }
   }
   if (quick_and_dirty) {
     ans.reflect();
   } else {
     ans = .5 * (ans + ans.transpose());
   }
   return std::move(ans);
 }