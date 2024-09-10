TEST(FastUpdate, BlockMatrixRemove)
{
  typedef double Scalar;
  typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> matrix_t;

  std::vector<int> N_list, M_list;
  N_list.push_back(10);
  M_list.push_back(10);
  M_list.push_back(20);
  M_list.push_back(30);

  for (int n=0; n<N_list.size(); ++n) {
    for (int m=0; m<M_list.size(); ++m) {
      const int N = N_list[n];
      const int M = M_list[m];

      matrix_t BigMatrix(N+M, N+M, 0), invBigMatrix(N+M, N+M, 0);//G, G^{-1}
      matrix_t SmallMatrix(N,N,0);//G'
      std::vector<std::pair<int,int> > swapped_rows_in_G, swapped_cols_in_G;

      randomize_matrix(BigMatrix, 100);//100 is a seed
      invBigMatrix = inverse(BigMatrix);

      //which rows and cols are to be removed
      std::vector<int> rows_removed(N+M);
      std::vector<int> rows_remain(N);
      for (int i=0; i<N+M; ++i) {
        rows_removed[i] = i;
      }
      std::random_shuffle(rows_removed.begin(), rows_removed.end());
      for (int i=0; i<N; ++i) {
        rows_remain[i] = rows_removed[i+M];
      }
      rows_removed.resize(M);
      std::sort(rows_removed.begin(), rows_removed.end());
      std::sort(rows_remain.begin(), rows_remain.end());

      for (int j=0; j<N; ++j) {
        for (int i=0; i<N; ++i) {
          SmallMatrix(i,j) = BigMatrix(rows_remain[i], rows_remain[j]);
        }
      }

      //testing compute_det_ratio_down
      double det_rat = compute_det_ratio_down(M,rows_removed,invBigMatrix);
      ASSERT_TRUE(std::abs(det_rat-alps::numeric::determinant(SmallMatrix)/alps::numeric::determinant(BigMatrix))<1E-8) << "N=" << N << " M=" << M;

      matrix_t invSmallMatrix2(invBigMatrix);
      double det_rat2 = compute_inverse_matrix_down(M,rows_removed,invSmallMatrix2, swap_list);
      ASSERT_TRUE(std::abs(det_rat-det_rat2)<1E-8) << "N=" << N << " M=" << M;

      matrix_t SmallMatrix3(BigMatrix);
      for (int s=0; s<swap_list.size(); ++s) {
        SmallMatrix3.swap_cols(swap_list[s].first, swap_list[s].second);
        SmallMatrix3.swap_rows(swap_list[s].first, swap_list[s].second);
      }
      SmallMatrix3.resize(N,N);
      ASSERT_TRUE(alps::numeric::norm_square(inverse(SmallMatrix3)-invSmallMatrix2)<1E-8) << "N=" << N << " M=" << M;
    }
  }
}