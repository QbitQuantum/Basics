  ACKernelAdaptorResection_K(const Mat &x2d, const Mat &x3D, const Mat3 & K)
    : x2d_(x2d.rows(), x2d.cols()), x3D_(x3D),
    N1_(K.inverse()),
    logalpha0_(log10(M_PI)), K_(K)
  {
    assert(2 == x2d_.rows());
    assert(3 == x3D_.rows());
    assert(x2d_.cols() == x3D_.cols());

    // Normalize points by inverse(K)
    ApplyTransformationToPoints(x2d, N1_, &x2d_);
  }