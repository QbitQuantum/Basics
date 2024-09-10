void run_fixed_size_test(int num_elements)
{
  using std::abs;
  typedef Matrix<Scalar, Dimension+1, Dynamic> MatrixX;
  typedef Matrix<Scalar, Dimension+1, Dimension+1> HomMatrix;
  typedef Matrix<Scalar, Dimension, Dimension> FixedMatrix;
  typedef Matrix<Scalar, Dimension, 1> FixedVector;

  const int dim = Dimension;

  // MUST be positive because in any other case det(cR_t) may become negative for
  // odd dimensions!
  const Scalar c = abs(internal::random<Scalar>());

  FixedMatrix R = randMatrixSpecialUnitary<Scalar>(dim);
  FixedVector t = Scalar(50)*FixedVector::Random(dim,1);

  HomMatrix cR_t = HomMatrix::Identity(dim+1,dim+1);
  cR_t.block(0,0,dim,dim) = c*R;
  cR_t.block(0,dim,dim,1) = t;

  MatrixX src = MatrixX::Random(dim+1, num_elements);
  src.row(dim) = Matrix<Scalar, 1, Dynamic>::Constant(num_elements, Scalar(1));

  MatrixX dst = cR_t*src;

  Block<MatrixX, Dimension, Dynamic> src_block(src,0,0,dim,num_elements);
  Block<MatrixX, Dimension, Dynamic> dst_block(dst,0,0,dim,num_elements);

  HomMatrix cR_t_umeyama = umeyama(src_block, dst_block);

  const Scalar error = ( cR_t_umeyama*src - dst ).array().square().sum();

  VERIFY(error < Scalar(10)*std::numeric_limits<Scalar>::epsilon());
}