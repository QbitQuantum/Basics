 inline
 fvar<T>
 cosh(const fvar<T>& x) {
   using std::sinh;
   using std::cosh;
   return fvar<T>(cosh(x.val_), x.d_ * sinh(x.val_));
 }