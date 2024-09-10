 inline
 fvar<T>
 cos(const fvar<T>& x) {
   using std::sin;
   using std::cos;
   return fvar<T>(cos(x.val_), x.d_ * -sin(x.val_));
 }