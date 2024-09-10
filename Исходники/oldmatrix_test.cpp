void test_matrix(const Matrix<size>& m)
{
  cout << "Testing matrix: " << m << std::endl;

  cout << "Transpose is: " << m.transpose() << std::endl;

  Matrix<size> minv = m.inverse();

  double mdet = m.determinant(), minvdet = minv.determinant();

  cout << "Inverse is: " << minv << std::endl;

  assert(fabs(mdet * minvdet - 1) < WFMATH_EPSILON);

  Matrix<size> nothing;

  nothing.identity();

  nothing -= m * minv;

  cout << "This should be zero: " << nothing << std::endl;

  for(int i = 0; i < size; ++i)
    for(int j = 0; j < size; ++j)
      assert(fabs(nothing.elem(i, j)) < WFMATH_EPSILON);
}