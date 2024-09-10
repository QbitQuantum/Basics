 inline
 fvar<typename stan::return_type<T1,T2>::type>
 fmod(const T1& x1, const fvar<T2>& x2) {
   using std::fmod;
   using std::floor;
   return fvar<typename stan::return_type<T1,T2>::type>(
     fmod(x1, x2.val_), -x2.d_ * floor(x1 / x2.val_));
 }