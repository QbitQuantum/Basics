template<typename MatrixType> void test_reference(const MatrixType& m) {
  typedef typename MatrixType::Scalar Scalar;
  enum { Flag          =  MatrixType::IsRowMajor ? Eigen::RowMajor : Eigen::ColMajor};
  enum { TransposeFlag = !MatrixType::IsRowMajor ? Eigen::RowMajor : Eigen::ColMajor};
  typename MatrixType::Index rows = m.rows(), cols=m.cols();
  typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Flag         > MatrixX;
  typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, TransposeFlag> MatrixXT;
  // Dynamic reference:
  typedef Eigen::Ref<const MatrixX  > Ref;
  typedef Eigen::Ref<const MatrixXT > RefT;

  Ref r1(m);
  Ref r2(m.block(rows/3, cols/4, rows/2, cols/2));
  RefT r3(m.transpose());
  RefT r4(m.topLeftCorner(rows/2, cols/2).transpose());

  VERIFY_RAISES_ASSERT(RefT r5(m));
  VERIFY_RAISES_ASSERT(Ref r6(m.transpose()));
  VERIFY_RAISES_ASSERT(Ref r7(Scalar(2) * m));

  // Copy constructors shall also never malloc
  Ref r8 = r1;
  RefT r9 = r3;

  // Initializing from a compatible Ref shall also never malloc
  Eigen::Ref<const MatrixX, Unaligned, Stride<Dynamic, Dynamic> > r10=r8, r11=m;

  // Initializing from an incompatible Ref will malloc:
  typedef Eigen::Ref<const MatrixX, Aligned> RefAligned;
  VERIFY_RAISES_ASSERT(RefAligned r12=r10);
  VERIFY_RAISES_ASSERT(Ref r13=r10); // r10 has more dynamic strides

}