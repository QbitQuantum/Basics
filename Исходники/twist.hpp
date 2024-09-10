    /// @brief Create a twist by taking the logarithm of a homogeneous transformation matrix.
    /// @param HT a homogeneous transformation matrix.
    Twist(const HomogeneousTransform<NumType>& HT)
    {
      Eigen::Matrix<NumType, 3, 3> Ainv;

      // Create the skew matrix from the rotation part of the homogeneous transform
      _skew = Skew<NumType>(HT.rotation());

      // p. 414 from Sastry
      Translation<NumType> trans = HT.translation();

      // Get the norm of the rotation
      NumType skewNorm = _skew.norm();

      // Pure rotation
      if ( fabs(trans.norm()) < 1e-10)
      {
        Ainv = Eigen::Matrix<NumType, 3, 3>::Zero();
      }
      // Pure translation
      else if (fabs(skewNorm) < 1e-10)
      {
        Ainv = Eigen::Matrix<NumType, 3, 3>::Identity();
      }
      else
      {
        Ainv = Eigen::Matrix<double, 3, 3>::Identity() +
          _skew._data/2 +
          (2*sin(skewNorm) - skewNorm*(1 + cos(skewNorm)))/(2*skewNorm*skewNorm*sin(skewNorm))*_skew._data*_skew._data;

      }
      _velocity = Translation<NumType>(
            Ainv(0, 0)*trans(0) + Ainv(0, 1)*trans(1) + Ainv(0, 2)*trans(2),
            Ainv(1, 0)*trans(0) + Ainv(1, 1)*trans(1) + Ainv(1, 2)*trans(2),
            Ainv(2, 0)*trans(0) + Ainv(2, 1)*trans(1) + Ainv(2, 2)*trans(2)
            );

      _zeroVal = (NumType)0;
    }