inline fvar<T> expm1(const fvar<T>& x) {
    using std::exp;
    return fvar<T>(expm1(x.val_), x.d_ * exp(x.val_));
}