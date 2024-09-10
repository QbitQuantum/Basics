  /// \brief Log: SE3 -> se3.
  ///
  /// Pseudo-inverse of exp from SE3 -> { v,w \in se3, ||w|| < 2pi }.
  template <typename _Scalar, int _Options> MotionTpl<_Scalar,_Options>
  log6(const SE3Tpl<_Scalar, _Options> & m)
  {
    typedef _Scalar Scalar;
    typedef typename SE3Tpl<Scalar,_Options>::Vector3 Vector3;
    typedef typename SE3Tpl<Scalar,_Options>::Matrix3 Matrix3;

    const Matrix3 & R = m.rotation();
    const Vector3 & p = m.translation();
    Vector3 w(log3(R));
    Vector3 v;
    Scalar t = w.norm();
    if (t > 1e-15)
    {
      Matrix3 S(skew(w));
      double ct,st; SINCOS (t,&st,&ct);
      Matrix3 V(
        Matrix3::Identity() +
        (1 - ct) / (t * t) * S + (t - st) / (t * t * t) * S * S);
      v = V.inverse() * p;
    }
    else
    {
      v = p;
    }
    return MotionTpl<_Scalar,_Options>(v, w);
  }