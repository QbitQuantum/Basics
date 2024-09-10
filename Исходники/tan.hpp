 inline
 fvar<T>
 tan(const fvar<T>& x) {
   using std::cos;
   using std::tan;
   return fvar<T>(tan(x.val_), x.d_ / (cos(x.val_) * cos(x.val_)));
 }