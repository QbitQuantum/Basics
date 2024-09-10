 inline
 fvar<T>
 fdim(const fvar<T>& x1, const fvar<T>& x2) {
   using stan::math::fdim;
   using std::floor;
   if(x1.val_ < x2.val_)
     return fvar<T>(fdim(x1.val_, x2.val_), 0);
   else 
     return fvar<T>(fdim(x1.val_, x2.val_),
                    x1.d_ - x2.d_ * floor(x1.val_ / x2.val_));
 }