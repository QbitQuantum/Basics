 measured_type operator()(const value_type* lo, const value_type* hi) const {
   measured_type m = algebra_type::identity();
   for (auto p = lo; p < hi; p++)
     m = algebra_type::combine(m, operator()(*p));
   return m;
 }