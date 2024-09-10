 inline fvar<T> asin(const fvar<T>& x) {
   using std::asin;
   using std::sqrt;
   return fvar<T>(asin(x.val_), x.d_ / sqrt(1 - square(x.val_)));
 }