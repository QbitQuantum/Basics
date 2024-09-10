 T2 convert(const T1& i) const
 {
     T2 o { };
     assert(operator()(i, o));
     return o;
 }