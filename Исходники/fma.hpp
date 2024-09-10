 inline
 fvar<typename stan::return_type<T1, T2, T3>::type>
 fma(const fvar<T1>& x1, const fvar<T2>& x2, const fvar<T3>& x3) {
   return fvar<typename stan::return_type<T1, T2, T3>::type>
     (fma(x1.val_, x2.val_, x3.val_),
      x1.d_ * x2.val_ + x2.d_ * x1.val_ + x3.d_);
 }