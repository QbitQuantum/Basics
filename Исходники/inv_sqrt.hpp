    inline 
    typename boost::math::tools::promote_args<T>::type
    inv_sqrt(const T x) {
      using std::sqrt;

      return 1.0 / sqrt(x);
    }