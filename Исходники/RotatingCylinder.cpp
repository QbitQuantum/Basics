 void values(FieldContainer<double> &values, BasisCachePtr basisCache)
 {
   CHECK_VALUES_RANK(values);
   values.initialize(_a);
 }