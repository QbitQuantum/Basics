    inline
    fvar<T>
    acos(const fvar<T>& x) {
      using std::acos;
      using std::sqrt;
      using stan::math::square;

      return fvar<T>(acos(x.val_), x.d_ / -sqrt(1 - square(x.val_)));
    }