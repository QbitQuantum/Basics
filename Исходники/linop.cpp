void At_mul_A(Eigen::MatrixXd & out, SparseDoubleFeat & A) {
  if (out.cols() != A.cols()) {
    throw std::runtime_error("At_mul_A(SparseDoubleFeat): out.cols() must equal A.cols()");
  }
  if (out.cols() != out.rows()) {
    throw std::runtime_error("At_mul_A(SparseDoubleFeat): out must be square matrix.)");
  }
  out.setZero();
  const int nfeat = A.M.ncol;

#pragma omp parallel for schedule(dynamic, 8)
  for (int f1 = 0; f1 < nfeat; f1++) {
    // looping over all non-zero rows of f1
    for (int i = A.Mt.row_ptr[f1], end = A.Mt.row_ptr[f1 + 1]; i < end; i++) {
      int Mrow     = A.Mt.cols[i]; /* row in M */
      double val1  = A.Mt.vals[i]; /* value for Mrow */

      for (int j = A.M.row_ptr[Mrow], end2 = A.M.row_ptr[Mrow + 1]; j < end2; j++) {
        int f2 = A.M.cols[j];
        if (f1 <= f2) {
          out(f2, f1) += A.M.vals[j] * val1;
        }
      }
    }
  }
}